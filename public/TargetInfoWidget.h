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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "", meta = (BindWidget, AllowPrivateAccess = "true"))
	class UTextBlock* LvText;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "", meta= (BindWidget, AllowPrivateAccess = "true"))
	class UTextBlock* NameText;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "", meta = (BindWidget, AllowPrivateAccess = "true"))
	class UProgressBar* HpBar;

	UPROPERTY()
	class AEnemyCharacter* Enemy;

public:
	void SetInfo(class AActor* EnemyActor);

	UFUNCTION()
	void SetHpPercent(float Percent);
};
