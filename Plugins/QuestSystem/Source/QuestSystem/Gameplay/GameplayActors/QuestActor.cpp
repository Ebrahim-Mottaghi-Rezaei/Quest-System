// Copyright Ebrahim Mottaghi Rezaei <https://www.linkedin.com/in/ebrahim-mr> 2025 All Rights Reserved. 

#include "QuestActor.h"

AQuestActor::AQuestActor() {
	PrimaryActorTick.bCanEverTick          = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	Quest = nullptr;
}
