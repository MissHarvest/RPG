// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC.h"

// Components
#include "QuestGiver.h"

// Sets default values
ANPC::ANPC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	QuestGiver = CreateDefaultSubobject<UQuestGiver>(TEXT("Quest Giver"));
}

// Called when the game starts or when spawned
void ANPC::BeginPlay()
{
	Super::BeginPlay();
	
}

void ANPC::Interact()
{
	// QuestGiver->ShowQuestPanel();
}