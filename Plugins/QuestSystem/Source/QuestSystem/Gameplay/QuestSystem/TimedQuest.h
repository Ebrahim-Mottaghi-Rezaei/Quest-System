// Copyright Ebrahim Mottaghi Rezaei <https://www.linkedin.com/in/ebrahim-mr>. All Rights Reserved 2025. 

#pragma once

#include "CoreMinimal.h"
#include "Quest.h"
#include "TimedQuest.generated.h"

UCLASS()
class QUESTSYSTEM_API UTimedQuest : public UQuest {
	GENERATED_BODY()

public:
	UTimedQuest();

protected:
	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category="Timed Quest" )
	float ExpirationDelay = 10.f;
	UPROPERTY( VisibleInstanceOnly, BlueprintReadOnly, Category="Timed Quest" )
	float RemainingTime = 0.f;

	virtual void Tick(float DeltaTime) override;

	virtual void UpdateStatus(EQuestStatus NewStatus) override;
};
