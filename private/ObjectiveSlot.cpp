// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectiveSlot.h"
#include <Components/CheckBox.h>
#include <Components/TextBlock.h>

void UObjectiveSlot::SetObjective(FObjective Objective)
{
	QuestSummaryText->SetText(FText::FromString(Objective.ObjectiveName));	
	FMargin Margin;
}