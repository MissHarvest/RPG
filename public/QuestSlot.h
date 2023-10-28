// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CustomStruct.h"
#include "Blueprint/UserWidget.h"
#include "QuestSlot.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API UQuestSlot : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UObjectiveSlot> ObjectiveSlotClass;

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* QuestNameText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UVerticalBox* ObjectiveListBox;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* QuestSummaryText;

private:
	/*  */
	void AddObjective(FObjective Objective);

public:
	/*  */
	void SetQuest(FQuest Quest);


};
