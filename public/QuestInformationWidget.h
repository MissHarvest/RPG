// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CustomStruct.h"
#include "Blueprint/UserWidget.h"
#include "QuestInformationWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(FOnAccpetSignature, UQuestInformationWidget, OnAccepted, FName, QuestID);

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

	UPROPERTY()
	class UQuestGiverWidget* QuestGiverWidget;

	/* Quest Reward Variable */
public:
	UPROPERTY()
	FOnAccpetSignature OnAccepted;

private:
	/*  */
	UFUNCTION()
	void ClickAccpetButton();

public:
	/* Show Quest Information by Name */
	void ShowQuest(FName QuestID);

	/*  */
	void SetQuestGiver(class UQuestGiverWidget* QuestGiver);
};
