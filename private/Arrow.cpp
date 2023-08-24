// Fill out your copyright notice in the Description page of Project Settings.


#include "Arrow.h"
#include <GameFramework/ProjectileMovementComponent.h>
#include <Components/StaticMeshComponent.h>
#include <Components/BoxComponent.h>
// Sets default values
AArrow::AArrow()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	SetRootComponent(BoxComponent);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	StaticMesh->SetupAttachment(BoxComponent);
	StaticMesh->SetCollisionProfileName(TEXT("NoCollision"));

	Projectile = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	Projectile->InitialSpeed = 6500.0f;
	Projectile->MaxSpeed = 6500.0f;
	Projectile->ProjectileGravityScale = 0.0f;
}

// Called when the game starts or when spawned
void AArrow::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AArrow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

