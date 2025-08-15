// Copyright Ebrahim Mottaghi Rezaei [https://www.linkedin.com/in/ebrahim-mr/]. All Rights Reserved
#pragma once

#include "CoreMinimal.h"
#include "Enums.generated.h"

UENUM( BlueprintType )
enum class EQuestStatus : uint8 {
	NotStarted, Active, Completed, Failed
};

UENUM( BlueprintType )
enum class EQuestTriggerVolumeAction : uint8 {
	Add, Update
};
