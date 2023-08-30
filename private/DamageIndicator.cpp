// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageIndicator.h"
#include "Components/WidgetComponent.h"
#include <GameFramework/ProjectileMovementComponent.h>
#include <Components/StaticMeshComponent.h>
#include "DamageWidget.h"
#include <Kismet/GameplayStatics.h>
#include <GameFramework/Character.h>
#include <Kismet/KismetMathLibrary.h>
// Sets default values
ADamageIndicator::ADamageIndicator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Actor Init Setting
	InitialLifeSpan = 0.3f;

	// Components Init Setting
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	SetRootComponent(StaticMesh);
	StaticMesh->SetCollisionProfileName(TEXT("NoCollision"));

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	WidgetComponent->SetupAttachment(RootComponent);

	ProjectileComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileComponent->InitialSpeed = 10.0f;
	ProjectileComponent->MaxSpeed = 10.0f;
	ProjectileComponent->ProjectileGravityScale = 0.0f;
	ProjectileComponent->Velocity = FVector(0, 0, 1);
}

// Called when the game starts or when spawned
void ADamageIndicator::BeginPlay()
{
	Super::BeginPlay();
	
	auto Widget = Cast<UDamageWidget>(WidgetComponent->GetUserWidgetObject());
	if (IsValid(Widget))
	{
		FText DamageText = FText::FromString(FString::FromInt(DamageSave));
		Widget->SetTextOfDamage(DamageText);
		auto Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		FVector PlayerDirection = Player->GetActorLocation() - GetActorLocation();
		//PlayerDirection.Z = 0;
		auto LookAtPlayer = UKismetMathLibrary::MakeRotFromX(PlayerDirection);
		SetActorRotation(LookAtPlayer);
	}
}

// Called every frame
void ADamageIndicator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADamageIndicator::SetDamage(float Damage)
{
	DamageSave = Damage;
}