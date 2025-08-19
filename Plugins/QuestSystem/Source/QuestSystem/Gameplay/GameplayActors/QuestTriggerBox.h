// Copyright Ebrahim Mottaghi Rezaei [https://www.linkedin.com/in/ebrahim-mr/]. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "QuestSystem/DataTypes/Enums.h"
#include "QuestTriggerBox.generated.h"

class UQuest;

UCLASS()
class QUESTSYSTEM_API AQuestTriggerBox : public ATriggerBox {
	GENERATED_BODY()

public:
	AQuestTriggerBox();

protected:
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Quest Trigger Box" )
	EQuestTriggerVolumeAction Action;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Quest Trigger Box" )
	TSubclassOf<UQuest> Quest;
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Quest Trigger Box", meta=(EditCondition="Action == EQuestTriggerVolumeAction::Update", EditConditionHides) )
	EQuestStatus NewStatus;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};
