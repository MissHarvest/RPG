// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageIndicatorComponent.h"
#include "DamageIndicator.h"

// Sets default values for this component's properties
UDamageIndicatorComponent::UDamageIndicatorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDamageIndicatorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	auto OwingActor = GetOwner();
	if (nullptr == OwingActor) return;
	
	OwingActor->OnTakeAnyDamage.AddDynamic(this, &UDamageIndicatorComponent::SpawnDamageIndicator);
}


// Called every frame
void UDamageIndicatorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UDamageIndicatorComponent::SpawnDamageIndicator(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	if (IsValid(DamageIndicatorClass))
	{
		auto DamageIndicator = GetWorld()->SpawnActorDeferred<ADamageIndicator>(DamageIndicatorClass, GetOwner()->GetActorTransform());
		if (nullptr != DamageIndicator)
		{
			DamageIndicator->SetDamage(Damage);
			DamageIndicator->FinishSpawning(GetOwner()->GetActorTransform());
		}
	}
}