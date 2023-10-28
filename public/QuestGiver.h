// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CustomStruct.h"
#include "Components/ActorComponent.h"
#include "QuestGiver.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RPG_API UQuestGiver : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<FQuest> Quest;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UQuestReceiver* QuestReceiver;

public:	
	// Sets default values for this component's properties
	UQuestGiver();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	/*  */
	void SetRecevier(class UQuestReceiver* Receiver);

	/*  */
	TArray<FQuest> GetQuestList();
};
