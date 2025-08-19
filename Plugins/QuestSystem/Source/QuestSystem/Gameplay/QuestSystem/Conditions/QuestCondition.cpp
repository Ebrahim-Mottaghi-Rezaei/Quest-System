// Copyright Ebrahim Mottaghi Rezaei <https://www.linkedin.com/in/ebrahim-mr>. All Rights Reserved 2025. 

#include "QuestCondition.h"

UQuestCondition::UQuestCondition() {}

UQuestCondition::~UQuestCondition() {}

void UQuestCondition::Initialize_Implementation() {}

UWorld* UQuestCondition::GetWorld() const {
	if ( HasAllFlags( RF_ClassDefaultObject ) )
		return nullptr;

	auto Outer = GetOuter();

	while ( Outer->IsValidLowLevelFast() ) {
		if ( const auto World = Outer->GetWorld() )
			return World;

		Outer = Outer->GetOuter();
	}

	return nullptr;
}

EQuestStatus UQuestCondition::Evaluate_Implementation() {
	return EQuestStatus::Active;
}
