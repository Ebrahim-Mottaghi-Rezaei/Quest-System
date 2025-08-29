// Copyright Ebrahim Mottaghi Rezaei [https://www.linkedin.com/in/ebrahim-mr/]. All Rights Reserved

#include "Quest.h"
#include "Conditions/QuestCondition.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "QuestSystem/QuestSystem.h"
#include "QuestSystem/Components/QuestComponent.h"
#include "QuestSystem/Gameplay/QuestSystem/Interfaces/QuestInterface.h"

UQuest::UQuest() {
	Status = EQuestStatus::NotStarted;

	Id             = FGuid::NewGuid();
	Name           = FText::FromString( TEXT( "Name" ) );
	GameplayText   = FText::FromString( TEXT( "Gameplay" ) );
	Icon           = nullptr;
	bIsTickable    = false;
	QuestComponent = nullptr;
	Condition      = nullptr;
}

void UQuest::BeginDestroy() {
	CleanUp();

	Super::BeginDestroy();
}

void UQuest::CleanUp() {
	if ( UQuestComponent* Comp = QuestComponent.Get() )
		Comp->OnQuestStatusChanged.RemoveDynamic( this, &ThisClass::OnQuestStatusChanged );

	QuestComponent.Reset();
}

void UQuest::Tick(float DeltaTime) {
	TickQuest( DeltaTime );
}

void UQuest::SetTickEnabled(bool bEnabled) {
	bIsTickable = bEnabled;
}

UQuestComponent* UQuest::GetQuestComponent() const {
	const auto World = GetWorld();
	if ( !IsValid( World ) ) {
		UE_LOG( LogQuestSystem, Warning, TEXT( "World is null" ) );
		return nullptr;
	}

	const auto PlayerController = UGameplayStatics::GetPlayerController( World, 0 );
	if ( !PlayerController ) {
		UE_LOG( LogQuestSystem, Warning, TEXT( "PlayerController is null" ) );
		return nullptr;
	}

	return IQuestInterface::Execute_GetQuestComponent( PlayerController );
}

UInventoryComponent* UQuest::GetInventoryComponent() const {
	const auto World = GetWorld();
	if ( !IsValid( World ) ) {
		UE_LOG( LogQuestSystem, Warning, TEXT( "World is null" ) );
		return nullptr;
	}

	const auto PlayerController = UGameplayStatics::GetPlayerController( World, 0 );
	if ( !PlayerController ) {
		UE_LOG( LogQuestSystem, Warning, TEXT( "PlayerController is null" ) );
		return nullptr;
	}

	return IQuestInterface::Execute_GetInventoryComponent( PlayerController );
}

void UQuest::EvaluateStatus() {
	if ( !IsValid( Condition ) )
		return;

	const auto EvaluationResult = Condition->Evaluate();

	if ( Status == EvaluationResult )
		return;

	if ( EvaluationResult == EQuestStatus::Completed || EvaluationResult == EQuestStatus::Failed ) {
		Status = EvaluationResult;
		Notify_StatusChanged( this, Status );
	}
}

void UQuest::UpdateStatus(const EQuestStatus NewStatus) {
	if ( Status == NewStatus )
		return;

	if ( IsValid( Condition ) )
		if ( NewStatus == EQuestStatus::Active ) {
			Condition->Initialize();

			EvaluateStatus();

			if ( Status == EQuestStatus::Completed || Status == EQuestStatus::Failed )
				return;

			if ( !QuestComponent.IsValid() )
				QuestComponent = GetQuestComponent();

			QuestComponent->OnQuestStatusChanged.AddDynamic( this, &ThisClass::OnQuestStatusChanged );
		}

	Status = NewStatus;
	Notify_StatusChanged( this, Status );
}

void UQuest::OnQuestStatusChanged(UQuest* Quest, EQuestStatus NewStatus) {
	if ( NewStatus == EQuestStatus::Failed ) {
		UpdateStatus( EQuestStatus::Failed );
		return;
	}

	if ( Condition && Condition->Evaluate() == EQuestStatus::Completed )
		UpdateStatus( EQuestStatus::Completed );
}

UWorld* UQuest::GetWorld() const {
	if ( HasAllFlags( RF_ClassDefaultObject ) )
		return nullptr;

	for ( auto Outer = GetOuter(); Outer; Outer = Outer->GetOuter() ) {
		if ( !Outer->IsValidLowLevelFast() )
			break;

		if ( UWorld* World = Outer->GetWorld() )
			return World;
	}
	return nullptr;
}

#if WITH_EDITOR
FColor UQuest::GetColorBasedOnStatus(const EQuestStatus NewStatus) {
	switch ( NewStatus ) {
		case EQuestStatus::NotStarted:
			return FColor::Magenta;
		case EQuestStatus::Active:
			return FColor::White;

		case EQuestStatus::Completed:
			return FColor::Green;
		case EQuestStatus::Failed:
			return FColor::Red;
		default:
			return FColor::Black;
	}
}

void UQuest::PostDuplicate(bool bDuplicateForPIE) {
	UObject::PostDuplicate( bDuplicateForPIE );

	Id = FGuid::NewGuid();
}

#endif
