// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectiveSlot.h"
#include <Components/CheckBox.h>
#include <Components/TextBlock.h>

void UObjectiveSlot::SetObjective(FObjective Objective)
{
	QuestSummaryText->SetText(FText::FromString(Objective.Summary));	
	ObjectiveNameText->SetText(FText::FromString(Objective.Target));
	
	/* Format */
	FString temp;
	temp.Append("( ");
	temp.Append(FString::FromInt(Objective.ProgressCount));
	temp.Append(" / ");
	temp.Append(FString::FromInt(Objective.RequestedCount));
	temp.Append(" )");

	ProgressText->SetText(FText::FromString(temp));
}

void UObjectiveSlot::SetCheckBox(bool bCompleted)
{
	CompletedCheckBox->SetIsChecked(bCompleted);
}