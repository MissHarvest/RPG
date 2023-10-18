// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	class UTextBlock* QuestName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UButton* Button;

	UPROPERTY()
	class UQuestGiverWidget* QuestGiverWidget;

private:
	UFUNCTION()
	void OnClicked();

protected:
	virtual void NativeOnInitialized() override;

public:
	/* Set Quest Name Label */
	void SetName(FName Name);

	/* Set Quest Giver Widget */
	void SetQuestGiver(class UQuestGiverWidget* QuestGiver);
};
