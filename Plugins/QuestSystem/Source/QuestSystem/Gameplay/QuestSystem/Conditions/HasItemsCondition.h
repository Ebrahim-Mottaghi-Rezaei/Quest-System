// Copyright Ebrahim Mottaghi Rezaei <https://www.linkedin.com/in/ebrahim-mr>. All Rights Reserved 2025. 

#pragma once

#include "CoreMinimal.h"
#include "QuestCondition.h"
#include "HasItemsCondition.generated.h"

struct FHasItemsConditionInfo;
class UGameplayItemData;

UCLASS( BlueprintType )
class QUESTSYSTEM_API UHasItemsCondition : public UQuestCondition {
	GENERATED_BODY()

public:
	UHasItemsCondition();

protected:
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Condition" )
	TArray<FHasItemsConditionInfo> RequiredItems;

public:
	FORCEINLINE TArray<FHasItemsConditionInfo> GetRequiredItems() const {
		return RequiredItems;
	}

	virtual EQuestStatus Evaluate_Implementation() override;
};
