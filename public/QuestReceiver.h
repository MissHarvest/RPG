// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CustomStruct.h"
#include "Components/ActorComponent.h"
#include "QuestReceiver.generated.h"

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_TwoParams(FQuestUpdatedSignature, UQuestReceiver, OnQuestUpdated, int32, Index, FQuest, Quest);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RPG_API UQuestReceiver : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TArray<FQuest> HaveQuest;

public:
	UPROPERTY()
	FQuestUpdatedSignature OnQuestUpdated;

public:	
	// Sets default values for this component's properties
	UQuestReceiver();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/*  */
	void ReceiveQuest(FQuest Quest);
		
	/*  */
	void UpdateQuestProgress(FName Name);
};
