// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CustomStruct.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere)
	class UDataTable* PlayerQuestStateTable;


public:
	UMyGameInstance();

public:
	/*  */
	TArray<EQuestState> GetPlayerQuestState(FName PID);
};
