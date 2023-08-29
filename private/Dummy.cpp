// Fill out your copyright notice in the Description page of Project Settings.


#include "Dummy.h"
#include <Components/BoxComponent.h>
#include <Components/StaticMeshComponent.h>
#include "DamageIndicator.h"
// Sets default values
ADummy::ADummy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 컴포넌트 생성
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	SetRootComponent(BoxComponent);
	BoxComponent->SetBoxExtent(FVector(50));

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	StaticMesh->SetupAttachment(BoxComponent);
	StaticMesh->SetCollisionProfileName(TEXT("NoCollision"));
	StaticMesh->SetRelativeLocation(FVector(0, 0, -50));
}

// Called when the game starts or when spawned
void ADummy::BeginPlay()
{
	Super::BeginPlay();
	OnTakeAnyDamage.AddDynamic(this, &ADummy::ReceiveDamage);
}

// Called every frame
void ADummy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADummy::ReceiveDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	UE_LOG(LogTemp, Warning, TEXT("HITTED"));
	GetWorld()->SpawnActor<ADamageIndicator>(DamageIndicatorClass, GetActorTransform());
}
