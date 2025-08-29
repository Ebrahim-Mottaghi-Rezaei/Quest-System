// Copyright Ebrahim Mottaghi Rezaei <https://www.linkedin.com/in/ebrahim-mr> 2025 All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "QuestSystem/DataTypes/Enums.h"
#include "Delegates.generated.h"

UCLASS( NotBlueprintable )
class QUESTSYSTEM_API UQuestDummy : public UObject {
	GENERATED_BODY()
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FQuestAddedDelegate, UQuest*, Quest );

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FQuestStatusChangedDelegate, UQuest*, Quest, EQuestStatus, NewStatus );

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FInventoryItemAddedDelegate, UGameplayItemData*, Item );

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FInventoryItemUpdatedDelegate, UGameplayItemData*, Item, uint8, Count );
