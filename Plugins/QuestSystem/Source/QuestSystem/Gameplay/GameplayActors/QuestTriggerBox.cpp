// Copyright Ebrahim Mottaghi Rezaei [https://www.linkedin.com/in/ebrahim-mr/]. All Rights Reserved

#include "QuestTriggerBox.h"
#include "GameFramework/Pawn.h"
#include "Gameframework/PlayerController.h"
#include "QuestSystem/QuestSystem.h"
#include "QuestSystem/Components/QuestComponent.h"
#include "QuestSystem/Gameplay/QuestSystem/Quest.h"
#include "QuestSystem/Gameplay/QuestSystem/Interfaces/QuestInterface.h"

AQuestTriggerBox::AQuestTriggerBox() {
	PrimaryActorTick.bCanEverTick          = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	Action    = EQuestTriggerVolumeAction::Add;
	NewStatus = EQuestStatus::NotStarted;
	Quest     = nullptr;
}

void AQuestTriggerBox::NotifyActorBeginOverlap(AActor* OtherActor) {
	Super::NotifyActorBeginOverlap( OtherActor );

	if ( !IsValid( OtherActor ) ) {
		UE_LOG( LogQuestSystem, Warning, TEXT( "OtherActor is null" ) );
		return;
	}

	if ( !IsValid( Quest ) ) {
		UE_LOG( LogQuestSystem, Warning, TEXT( "Quest is null" ) );
		return;
	}

	if ( !OtherActor->IsA( APawn::StaticClass() ) )
		return;

	const auto Controller = Cast<APawn>( OtherActor )->GetController();
	if ( !IsValid( Controller ) ) {
		UE_LOG( LogQuestSystem, Log, TEXT("Controller is null.") )
		return;
	}

	const auto QuestComponent = IQuestInterface::Execute_GetQuestComponent( Controller );
	if ( !IsValid( QuestComponent ) ) {
		UE_LOG( LogQuestSystem, Log, TEXT("QuestComponent is null.") )
		return;
	}

	if ( Action == EQuestTriggerVolumeAction::Add )
		QuestComponent->AddQuest( Quest );
	else
		QuestComponent->UpdateQuestStatus( Quest, NewStatus );
}
