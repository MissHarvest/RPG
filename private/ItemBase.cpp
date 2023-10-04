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

	if (ItemSlot.Item.IsNull())
	{
		UE_LOG(LogTemp, Warning, TEXT("Not Exist"));
	}
	else UE_LOG(LogTemp, Warning, TEXT("Exist"));
	ItemSlot.Quentity = 1;
}

// Called when the game starts or when spawned
void AItemBase::BeginPlay()
{
	Super::BeginPlay();
	
	if (ItemSlot.Item.IsNull()) return;

	auto Item = ItemSlot.Item.DataTable->FindRow<FItem>(ItemSlot.Item.RowName, "Failed");
	StaticMesh->SetStaticMesh(Item->Mesh);
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