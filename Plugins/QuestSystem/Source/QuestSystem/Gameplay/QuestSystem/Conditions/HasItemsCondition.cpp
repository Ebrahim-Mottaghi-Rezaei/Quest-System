// Copyright Ebrahim Mottaghi Rezaei <https://www.linkedin.com/in/ebrahim-mr> 2025 All Rights Reserved. 

#include "HasItemsCondition.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "QuestSystem/QuestSystem.h"
#include "QuestSystem/Components/InventoryComponent.h"
#include "QuestSystem/DataTypes/Structs.h"
#include "QuestSystem/Gameplay/QuestSystem/Interfaces/QuestInterface.h"

UHasItemsCondition::UHasItemsCondition() {}

EQuestStatus UHasItemsCondition::Evaluate_Implementation() {
	const auto PlayerController = UGameplayStatics::GetPlayerController( GetWorld(), 0 );
	if ( !IsValid( PlayerController ) ) {
		UE_LOG( LogQuestSystem, Warning, TEXT("PlayerController is null.") );
		return EQuestStatus::Failed;
	}

	const auto InventoryComponent = IQuestInterface::Execute_GetInventoryComponent( PlayerController );
	if ( !IsValid( InventoryComponent ) ) {
		UE_LOG( LogQuestSystem, Warning, TEXT("InventoryComponent is null.") );
		return EQuestStatus::Failed;
	}

	for ( const FHasItemsConditionInfo& RequiredItem : RequiredItems )
		if ( InventoryComponent->GetItemCount( RequiredItem.Item ) < RequiredItem.Count )
			return EQuestStatus::Failed;

	return EQuestStatus::Completed;
}
