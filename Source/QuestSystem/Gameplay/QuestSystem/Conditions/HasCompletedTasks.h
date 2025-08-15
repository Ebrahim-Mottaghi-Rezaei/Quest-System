// Copyright Ebrahim Mottaghi Rezaei <https://www.linkedin.com/in/ebrahim-mr>. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "QuestCondition.h"
#include "HasCompletedTasks.generated.h"

class UQuest;

UCLASS()
class QUESTSYSTEM_API UHasCompletedTasks : public UQuestCondition {
	GENERATED_BODY()

public:
	UHasCompletedTasks();

protected:
	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	TArray<TSubclassOf<UQuest>> RequiredQuests;

	virtual EQuestStatus Evaluate_Implementation() override;
};
