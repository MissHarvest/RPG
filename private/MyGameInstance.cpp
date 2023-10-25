// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

UMyGameInstance::UMyGameInstance()
{
	ConstructorHelpers::FObjectFinder<UDataTable> DT_PlayerQuestState(TEXT("/Script/Engine.DataTable'/Game/Data/DT_PlayerQuestList.DT_PlayerQuestList'"));
	if (DT_PlayerQuestState.Succeeded())
	{
		PlayerQuestStateTable = DT_PlayerQuestState.Object;
	}
}

TArray<EQuestState> UMyGameInstance::GetPlayerQuestState(FName PID)
{
	TArray<EQuestState> OutArray;

	if (PlayerQuestStateTable)
	{
		auto PlayerQuestState = PlayerQuestStateTable->FindRow<FPlayerQuest>(PID, TEXT(""))->Quest;
		TArray<FString> TempArray;
		PlayerQuestState.ParseIntoArray(TempArray, TEXT(","));

		for (int i = 0; i < TempArray.Num(); ++i)
		{
			OutArray.Emplace(EQuestState((uint8)FCString::Atoi(*TempArray[i])));
		}
	}

	return OutArray;
}