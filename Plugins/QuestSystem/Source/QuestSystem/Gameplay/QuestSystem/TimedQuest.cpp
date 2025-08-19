// Copyright Ebrahim Mottaghi Rezaei <https://www.linkedin.com/in/ebrahim-mr>. All Rights Reserved 2025. 

#include "TimedQuest.h"

UTimedQuest::UTimedQuest() {}

void UTimedQuest::Tick(float DeltaTime) {
	Super::Tick( DeltaTime );

	RemainingTime -= DeltaTime;
	if ( RemainingTime <= 0.f ) {
		SetTickEnabled( false );

		UpdateStatus( EQuestStatus::Failed );
	}
}

void UTimedQuest::UpdateStatus(EQuestStatus NewStatus) {
	Super::UpdateStatus( NewStatus );

	if ( NewStatus == EQuestStatus::Active ) {
		RemainingTime = ExpirationDelay;
		SetTickEnabled( true );
	} else if ( NewStatus != EQuestStatus::NotStarted )
		SetTickEnabled( false );
}
