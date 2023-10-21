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
	None,
	Item,
	Skill
};

UENUM(BlueprintType)
enum class EQuickSlotKey : uint8
{
	NumberKey1,
	NumberKey2,
	NumberKey3,
	NumberKey4,
	NumberKey5,
	NumberKey6,
	NumberKey7,
	NumberKey8,
	NumberKey9,
	NumberKey0,
};

UENUM(BlueprintType)
enum class EObjectiveType : uint8
{
	Hunting,
	Collection,
	Deliver,
};