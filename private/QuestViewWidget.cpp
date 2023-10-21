// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestViewWidget.h"
#include "PlayerCharacter.h"
#include "QuestReceiver.h"
#include <Components/VerticalBox.h>
#include "QuestSlot.h"

void UQuestViewWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	//NativeOnInitialized
	auto QuestReceiver = Cast<APlayerCharacter>(GetOwningPlayerPawn())->GetQuestReceiver();
	QuestReceiver->OnQuestUpdated.AddDynamic(this, &UQuestViewWidget::UpdateQuestViewer);
}

void UQuestViewWidget::UpdateQuestViewer(int32 Index, FQuest Quest)
{
	UE_LOG(LogTemp, Warning, TEXT("UpdateQuestViewer %d/%d"), Index, QuestWidgets.Num());
	if (Index > QuestWidgets.Num()) return;
	else if (Index == QuestWidgets.Num())
	{
		// Create Widget 
		auto QuestWidget = CreateWidget<UQuestSlot>(GetOwningPlayer(), QuestProgressWidgetClass);
		// Set Detail
		//QuestWidgets.Add(QuestWidget);
		
		QuestWidget->SetPadding(8);
		QuestWidget->SetQuest(Quest);
		QuestList->AddChild(QuestWidget);
		
		//QuestList->GetChildAt()
		// QuestWidget
	}
	else
	{
		// Access Widget

		// Set Detail
	}
}
