// Copyright Ebrahim Mottaghi Rezaei <https://www.linkedin.com/in/ebrahim-mr>. All Rights Reserved 2025. 

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
