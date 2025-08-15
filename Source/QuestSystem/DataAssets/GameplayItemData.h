// Copyright Ebrahim Mottaghi Rezaei <https://www.linkedin.com/in/ebrahim-mr>. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayItemData.generated.h"

UCLASS(Blueprintable)
class QUESTSYSTEM_API UGameplayItemData : public UDataAsset {
	GENERATED_BODY()

public:
	UGameplayItemData();

protected:
	UPROPERTY( BlueprintReadOnly, VisibleAnywhere )
	FGuid Id;

	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	FText Name;

	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	FText GameplayText;

	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	UTexture2D* Icon;

#if WITH_EDITOR
	virtual void PostDuplicate(bool bDuplicateForPIE) override;
#endif

public:
	FORCEINLINE FGuid GetId() const {
		return Id;
	}

	FORCEINLINE FText GetItemName() const {
		return Name;
	}

	FORCEINLINE FText GetGameplayText() const {
		return GameplayText;
	}
};
