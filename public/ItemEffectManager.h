// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ItemEffectManager.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API UItemEffectManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	bool PrintID(int32 ID, class APawn* OwingPawn);
};
