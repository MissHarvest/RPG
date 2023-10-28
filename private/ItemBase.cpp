// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemBase.h"
#include <Components/StaticMeshComponent.h>
#include <Components/SphereComponent.h>
#include "CustomStruct.h"
// Sets default values
AItemBase::AItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	SetRootComponent(SphereComponent);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	StaticMesh->SetupAttachment(SphereComponent);

	ItemSlot.AddQuantity(2);
}

// Called when the game starts or when spawned
void AItemBase::BeginPlay()
{
	Super::BeginPlay();
	
	if (ItemSlot.IsEmpty()) return;

	//StaticMesh->SetStaticMesh(ItemSlot.GetMesh());
}

// Called every frame
void AItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FItemSlot AItemBase::GetItem()
{
	return ItemSlot;
}