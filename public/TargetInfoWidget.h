// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TargetInfoWidget.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API UTargetInfoWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY()
	class AEnemyCharacter* Enemy;

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* MonsterLvText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* MonsterNameText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UProgressBar* MonsterHpBar;

public:
	void SetInfo(class AActor* EnemyActor);

	UFUNCTION()
	void SetHpPercent(float Percent);
};
