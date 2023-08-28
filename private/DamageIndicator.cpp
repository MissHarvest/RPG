// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageIndicator.h"
#include "Components/Widget.h"
#include "Components/WidgetComponent.h"
#include <GameFramework/ProjectileMovementComponent.h>
// Sets default values
ADamageIndicator::ADamageIndicator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//
	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	WidgetComponent->SetupAttachment(RootComponent);

	ProjectileComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
}

// Called when the game starts or when spawned
void ADamageIndicator::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADamageIndicator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

