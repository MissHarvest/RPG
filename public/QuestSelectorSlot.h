// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CustomStruct.h"
#include "Blueprint/UserWidget.h"
#include "QuestSelectorSlot.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API UQuestSelectorSlot : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* QuestNameText;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UButton* Button;

	UPROPERTY()
	class UQuestGiverWidget* QuestGiverWidget;
	
	int32 Index;

private:
	UFUNCTION()
	void OnClicked();

protected:
	virtual void NativeOnInitialized() override;

public:
	/*  */
	void Init(int32 IndexOfList, FString QuestName);

	/* Set Quest Giver Widget */
	void SetQuestGiver(class UQuestGiverWidget* QuestGiver);

	/*  */
	class UButton* GetButton() { return Button; } ;
};
