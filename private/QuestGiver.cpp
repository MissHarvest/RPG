// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestGiver.h"

#include <Blueprint/UserWidget.h>
#include <Kismet/GameplayStatics.h>
#include <Blueprint/WidgetBlueprintLibrary.h>
// Sets default values for this component's properties
UQuestGiver::UQuestGiver()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// Load Quest Id List
	QuestIdList.Add(1);

	
}


// Called when the game starts
void UQuestGiver::BeginPlay()
{
	Super::BeginPlay();

	// ...
	FQuest temp;
	temp.Set(1);
	QuestList.Add(temp);
}


// Called every frame
void UQuestGiver::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UQuestGiver::ShowQuestPanel()
{
	if (nullptr == QuestPanelWidgetClass) return;
	
	QuestGiverWidget = CreateWidget<UUserWidget>(GetWorld(), QuestPanelWidgetClass);
	if (QuestGiverWidget)
	{
		auto PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		PlayerController->SetShowMouseCursor(true);
		UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(PlayerController, QuestGiverWidget);		
		QuestGiverWidget->AddToViewport();
	}
}