// Copyright Ebrahim Mottaghi Rezaei <https://www.linkedin.com/in/ebrahim-mr> 2025 All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "QuestSystem/DataTypes/Delegates.h"
#include "InventoryComponent.generated.h"

class UGameplayItemData;
class UQuest;

UCLASS( ClassGroup=(QuestTask), meta=(BlueprintSpawnableComponent) )
class QUESTSYSTEM_API UInventoryComponent : public UActorComponent {
	GENERATED_BODY()

public:
#pragma region event OnItemAdded

protected:
	UFUNCTION( BlueprintImplementableEvent, Category = "Events", DisplayName="ItemAdded" )
	// ReSharper disable once CppUEBlueprintImplementableEventNotImplemented
	void K2_ItemAdded(UGameplayItemData* Item);

	UFUNCTION( BlueprintCallable, Category="InventoryComponent" )
	FORCEINLINE void Notify_ItemAdded(UGameplayItemData* Item) {
		OnItemAdded.Broadcast( Item );
		K2_ItemAdded( Item );
	}

public:
	UPROPERTY( BlueprintCallable, BlueprintAssignable, Category="Event" )
	FInventoryItemAddedDelegate OnItemAdded;
#pragma endregion

#pragma region event OnItemUpdated

protected:
	UFUNCTION( BlueprintImplementableEvent, Category = "Events", DisplayName="ItemUpdated" )
	// ReSharper disable once CppUEBlueprintImplementableEventNotImplemented
	void K2_ItemUpdated(UGameplayItemData* Item, uint8 Count);

	UFUNCTION( BlueprintCallable, Category="InventoryComponent" )
	FORCEINLINE void Notify_ItemUpdated(UGameplayItemData* Item, uint8 Count) {
		OnItemUpdated.Broadcast( Item, Count );
		K2_ItemUpdated( Item, Count );
	}

public:
	UPROPERTY( BlueprintCallable, BlueprintAssignable, Category="Event" )
	FInventoryItemUpdatedDelegate OnItemUpdated;
#pragma endregion
	UInventoryComponent();

protected:
	UPROPERTY( BlueprintReadOnly, Category="InventoryComponent" )
	TMap<FGuid, uint8> Inventory;

public:
	UFUNCTION( BlueprintCallable, Category="InventoryComponent" )
	void AddToInventory(UGameplayItemData* Item, int Count);

	UFUNCTION( BlueprintCallable, Category="InventoryComponent" )
	uint8 GetItemCount(UGameplayItemData* Item) const;

	UFUNCTION( BlueprintCallable, Category="InventoryComponent" )
	bool HasItem(UGameplayItemData* Item) const;
};
