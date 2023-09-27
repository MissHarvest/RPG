// Fill out your copyright notice in the Description page of Project Settings.


#include "InventorySystem.h"
#include "ItemBase.h"

// Sets default values for this component's properties
UInventorySystem::UInventorySystem()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	Size = 20;
}


// Called when the game starts
void UInventorySystem::BeginPlay()
{
	Super::BeginPlay();

	// ...
	Contents.SetNum(Size);
}


// Called every frame
void UInventorySystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UInventorySystem::AddItem(const FItemSlot ItemSlot)
{
	int emptyIdx = -1;
	for (int i = 0; i < Contents.Num(); ++i)
	{
		if (Contents[i].Item.IsNull())
		{
			emptyIdx = i;
			break;
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("Empty Index : %d"), emptyIdx);
	if (-1 == emptyIdx) return false;
	Contents[emptyIdx] = ItemSlot;
	BroadCastSlotChanged();
	return true;
}

void UInventorySystem::SwapItem(UInventorySystem* SourceInventory, int32 SourceIndex, int32 DestinationIndex)
{
	auto TempItemSlot = Contents[DestinationIndex];
	Contents[DestinationIndex] = SourceInventory->Contents[SourceIndex];
	SourceInventory->Contents[SourceIndex] = TempItemSlot;
	BroadCastSlotChanged();
	SourceInventory->BroadCastSlotChanged();
}

void UInventorySystem::BroadCastSlotChanged()
{
	OnSlotChanged.Broadcast();
}

bool UInventorySystem::ConsumeItem(int32 IndexToUse)
{
	// Index Item Is Exist?
	if (Contents[IndexToUse].Item.IsNull()) return false;
	
	// Index Item Is Consumable?
	//if (Contents[IndexToUse].Item.DataTable->FindRow<FItem>(Contents[IndexToUse].Item.RowName, "Failed")->ID)
	//{

	//}

	// Use
	auto OwingPawn = Cast<APawn>(GetOwner());
	if (nullptr == OwingPawn) return false;
	bool Used = Contents[IndexToUse].Item.DataTable->FindRow<FItem>(Contents[IndexToUse].Item.RowName, "Failed")->UseItem(OwingPawn);
	if (Used)
	{
		--Contents[IndexToUse].Quentity;
		if (0 == Contents[IndexToUse].Quentity)
		{
			FItemSlot tempSlot;
			Contents[IndexToUse] = tempSlot;
		}
		BroadCastSlotChanged();
	}
	return Used;
}