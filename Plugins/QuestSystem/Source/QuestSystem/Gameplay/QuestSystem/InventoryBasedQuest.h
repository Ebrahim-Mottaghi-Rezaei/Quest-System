// Copyright Ebrahim Mottaghi Rezaei <https://www.linkedin.com/in/ebrahim-mr>. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Quest.h"
#include "InventoryBasedQuest.generated.h"

class UGameplayItemData;

UCLASS()
class QUESTSYSTEM_API UInventoryBasedQuest : public UQuest {
	GENERATED_BODY()

public:
	UInventoryBasedQuest();

	virtual ~UInventoryBasedQuest() override;

protected:
	virtual void UpdateStatus(EQuestStatus NewStatus) override;

	bool CheckForRelevantItem(const UGameplayItemData* Item) const;

	UFUNCTION()
	void OnItemAddedToInventory(UGameplayItemData* Item);

	UFUNCTION()
	void OnItemUpdatedInInventory(UGameplayItemData* Item, uint8 Count);

	UPROPERTY()
	TSoftObjectPtr<UInventoryComponent> InventoryComponent;
};
