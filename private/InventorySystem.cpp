// Fill out your copyright notice in the Description page of Project Settings.


#include "InventorySystem.h"
#include "QuickSlotSystem.h"
#include "PlayerCharacter.h"

// Sets default values for this component's properties
UInventorySystem::UInventorySystem()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
	Size = 20;
	EmptyIndex = 0;
}

// Called when the game starts
void UInventorySystem::BeginPlay()
{
	Super::BeginPlay();

	// ...
	Contents.SetNum(Size);

	// Inventory Load //

	// Set EmptyIndex //
	EmptyIndex = 0;
}

// Called every frame
void UInventorySystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UInventorySystem::AddItem(const FItemSlot ItemSlot)
{
	if (EmptyIndex == -1) return false;

	if (ItemSlot.GetItem().bNestable == false)
	{
		Contents[EmptyIndex] = ItemSlot;
		BroadCastSlotChanged(EmptyIndex, ItemSlot);
		UpdateEmptyIndex();		
		return true;
	}

	int32 Index = Contents.Find(ItemSlot);
	if (-1 == Index)
	{
		UE_LOG(LogTemp, Warning, TEXT("Index == -1"));
		Contents[EmptyIndex] = ItemSlot;
		BroadCastSlotChanged(EmptyIndex, ItemSlot);
		UpdateEmptyIndex();		
		return true;
	}
	
	Contents[Index].AddQuantity(ItemSlot.GetQuantity());
	BroadCastSlotChanged(Index, Contents[Index]);
	return true;
}

void UInventorySystem::UpdateEmptyIndex()
{
	for (int i = EmptyIndex + 1; i < Contents.Num(); ++i)
	{
		if (Contents[i].IsEmpty())
		{
			EmptyIndex = i;
			return;
		}
	}
	
	// Inventory is full
	EmptyIndex = -1;
}

bool UInventorySystem::AddItem(const TArray<FItemSlot> Items)
{
	for (int i = 0; i < Items.Num(); ++i)
	{
		AddItem(Items[i]);
	}
	return true;
}

void UInventorySystem::SwapItem(UInventorySystem* SourceInventory, int32 SourceIndex, int32 DestinationIndex)
{
	/* 원본 코드 */
	auto TempItemSlot = Contents[DestinationIndex];
	Contents[DestinationIndex] = SourceInventory->Contents[SourceIndex];
	SourceInventory->Contents[SourceIndex] = TempItemSlot;
	
	BroadCastSlotChanged(DestinationIndex, Contents[DestinationIndex]);
	SourceInventory->BroadCastSlotChanged(SourceIndex, SourceInventory->Contents[SourceIndex]);
}

void UInventorySystem::BroadCastSlotChanged(int32 Index, FItemSlot ItemSlot)
{
	OnSlotChanged.Broadcast(Index, ItemSlot);
}

void UInventorySystem::ConsumeItemByIndex(int32 IndexToUse)
{
	auto OwningPlayer = Cast<APlayerCharacter>(GetOwner());

	// 아이템 사용
	if (Contents[IndexToUse].Consume())
	{
		OwningPlayer->ApplyEffect(Contents[IndexToUse].GetItem());
		OnSlotChanged.Broadcast(IndexToUse, Contents[IndexToUse]);
	}

	if (Contents[IndexToUse].IsEmpty())
	{
		EmptyIndex = IndexToUse;
	}
}

FItemSlot UInventorySystem::GetItemByIndex(int32 IndexToFind)
{
	return Contents[IndexToFind];
}

