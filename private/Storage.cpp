// Fill out your copyright notice in the Description page of Project Settings.


#include "Storage.h"
#include <Components/SphereComponent.h>
#include <Components/StaticMeshComponent.h>
#include "InventorySystem.h"

#include <Kismet/GameplayStatics.h>

#include "PlayerCharacter.h"
#include "DefaultScreenWidget.h"
// Sets default values
AStorage::AStorage()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	SetRootComponent(SphereComponent);

	StorageMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Storage"));
	StorageMesh->SetupAttachment(SphereComponent);

	LidMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Storage_Lid"));
	LidMesh->SetupAttachment(SphereComponent);

	Inventory = CreateDefaultSubobject<UInventorySystem>(TEXT("Inventory"));
}

// Called when the game starts or when spawned
void AStorage::BeginPlay()
{
	Super::BeginPlay();
	auto Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	Cast<APlayerCharacter>(Player)->GetPlayerWidget()->LinkStorage(Inventory);
	
}

// Called every frame
void AStorage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

