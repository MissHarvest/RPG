// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CustomStruct.h"
#include "Blueprint/UserWidget.h"
#include "QuestGiverWidget.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API UQuestGiverWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Resource", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UQuestSelectorSlot> QuestSelectorWidgetClass;

	UPROPERTY()
	TArray<UQuestSelectorSlot*> QuestSelectors;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UVerticalBox* QuestListBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UQuestInformationWidget* QuestInformation;

public:
	/* Add Quest Widgets in ListBox */
	void AddQuest(TArray<FQuest> QuestList);

	/* Show Quest Information by name */
	void ShowQuestInformation(FText QuestName);
};
