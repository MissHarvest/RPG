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

	UPROPERTY(VisibleAnywhere)
	class UDataTable* ItemDataTable;

	UPROPERTY(VisibleAnywhere)
	class UDataTable* NPCQuestTable;

	UPROPERTY(VisibleAnywhere)
	class UDataTable* QuestTable;

	UPROPERTY(VisibleAnywhere)
	class UDataTable* MonsterTable;

private:
	/*  */
	TArray<FItemSlot> GetItemListFromString(FString String);

	/*  */
	TArray<FObjective> GetObjectivesFromString(FString String);

public:
	UMyGameInstance();

public:
	/*  */
	TArray<EQuestState> GetPlayerQuestState(FName PID);

	/*  */
	FItemSlot GetItem(FName IID);

	/*  */
	TArray<FQuest> GetNPCQuest(FName NID);

	/*  */
	TArray<FQuest> GetNoneClearQuest(TArray<FQuest> NPCQuest, FName PID);

	/*  */
	FQuest GetQuest(FName QID);
};
