// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemEffectManager.h"
#include "PlayerCharacter.h"
#include "StatComponent.h"

bool UItemEffectManager::PrintID(int32 ID, class APawn* OwingPawn)
{
	if (ID <= 0) return false;
	Cast<APlayerCharacter>(OwingPawn)->GetStatComponent()->RecoveryHp(10);
	return true;
}