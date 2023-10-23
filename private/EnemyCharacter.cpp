// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "StatComponent.h"
#include "DamageIndicatorComponent.h"

#include <Kismet/KismetSystemLibrary.h>
#include "InventorySystem.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MID = "000001";
	ConstructorHelpers::FObjectFinder<UDataTable> DTMonster(TEXT("/Script/Engine.DataTable'/Game/Data/DT_MonsterList.DT_MonsterList'"));
	if (DTMonster.Succeeded())
	{
		MonsterDataHandle.DataTable = DTMonster.Object;
		MonsterDataHandle.RowName = MID;
	}

	Name = MonsterDataHandle.DataTable->FindRow<FMonsterData>(MID, TEXT("Failed"))->Name;

	Stat = CreateDefaultSubobject<UStatComponent>(TEXT("Stat Component"));

	DamageIndicatorComp = CreateDefaultSubobject<UDamageIndicatorComponent>(TEXT("Damage Indicator"));
	UE_LOG(LogTemp, Warning, TEXT("Enemy Constructor"));

	TestInven = CreateDefaultSubobject<UInventorySystem>(TEXT("TEST"));

	

}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Enemy BeginPlay"));
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AEnemyCharacter::Attack()
{	
	UE_LOG(LogTemp, Warning, TEXT("BT_AI_ENEMY_Attack!!"));
	return PlayAnimMontage(AttackMontage);	
}

float AEnemyCharacter::Damaged()
{
	return PlayAnimMontage(DamagedMontage);
}

float AEnemyCharacter::Death()
{
	UE_LOG(LogTemp, Warning, TEXT("Death"));
	//FString temp("더미");
	OnDeath.Broadcast(MID);
	GetMesh()->SetSimulatePhysics(true);
	return 0;
}

void AEnemyCharacter::BroadCastAttackEnd()
{
	if(OnAttackEnd.IsBound())
		OnAttackEnd.Broadcast();
}

FMonsterData* AEnemyCharacter::GetData() 
{
	return MonsterDataHandle.DataTable->FindRow<FMonsterData>(MID, TEXT("Failed"));
}