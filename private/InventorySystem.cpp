// Fill out your copyright notice in the Description page of Project Settings.


#include "InventorySystem.h"
#include "QuickSlotSystem.h"

// Sets default values for this component's properties
UInventorySystem::UInventorySystem()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
	Size = 20;
	EmptyIndex = -1;
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
	// 원본 코드 /
	int emptyIdx = -1;
	for (int i = 0; i < Contents.Num(); ++i)
	{
		if (Contents[i].IsEmpty())
		{
			emptyIdx = i;
			break;
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("Empty Index : %d"), emptyIdx);
	if (-1 == emptyIdx) return false;
	Contents[emptyIdx] = ItemSlot;
	BroadCastSlotChanged();

	int32 index = 0;
	if (RegistedItemsID.Find(Contents[emptyIdx].GetID(), index))
	{
		int32 QuickSlotIndex = QuickSlotSystem->GetQuickSlotIndexByItemID(Contents[emptyIdx].GetID());
		if (-1 != QuickSlotIndex)
		{
			QuickSlotSystem->ChangeLinkedIndex(QuickSlotIndex, emptyIdx);
			Contents[emptyIdx].SetLinkedIndex(QuickSlotIndex);
		}
	}
	QuickSlotSystem->UpdateQuickSlot();

	return true;
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
	
	/* 서로 다른 인벤토리 간의 이동일 경우 생각하기 */
	if (Contents[SourceIndex].IsLinked())
	{
		QuickSlotSystem->ChangeLinkedIndex(Contents[SourceIndex].GetLinkedIndex(), SourceIndex);
	}
	
	if (Contents[DestinationIndex].IsLinked())
	{
		QuickSlotSystem->ChangeLinkedIndex(Contents[DestinationIndex].GetLinkedIndex(), DestinationIndex);
	}

	BroadCastSlotChanged();
	SourceInventory->BroadCastSlotChanged();
}

void UInventorySystem::BroadCastSlotChanged()
{
	OnSlotChanged.Broadcast();
}

void UInventorySystem::ConsumeItemByIndex(int32 IndexToUse)
{
	auto OwnigPawn = Cast<APawn>(GetOwner());
	bool bUsed = Contents[IndexToUse].Use(OwnigPawn);
	if (bUsed)
	{
		BroadCastSlotChanged();
	}	
}

void UInventorySystem::RegisterItemID(int32 ID)
{
	int32 index = 0;
	if (!RegistedItemsID.Find(ID, index))
	{
		RegistedItemsID.Add(ID);
	}
}

void UInventorySystem::DeleteRegistedID(int32 ID)
{
	int32 index = 0;
	UE_LOG(LogTemp, Warning, TEXT("Delete Registed Item : %d"), ID);
	if (RegistedItemsID.Find(ID, index))
	{
		RegistedItemsID.RemoveAt(index);
	}
}

FItemSlot UInventorySystem::GetItemByIndex(int32 IndexToFind)
{
	return Contents[IndexToFind];
}

void UInventorySystem::ChangedLinkedIndex(int32 TargetIndex, int32 ChangedIndex)
{
	Contents[TargetIndex].SetLinkedIndex(ChangedIndex);
}

