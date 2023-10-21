// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CustomStruct.h"
#include "Blueprint/UserWidget.h"
#include "QuestSelectorSlot.generated.h"

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(FOnSelectedSignature, UQuestSelectorSlot, OnSelected, FName, QuestID);

/**
 * 
 */
UCLASS()
class RPG_API UQuestSelectorSlot : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* QuestName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UButton* Button;

	UPROPERTY()
	class UQuestGiverWidget* QuestGiverWidget;
	
	FName QuestID;

public:
	UPROPERTY()
	FOnSelectedSignature OnSelected;

private:
	UFUNCTION()
	void OnClicked();

protected:
	virtual void NativeOnInitialized() override;

public:
	/*  */
	void Init(FQuest Quest);

	/* Set Quest Giver Widget */
	void SetQuestGiver(class UQuestGiverWidget* QuestGiver);
};
