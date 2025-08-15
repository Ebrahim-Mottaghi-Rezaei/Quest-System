// Copyright Ebrahim Mottaghi Rezaei [https://www.linkedin.com/in/ebrahim-mr/]. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Tickable.h"
#include "QuestSystem/QuestSystem.h"
#include "QuestSystem/Components/QuestComponent.h"
#include "QuestSystem/DataTypes/Delegates.h"
#include "QuestSystem/DataTypes/Enums.h"
#include "Quest.generated.h"

class UInventoryComponent;
class UQuestCondition;

UCLASS( Abstract, Blueprintable, EditInlineNew )
class QUESTSYSTEM_API UQuest : public UObject, public FTickableGameObject {
	GENERATED_BODY()

public:
#pragma region event OnStatusChanged

protected:
	UFUNCTION( BlueprintImplementableEvent, Category = "Events", DisplayName="StatusChanged" )
	// ReSharper disable once CppUEBlueprintImplementableEventNotImplemented
	void K2_StatusChanged(UQuest* Quest, EQuestStatus NewStatus);

	UFUNCTION( BlueprintCallable )
	FORCEINLINE void Notify_StatusChanged(UQuest* Quest, EQuestStatus NewStatus) {
#if WITH_EDITOR
		const auto Message = FString::Printf( TEXT( "Quest: %s state changed to: %s" ), *Name.ToString(), *StaticEnum<EQuestStatus>()->GetNameStringByValue( static_cast<int64>(NewStatus) ) );

		if ( GEngine ) {
			int key = GetTypeHash( Id );
			GEngine->AddOnScreenDebugMessage( key, 100.0f, GetColorBasedOnStatus( NewStatus ), *Message );
		}

		UE_LOG( LogQuestSystem, Verbose, TEXT("%s"), *Message );
#endif
		OnStatusChanged.Broadcast( Quest, NewStatus );
		K2_StatusChanged( Quest, NewStatus );
	}

public:
	UPROPERTY( BlueprintCallable, BlueprintAssignable, Category="Event" )
	FQuestStatusChangedDelegate OnStatusChanged;

#pragma endregion

	UQuest();

	virtual ~UQuest() override;

protected:
	UPROPERTY( BlueprintReadOnly/*, EditAnywhere*/ )
	FGuid Id;

	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	FText Name;

	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	FText GameplayText;

	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	UTexture2D* Icon;

	UPROPERTY( BlueprintReadOnly, VisibleAnywhere )
	EQuestStatus Status;

	UPROPERTY( BlueprintReadWrite, EditAnywhere, Instanced, meta=(editinlinenew, ShowInnerProperties, FullyExpand=true) )
	UQuestCondition* Condition;

	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly )
	bool bIsTickable;

	// FTickableGameObject interface
	virtual void Tick(float DeltaTime) override;

	UFUNCTION( BlueprintImplementableEvent, Category = "Quest" )
	void TickQuest(float DeltaTime);

	virtual TStatId GetStatId() const override {
		RETURN_QUICK_DECLARE_CYCLE_STAT( UQuest, STATGROUP_Tickables );
	}

	UFUNCTION( BlueprintCallable, Category = "Quest" )
	void SetTickEnabled(bool bEnabled);

	virtual bool IsTickable() const override {
		return bIsTickable;
	}

	virtual bool IsTickableWhenPaused() const override {
		return false;
	}

	virtual bool IsTickableInEditor() const override {
		return false;
	}

	UQuestComponent* GetQuestComponent() const;

	UInventoryComponent* GetInventoryComponent() const;

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

	FORCEINLINE EQuestStatus GetStatus() const {
		return Status;
	}

	UFUNCTION( BlueprintCallable, Category = "Quest" )
	virtual void UpdateStatus(EQuestStatus NewStatus);

protected:
	UFUNCTION()
	void OnQuestStatusChanged(UQuest* Quest, EQuestStatus NewStatus);

	virtual UWorld* GetWorld() const override;

#if WITH_EDITOR
	static FColor GetColorBasedOnStatus(EQuestStatus NewStatus);

	virtual void PostDuplicate(bool bDuplicateForPIE) override;
#endif

	UPROPERTY()
	TSoftObjectPtr<UQuestComponent> QuestComponent;
};
