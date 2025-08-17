// Copyright Ebrahim Mottaghi Rezaei <https://www.linkedin.com/in/ebrahim-mr>. All Rights Reserved.

#include "InventoryComponent.h"
#include "QuestSystem/DataAssets/GameplayItemData.h"

UInventoryComponent::UInventoryComponent() {
	PrimaryComponentTick.bCanEverTick          = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;
}

void UInventoryComponent::AddToInventory(UGameplayItemData* Item, int Count) {
	const auto Id        = Item->GetId();
	const auto FoundItem = Inventory.Find( Id );
	if ( FoundItem == nullptr ) {
		Inventory.Add( Id, Count );
		Notify_ItemAdded( Item );
	} else {
		*FoundItem += Count;
		Notify_ItemUpdated( Item, *FoundItem );
	}
}

uint8 UInventoryComponent::GetItemCount(UGameplayItemData* Item) const {
	return Inventory.FindRef( Item->GetId() );
}

bool UInventoryComponent::HasItem(UGameplayItemData* Item) const {
	return Inventory.FindRef( Item->GetId() ) > 0;
}
