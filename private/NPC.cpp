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

	NID = "000001";

	QuestGiver = CreateDefaultSubobject<UQuestGiver>(TEXT("Quest Giver"));
	QuestGiver->LoadTable(TEXT("/Script/Engine.DataTable'/Game/Data/DT_NPCQuestList.DT_NPCQuestList'"), NID);

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("Interact Range"));
	SphereComp->SetupAttachment(RootComponent);
	
}

// Called when the game starts or when spawned
void ANPC::BeginPlay()
{
	Super::BeginPlay();
}

// ��ȣ�ۿ뵵 ������ �ִ�.
// �ݱ� - �ڽ��� �� �κ��丮 ?
// ����Ʈ - ���ù�
// 
TArray<FString> ANPC::ReceiveQuest(class UQuestReceiver* Receiver)
{
	//QuestGiver->SetRecevier(Receiver);
	return QuestGiver->GetQuestList();
}