// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CustomStruct.h"
#include "Components/ActorComponent.h"
#include "QuestReceiver.generated.h"

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_TwoParams(FQuestUpdatedSignature, UQuestReceiver, OnUpdatedHaveQuest, int32, Index, FQuest, Quest);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RPG_API UQuestReceiver : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Quest", meta = (AllowPrivateAccess = "true"))
	TArray<FQuest> HaveQuest;

	//UPROPERTY(VisibleAnywhere, Category = "Quest")
	//TArray<EQuestState>* PlayerQuestState;

public:
	UPROPERTY()
	FQuestUpdatedSignature OnUpdatedHaveQuest;

public:	
	// Sets default values for this component's properties
	UQuestReceiver();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	/*  */
	void UpdateQuestProgress(FName Name);

	/* Add or Update HaveQuest */
	void AddOrUpdateQuest(FQuest Quest);
};
