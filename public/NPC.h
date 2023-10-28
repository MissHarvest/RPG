// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractionInterface.h"
#include "GameFramework/Character.h"
#include "NPC.generated.h"

UCLASS()
class RPG_API ANPC : public ACharacter, public IInteractionInterface
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UQuestGiver* QuestGiver;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class USphereComponent* SphereComp;

	UPROPERTY()
	FName NID;

public:
	// Sets default values for this character's properties
	ANPC();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/* Override Interface Function */
	virtual TArray<FQuest> ReceiveQuest(class UQuestReceiver* Receiver) override;

public:	


};
