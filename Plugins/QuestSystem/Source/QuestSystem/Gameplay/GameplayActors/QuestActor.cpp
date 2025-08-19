// Copyright Ebrahim Mottaghi Rezaei <https://www.linkedin.com/in/ebrahim-mr>. All Rights Reserved 2025. 

#include "QuestActor.h"

AQuestActor::AQuestActor() {
	PrimaryActorTick.bCanEverTick          = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	Quest = nullptr;
}
