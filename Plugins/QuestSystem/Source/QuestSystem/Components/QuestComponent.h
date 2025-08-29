// Copyright Ebrahim Mottaghi Rezaei [https://www.linkedin.com/in/ebrahim-mr/]. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "QuestSystem/DataTypes/Delegates.h"
#include "QuestSystem/DataTypes/Enums.h"
#include "QuestComponent.generated.h"

class UQuest;

UCLASS( ClassGroup=(QuestTask), meta=(BlueprintSpawnableComponent) )
class QUESTSYSTEM_API UQuestComponent : public UActorComponent {
	GENERATED_BODY()

public:
#pragma region event OnQuestAdded

protected:
	UFUNCTION( BlueprintImplementableEvent, Category = "Events", DisplayName="QuestAdded" )
	// ReSharper disable once CppUEBlueprintImplementableEventNotImplemented
	void K2_QuestAdded(UQuest* Quest);

	UFUNCTION( BlueprintCallable, Category="QuestComponent" )
	void Notify_QuestAdded(UQuest* Quest) {
		OnQuestAdded.Broadcast( Quest );
		K2_QuestAdded( Quest );
	}

public:
	UPROPERTY( BlueprintCallable, BlueprintAssignable, Category="Event" )
	FQuestAddedDelegate OnQuestAdded;
#pragma endregion
#pragma region event OnQuestStatusChanged

protected:
	UFUNCTION( BlueprintImplementableEvent, Category = "Events", DisplayName="QuestStatusChanged" )
	// ReSharper disable once CppUEBlueprintImplementableEventNotImplemented
	void K2_QuestStatusChanged(UQuest* Quest, EQuestStatus NewStatus);

	UFUNCTION( BlueprintCallable, Category="QuestComponent" )
	void Notify_QuestStatusChanged(UQuest* Quest, EQuestStatus NewStatus) {
		OnQuestStatusChanged.Broadcast( Quest, NewStatus );
		K2_QuestStatusChanged( Quest, NewStatus );
	}

public:
	UPROPERTY( BlueprintCallable, BlueprintAssignable, Category="Event" )
	FQuestStatusChangedDelegate OnQuestStatusChanged;
#pragma endregion

	UQuestComponent();

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void BeginDestroy() override;

protected:
	UPROPERTY( BlueprintReadOnly, Category="QuestComponent" )
	TMap<FGuid, UQuest*> ActiveQuests;

public:
	UFUNCTION( BlueprintCallable, Category="QuestComponent" )
	void AddQuest(TSubclassOf<UQuest> Quest);

	UFUNCTION( BlueprintCallable, Category="QuestComponent" )
	void UpdateQuestStatus(TSubclassOf<UQuest> Quest, EQuestStatus Status);

	UFUNCTION( BlueprintCallable, Category="QuestComponent" )
	EQuestStatus GetQuestStatus(const FGuid& QuestId) const;

	void RemoveQuestStatusChangeBinding(UQuest* Quest);

protected:
	UFUNCTION()
	void QuestStatusChanged(UQuest* Quest, EQuestStatus NewStatus);

	void CleanUp();
};
