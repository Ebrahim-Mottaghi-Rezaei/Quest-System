// Copyright Ebrahim Mottaghi Rezaei [https://www.linkedin.com/in/ebrahim-mr/]. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Structs.generated.h"

class UGameplayItemData;

USTRUCT( BlueprintType, Category = "Quest System" )
struct QUESTSYSTEM_API FBaseStruct {
	GENERATED_BODY()

public:
	virtual ~FBaseStruct() = default;

	FBaseStruct();

	virtual FString ToString();
};

USTRUCT( BlueprintType, Category = "Quest System" )
struct QUESTSYSTEM_API FQuestInfo : public FBaseStruct {
	GENERATED_BODY()

public:
	FQuestInfo();

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Quest Info" )
	FGuid Id;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Quest Info" )
	FText Name;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Quest Info" )
	FText Description;
};

USTRUCT( BlueprintType, Category = "Quest System" )
struct QUESTSYSTEM_API FHasItemsConditionInfo : public FBaseStruct {
	GENERATED_BODY()

public:
	FHasItemsConditionInfo();

	UPROPERTY( BlueprintReadWrite, EditAnywhere, Category = "Has Item Condition Info" )
	UGameplayItemData* Item;
	UPROPERTY( BlueprintReadWrite, EditAnywhere, Category = "Has Item Condition Info" )
	uint8 Count;
};
