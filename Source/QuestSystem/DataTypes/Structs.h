// Copyright Ebrahim Mottaghi Rezaei [https://www.linkedin.com/in/ebrahim-mr/]. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Structs.generated.h"

class UGameplayItemData;

USTRUCT( BlueprintType, Category = "DataTypes" )
struct QUESTSYSTEM_API FBaseStruct {
	GENERATED_BODY()

public:
	virtual ~FBaseStruct() = default;

	FBaseStruct();

	virtual FString ToString();
};

USTRUCT( BlueprintType, Category = "DataTypes" )
struct QUESTSYSTEM_API FQuestInfo : public FBaseStruct {
	GENERATED_BODY()

public:
	FQuestInfo();

	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	FGuid Id;

	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	FText Name;

	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	FText Description;
};

USTRUCT( BlueprintType, Category = "DataTypes" )
struct QUESTSYSTEM_API FHasItemsConditionInfo : public FBaseStruct {
	GENERATED_BODY()

public:
	FHasItemsConditionInfo();

	UPROPERTY( BlueprintReadWrite, EditAnywhere )
	UGameplayItemData* Item;
	UPROPERTY( BlueprintReadWrite, EditAnywhere )
	uint8 Count;
};
