// Copyright Ebrahim Mottaghi Rezaei [https://www.linkedin.com/in/ebrahim-mr/]. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "QuestInterface.generated.h"

class UInventoryComponent;
class UQuestComponent;

UINTERFACE()
class UQuestInterface : public UInterface {
	GENERATED_BODY()
};

class QUESTSYSTEM_API IQuestInterface {
	GENERATED_BODY()

public:
	UFUNCTION( BlueprintCallable, BlueprintNativeEvent, Category="Quest Interface" )
	UInventoryComponent* GetInventoryComponent();

	UFUNCTION( BlueprintCallable, BlueprintNativeEvent, Category="Quest Interface" )
	UQuestComponent* GetQuestComponent();
};
