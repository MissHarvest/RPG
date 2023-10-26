// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestInformationWidget.h"
#include <Components/TextBlock.h>
#include <Components/Button.h>
#include "QuestGiverWidget.h"
#include <Components/HorizontalBox.h>
#include "RewardSlot.h"

void UQuestInformationWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	AcceptButton->OnClicked.AddDynamic(this, &UQuestInformationWidget::OnClicked);
}

void UQuestInformationWidget::ShowQuest(FQuest Quest)
{
	QuestNameText->SetText(FText::FromString(Quest.GetName()));
	QuestContentText->SetText(FText::FromString(Quest.GetContent()));

	FString Label;
	switch (Quest.QuestState)
	{
	case EQuestState::Stay:
		Label = TEXT("수락");
		break;

	case EQuestState::Accept:
		Label = TEXT("포기");
		break;

	case EQuestState::CompleteStay:
		Label = TEXT("완료");
		break;
	}
	ButtonText->SetText(FText::FromString(Label));

	RewardBox->ClearChildren();
	auto Reward = Quest.GetReward();
	for (int i = 0; i < Reward.Num(); ++i)
	{
		if (RewardSlotClass)
		{
			auto RewardSlot = CreateWidget<URewardSlot>(GetWorld(), RewardSlotClass);
			RewardSlot->Init(Reward[i]);
			RewardBox->AddChild(RewardSlot);
		}
	}
}

void UQuestInformationWidget::SetQuestGiver(class UQuestGiverWidget* QuestGiver)
{
	QuestGiverWidget = QuestGiver;
}

void UQuestInformationWidget::OnClicked()
{
	QuestGiverWidget->SendToGiver();
}