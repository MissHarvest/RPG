// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CustomStruct.h"
#include "Blueprint/UserWidget.h"
#include "QuestInformationWidget.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API UQuestInformationWidget : public UUserWidget
{
	GENERATED_BODY()

	FName QuestID;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* QuestNameText;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* QuestContentText;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UButton* AcceptButton;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* ButtonText;

	UPROPERTY()
	class UQuestGiverWidget* QuestGiverWidget;

	// EQuestState - > QuestState : Stay > 작동, Accpet > 작동

	/* Quest Reward Variable */
public:
	/* Show Quest Information */
	void ShowQuest(FQuest Quest);

	/*  */
	void SetQuestGiver(class UQuestGiverWidget* QuestGiver);

	/*  */
	class UButton* GetAcceptButton() const { return AcceptButton; }
};
