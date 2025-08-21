// Copyright Ebrahim Mottaghi Rezaei <https://www.linkedin.com/in/ebrahim-mr> 2025 All Rights Reserved. 

#include "InventoryBasedQuest.h"
#include "Conditions/HasItemsCondition.h"
#include "QuestSystem/QuestSystem.h"
#include "QuestSystem/Components/InventoryComponent.h"
#include "QuestSystem/DataAssets/GameplayItemData.h"
#include "QuestSystem/DataTypes/Structs.h"

UInventoryBasedQuest::UInventoryBasedQuest() {
	InventoryComponent = nullptr;
}

UInventoryBasedQuest::~UInventoryBasedQuest() {
	if ( InventoryComponent.IsValid() ) {
		if ( InventoryComponent->OnItemAdded.IsAlreadyBound( this, &ThisClass::OnItemAddedToInventory ) )
			InventoryComponent->OnItemAdded.AddDynamic( this, &ThisClass::OnItemAddedToInventory );

		if ( InventoryComponent->OnItemUpdated.IsAlreadyBound( this, &ThisClass::OnItemUpdatedInInventory ) )
			InventoryComponent->OnItemUpdated.AddDynamic( this, &ThisClass::OnItemUpdatedInInventory );

		InventoryComponent.Reset();
	}
}

void UInventoryBasedQuest::UpdateStatus(EQuestStatus NewStatus) {
	if ( Status == NewStatus )
		return;

	if ( !IsValid( Condition ) ) {
		UE_LOG( LogQuestSystem, Warning, TEXT( "Condition is null" ) );
		return;
	}

	if ( NewStatus == EQuestStatus::Active ) {
		if ( Condition->Evaluate_Implementation() == EQuestStatus::Completed ) {
			Status = EQuestStatus::Completed;
			Notify_StatusChanged( this, EQuestStatus::Completed );
			return;
		}

		if ( !InventoryComponent.IsValid() )
			InventoryComponent = GetInventoryComponent();

		InventoryComponent->OnItemAdded.AddDynamic( this, &ThisClass::OnItemAddedToInventory );
		InventoryComponent->OnItemUpdated.AddDynamic( this, &ThisClass::OnItemUpdatedInInventory );
	}

	Status = NewStatus;
	Notify_StatusChanged( this, Status );
}

bool UInventoryBasedQuest::CheckForRelevantItem(const UGameplayItemData* Item) const {
	if ( !IsValid( Condition ) ) {
		UE_LOG( LogQuestSystem, Error, TEXT( "Condition is null" ) );
		return false;
	}

	const auto Cond = Cast<UHasItemsCondition>( Condition );
	if ( !IsValid( Cond ) ) {
		UE_LOG( LogQuestSystem, Error, TEXT( "Could not cast %s to %s" ), *Condition->GetName(), *ThisClass::GetName() );
		return false;
	}

	for ( const auto RequiredItem : Cond->GetRequiredItems() )
		if ( RequiredItem.Item->GetId() == Item->GetId() )
			return true;

	return false;
}

void UInventoryBasedQuest::OnItemAddedToInventory(UGameplayItemData* Item) {
	bool bRelevantItemFound = CheckForRelevantItem( Item );

	if ( bRelevantItemFound && Condition->Evaluate_Implementation() == EQuestStatus::Completed )
		UpdateStatus( EQuestStatus::Completed );
}

void UInventoryBasedQuest::OnItemUpdatedInInventory(UGameplayItemData* Item, uint8 Count) {
	bool bRelevantItemFound = CheckForRelevantItem( Item );

	if ( bRelevantItemFound && Condition->Evaluate_Implementation() == EQuestStatus::Completed )
		UpdateStatus( EQuestStatus::Completed );
}
