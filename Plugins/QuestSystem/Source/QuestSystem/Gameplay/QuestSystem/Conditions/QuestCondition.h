// Copyright Ebrahim Mottaghi Rezaei <https://www.linkedin.com/in/ebrahim-mr> 2025 All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "QuestSystem/DataTypes/Enums.h"
#include "UObject/Object.h"
#include "QuestCondition.generated.h"

class UWorld;

UCLASS( Abstract, Blueprintable, EditInlineNew )
class QUESTSYSTEM_API UQuestCondition : public UObject {
	GENERATED_BODY()

	friend class UQuest;

public:
	UQuestCondition();

	virtual ~UQuestCondition() override;

protected:
	UFUNCTION( BlueprintnativeEvent, Category = "QuestCondition" )
	void Initialize();

	UFUNCTION( BlueprintCallable, BlueprintnativeEvent, Category = "QuestCondition" )
	EQuestStatus Evaluate();

	virtual UWorld* GetWorld() const override;
};
