// Copyright Ebrahim Mottaghi Rezaei <https://www.linkedin.com/in/ebrahim-mr> 2025 All Rights Reserved. 

#include "GameplayItemData.h"
#include "Engine/Texture2D.h"

UGameplayItemData::UGameplayItemData() {
	Id           = FGuid::NewGuid();
	Name         = FText::FromString( TEXT( "Name" ) );
	GameplayText = FText::FromString( TEXT( "Gameplay" ) );
	Icon         = nullptr;
}

#if WITH_EDITOR
void UGameplayItemData::PostDuplicate(bool bDuplicateForPIE) {
	UObject::PostDuplicate( bDuplicateForPIE );

	Id = FGuid::NewGuid();
}

#endif
