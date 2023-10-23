// Fill out your copyright notice in the Description page of Project Settings.


#include "StatComponent.h"
#include "Recovery.h"

#include "EnemyCharacter.h"
#include "EnemyAIController.h"

// Sets default values for this component's properties
UStatComponent::UStatComponent()
	: Super()
	, Level(1)
	, CurrentHp(0)
	, MaxHp(100)
	, CurrentMp(0)
	, MaxMp(100)
	, CurrentXp(0)
	, MaxXp(100)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true; // false 로 해도 되지 않을까

	auto MS = Cast<AEnemyCharacter>(GetOwner());
	if (MS)
	{
		auto Data = MS->GetData();
		Status = FStatus(Data);
	}
	

	// ...
}


// Called when the game starts
void UStatComponent::BeginPlay()
{
	Super::BeginPlay();

	// 
	CurrentHp = MaxHp;
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UStatComponent::ReceiveDamage);
}


// Called every frame
void UStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UStatComponent::ReceiveDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	CurrentHp -= Damage;
	UE_LOG(LogTemp, Warning, TEXT("Enemy Damaged / Stat"));
	auto Enemy = Cast<AEnemyCharacter>(GetOwner());
	if (nullptr == Enemy) return;

	auto Controller = Cast<AEnemyAIController>(Enemy->GetController());
	if (nullptr == Controller) return;
	
	UE_LOG(LogTemp, Warning, TEXT("Enemy Stat : nullptr is not exist => Do ReveiveDamage"));
	auto Player = InstigatedBy->GetPawn();
	Controller->ReceiveDamage(Player);

	BroadCastHpChange();
}

void UStatComponent::DecreaseHP(int32 Amount)
{
	CurrentHp -= Amount;
	BroadCastHpChange();
}

float UStatComponent::GetHpPercent()
{
	float Percent = (float)CurrentHp / (float)MaxHp;
	UE_LOG(LogTemp, Warning, TEXT("CurrentHP(%d), MaxHP(%d), Percent(%f)"), CurrentHp, MaxHp, Percent);
	return Percent;
}

float UStatComponent::GetMpPercent()
{
	float Percent = (float)CurrentMp / (float)MaxMp;
	return Percent;
}

float UStatComponent::GetXpPercent()
{
	float Percent = (float)CurrentXp / (float)MaxXp;
	return Percent;
}

void UStatComponent::BroadCastHpChange()
{
	OnHpChanged.Broadcast(GetHpPercent());
}

void UStatComponent::BroadCastMpChange()
{
	OnMpChanged.Broadcast(GetMpPercent());
}

void UStatComponent::BroadCastXpChange()
{
	OnXpChanged.Broadcast(GetXpPercent());
}

void UStatComponent::RecoveryHp(int32 Amount)
{
	TScriptInterface<IRecovery> RecoveryStrategy = NewObject<UNormalRecovery>();
	RecoveryStrategy->Recovery(CurrentHp, Amount, FBroadCastSingature::CreateUObject(this, &UStatComponent::BroadCastHpChange), 0);
	if (CurrentHp > MaxHp) CurrentHp = MaxHp;
}

void UStatComponent::RecoveryHp(int32 Amount, int32 Sec)
{
	TScriptInterface<IRecovery> RecoveryStrategy = NewObject<UTickRecovery>();
	RecoveryStrategy->Recovery(CurrentHp, Amount, FBroadCastSingature::CreateUObject(this, &UStatComponent::BroadCastHpChange), Sec);
	if (CurrentHp > MaxHp) CurrentHp = MaxHp;
}

void UStatComponent::RecoveryMp(int32 Amount)
{
	TScriptInterface<IRecovery> RecoveryStrategy = NewObject<UNormalRecovery>();
	RecoveryStrategy->Recovery(CurrentMp, Amount, FBroadCastSingature::CreateUObject(this, &UStatComponent::BroadCastMpChange), 0);
	if (CurrentMp > MaxMp) CurrentMp = MaxMp;
}

void UStatComponent::GainXp(int32 Amount)
{
	TScriptInterface<IRecovery> RecoveryStrategy = NewObject<UNormalRecovery>();
	RecoveryStrategy->Recovery(CurrentXp, Amount, FBroadCastSingature::CreateUObject(this, &UStatComponent::BroadCastXpChange), 0);
	if (CurrentXp > MaxXp) CurrentXp = MaxXp;
}
