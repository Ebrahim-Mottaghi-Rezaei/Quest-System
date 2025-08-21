// Copyright Ebrahim Mottaghi Rezaei <https://www.linkedin.com/in/ebrahim-mr> 2025 All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "QuestActor.generated.h"

class UQuest;

UCLASS( Blueprintable )
class QUESTSYSTEM_API AQuestActor : public AActor {
	GENERATED_BODY()

public:
	AQuestActor();

protected:
	UPROPERTY( BlueprintReadOnly, EditInstanceOnly, Category="Quest Actor" )
	TSubclassOf<UQuest> Quest;
};
