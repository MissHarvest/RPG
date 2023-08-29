// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DamageWidget.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API UDamageWidget : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
	class UTextBlock* DamageText;
};
