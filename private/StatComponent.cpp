// Fill out your copyright notice in the Description page of Project Settings.


#include "StatComponent.h"
#include "Recovery.h"
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
	PrimaryComponentTick.bCanEverTick = true; // false 로 해도 되지 않을까

	// ...
}


// Called when the game starts
void UStatComponent::BeginPlay()
{
	Super::BeginPlay();

	// 
	Normal = NewObject<UNormalRecovery>(this, TEXT("Normal Recovery"));
	Tick = NewObject<UTickRecovery>(this, TEXT("Tick Recovery"));
	
	// 여기서 BroadCast 를 호출해도 될까?
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
	Normal->Recovery(CurrentHp, Amount, FBroadCastSingature::CreateUObject(this, &UStatComponent::BroadCastHpChange), 0);
}

void UStatComponent::RecoveryHp(int32 Amount, int32 Sec)
{
	Tick->Recovery(CurrentHp, Amount, FBroadCastSingature::CreateUObject(this, &UStatComponent::BroadCastHpChange), Sec);
}

void UStatComponent::RecoveryHp(int32 Amount, TScriptInterface<class IRecovery> RecoveryStrategy)
{
	RecoveryStrategy->Recovery(CurrentHp, Amount, FBroadCastSingature::CreateUObject(this, &UStatComponent::BroadCastHpChange), 0);
}