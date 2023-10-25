// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestSlot.h"
#include <Components/TextBlock.h>
#include "ObjectiveSlot.h"
#include <Components/VerticalBox.h>

void UQuestSlot::SetQuest(FQuest Quest)
{
	ObjectiveListBox->ClearChildren();

	QuestNameText->SetText(FText::FromString(Quest.GetName()));
	
	TArray<FObjective> Objectives = Quest.GetObjectives();
	for (int i = 0; i < Objectives.Num(); ++i)
	{
		AddObjective(Objectives[i]);
	}	
}

void UQuestSlot::AddObjective(FObjective Objective)
{
	if (ObjectiveSlotClass)
	{
		auto ObjectiveSlot = CreateWidget<UObjectiveSlot>(GetOwningPlayer(), ObjectiveSlotClass);
		ObjectiveSlot->SetObjective(Objective);
		ObjectiveSlot->SetCheckBox(Objective.bCompleted);
		ObjectiveListBox->AddChild(ObjectiveSlot);
	}
}