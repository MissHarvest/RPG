// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CustomStruct.h"
#include "Blueprint/UserWidget.h"
#include "ObjectiveSlot.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API UObjectiveSlot : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* ObjectiveNameText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UCheckBox* CompletedCheckBox;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* ProgressText;

public:
	/*  */
	void SetObjective(FObjective Objective);

	/*  */
	void SetCheckBox(bool bCompleted);
};
