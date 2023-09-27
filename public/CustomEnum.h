// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CustomEnum.generated.h"

UCLASS()
class RPG_API ACustomEnum : public AActor
{
	GENERATED_BODY()
};

UENUM(BlueprintType)
enum class ESlotType : uint8
{
	Item,
	Skill
};

