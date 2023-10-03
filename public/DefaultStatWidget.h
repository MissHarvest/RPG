// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DefaultStatWidget.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API UDefaultStatWidget : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY()
	class UStatComponent* StatModel;

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UProgressBar* HpBar;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UProgressBar* MpBar;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* LvText;

protected:
	virtual void NativeOnInitialized() override;

private:
	UFUNCTION()
	void SetHpPercent(float Percent);

	UFUNCTION()
	void SetMpPercent(float Percent);
};
