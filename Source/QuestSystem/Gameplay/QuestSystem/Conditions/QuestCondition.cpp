// Copyright Ebrahim Mottaghi Rezaei <https://www.linkedin.com/in/ebrahim-mr>. All Rights Reserved.

#include "QuestCondition.h"

UQuestCondition::UQuestCondition() {}
UQuestCondition::~UQuestCondition() {}

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
