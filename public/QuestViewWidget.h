// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CustomStruct.h"
#include "Blueprint/UserWidget.h"
#include "QuestViewWidget.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API UQuestViewWidget : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UQuestSlot> QuestProgressWidgetClass;

	UPROPERTY()
	TArray<class UQuestSlot*> QuestWidgets;

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UVerticalBox* QuestList;

private:
	UFUNCTION()
	void UpdateQuestViewer(int32 Index, FQuest Quest);

protected:
	virtual void NativeOnInitialized() override;


};
