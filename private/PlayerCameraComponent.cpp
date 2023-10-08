// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCameraComponent.h"

#include <Kismet/KismetSystemLibrary.h>
#include <Kismet/KismetMathLibrary.h>

#include <GameFramework/Controller.h>

void UPlayerCameraComponent::BeginPlay()
{
	Super::BeginPlay();
	this->SetTickGroup(ETickingGroup::TG_PostUpdateWork);
}

void UPlayerCameraComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	ChaseTarget();
}

void UPlayerCameraComponent::ChaseTarget()
{
	if (nullptr == TargetActor) return;

	auto LookRotation = UKismetMathLibrary::FindLookAtRotation(K2_GetComponentLocation(), TargetActor->GetActorLocation());
	auto OwingPawn = Cast<APawn>(GetOwner());

	if (nullptr == OwingPawn) return;
	Cast<APawn>(GetOwner())->GetController()->SetControlRotation(LookRotation);
}

void UPlayerCameraComponent::SetTargetToChase()
{
	if (nullptr != TargetActor)
	{
		TargetActor = nullptr;
		return;
	}

	//FVector Start = K2_GetComponentLocation();
	//FVector End = Start + GetForwardVector() * 15000.0f;

	FHitResult LocalHitResult;
	//TArray<TEnumAsByte<EObjectTypeQuery>> TraceObjectTypes;
	//TEnumAsByte<EObjectTypeQuery> PawnType = UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn);
	//TraceObjectTypes.Add(PawnType);

	//TArray<AActor*> ActorsToIgnore;
	//ActorsToIgnore.Add(GetOwner());

	bool IsHit = FindEnemyAtForward(LocalHitResult);
		/*UKismetSystemLibrary::SphereTraceSingleForObjects(
		GetWorld(),
		Start,
		End,
		30.0f,
		TraceObjectTypes,
		false,
		ActorsToIgnore,
		EDrawDebugTrace::ForDuration,
		LocalHitResult,
		true
	);*/

	if (IsHit && LocalHitResult.GetActor()->ActorHasTag(FName("Enemy")))
	{
		TargetActor = LocalHitResult.GetActor();
	}
}

bool UPlayerCameraComponent::FindEnemyAtForward(FHitResult& HitResult)
{
	FVector Start = K2_GetComponentLocation();
	FVector End = Start + GetForwardVector() * 15000.0f;

	TArray<TEnumAsByte<EObjectTypeQuery>> TraceObjectTypes;
	TEnumAsByte<EObjectTypeQuery> PawnType = UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn);
	TraceObjectTypes.Add(PawnType);

	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(GetOwner());

	bool IsHit = UKismetSystemLibrary::SphereTraceSingleForObjects(
		GetWorld(),
		Start,
		End,
		50.0f,
		TraceObjectTypes,
		false,
		ActorsToIgnore,
		EDrawDebugTrace::None,
		HitResult,
		true
	);
	return IsHit;
}