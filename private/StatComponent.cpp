// Fill out your copyright notice in the Description page of Project Settings.


#include "StatComponent.h"

// Sets default values for this component's properties
UStatComponent::UStatComponent()
	: Super()
	, CurrentHp(0)
	, MaxHp(100)
	, CurrentMp(0)
	, MaxMp(100)
	, CurrentXp(0)
	, MaxXp(100)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true; // false �� �ص� ���� ������

	// ...
}


// Called when the game starts
void UStatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	// ���⼭ BroadCast �� ȣ���ص� �ɱ�?
	CurrentHp = 50;
	
}


// Called every frame
void UStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

float UStatComponent::GetHpPercent()
{
	float Percent = (float)CurrentHp / (float)MaxHp;
	return Percent;
}

void UStatComponent::BroadCastHpChange()
{
	OnHpChanged.Broadcast(GetHpPercent());
}


void UStatComponent::RecoveryHp(int32 Amount)
{
	CurrentHp += Amount;
	if (CurrentHp > MaxHp) CurrentHp = MaxHp;
	BroadCastHpChange();
}

void UStatComponent::RecoveryHp(int32 Amount, int32 Sec)
{

}