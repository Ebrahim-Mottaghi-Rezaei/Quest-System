// Copyright Ebrahim Mottaghi Rezaei <https://www.linkedin.com/in/ebrahim-mr> 2025 All Rights Reserved. 

#include "HasCompletedTasks.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "QuestSystem/QuestSystem.h"
#include "QuestSystem/Components/QuestComponent.h"
#include "QuestSystem/Gameplay/QuestSystem/Quest.h"
#include "QuestSystem/Gameplay/QuestSystem/Interfaces/QuestInterface.h"

UHasCompletedTasks::UHasCompletedTasks() {}

EQuestStatus UHasCompletedTasks::Evaluate_Implementation() {
	const auto PlayerController = UGameplayStatics::GetPlayerController( GetWorld(), 0 );
	if ( !IsValid( PlayerController ) ) {
		UE_LOG( LogQuestSystem, Warning, TEXT("PlayerController is null.") );
		return EQuestStatus::Failed;
	}

	const auto QuestComponent = IQuestInterface::Execute_GetQuestComponent( PlayerController );
	if ( !IsValid( QuestComponent ) ) {
		UE_LOG( LogQuestSystem, Warning, TEXT("InventoryComponent is null.") );
		return EQuestStatus::Failed;
	}

	bool bNotStarted = true;
	bool bCompleted  = true;
	bool bFailed     = false;
	for ( const auto RequiredItem : RequiredQuests ) {
		const auto CurrentStatus = QuestComponent->GetQuestStatus( RequiredItem.GetDefaultObject()->GetId() );

		switch ( CurrentStatus ) {
			case EQuestStatus::NotStarted:
			case EQuestStatus::Active:
				bNotStarted = false;
				bCompleted = false;
				break;
			case EQuestStatus::Failed:
				bFailed = true;
				break;
			default: ;
		}

		if ( bFailed )
			return EQuestStatus::Failed;
	}

	if ( bCompleted )
		return EQuestStatus::Completed;

	if ( bNotStarted )
		return EQuestStatus::NotStarted;

	return EQuestStatus::Active;
}
