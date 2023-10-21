// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC.h"

// Components
#include "QuestGiver.h"
#include <Components/SphereComponent.h>

// Sets default values
ANPC::ANPC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	QuestGiver = CreateDefaultSubobject<UQuestGiver>(TEXT("Quest Giver"));

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("Interact Range"));
	SphereComp->SetupAttachment(RootComponent);
	
}

// Called when the game starts or when spawned
void ANPC::BeginPlay()
{
	Super::BeginPlay();
	SphereComp->OnComponentEndOverlap.AddDynamic(this, &ANPC::CloseWidget);
}

// 상호작용도 종류가 있다.
// 줍기 - 자신이 들어갈 인벤토리 ?
// 퀘스트 - 리시버
// 
void ANPC::ReceiveQuest(class UQuestReceiver* Receiver)
{
	QuestGiver->ShowQuestPanel();
	QuestGiver->SetRecevier(Receiver);
}

void ANPC::CloseWidget(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// Player 한테 주는게 맞을지도
	UE_LOG(LogTemp, Warning, TEXT("sdf"));
	QuestGiver->CloseQuestGiverWidget();
}