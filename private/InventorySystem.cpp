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
	EmptyIndex = -1;
}


// Called when the game starts
void UInventorySystem::BeginPlay()
{
	Super::BeginPlay();

	// ...
	Contents.SetNum(Size);
	TestContents.SetNum(Size);

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

	/*if (-1 == EmptyIndex) return false;

	auto Item_ = NewObject<UTestItem>();
	Item_->Quentity = ItemSlot.Quentity;
	Item_->Item = ItemSlot.Item;

	TestContents[EmptyIndex] = Item_;
	BroadCastSlotChanged();
	return true;*/
}

bool UInventorySystem::AddItem(class UTestItem* RefItem)
{
	int emptyIdx = -1;
	for (int i = 0; i < TestContents.Num(); ++i)
	{
		if (nullptr == TestContents[i])
		{
			emptyIdx = i;
			break;
		}
	}
	
	if (-1 == emptyIdx) return false;
	TestContents[emptyIdx] = RefItem;
	BroadCastSlotChanged();
	return true;
}

void UInventorySystem::SwapItem(UInventorySystem* SourceInventory, int32 SourceIndex, int32 DestinationIndex)
{
	/* 원본 코드 */
	auto TempItemSlot = Contents[DestinationIndex];
	Contents[DestinationIndex] = SourceInventory->Contents[SourceIndex];
	SourceInventory->Contents[SourceIndex] = TempItemSlot;
	BroadCastSlotChanged();
	SourceInventory->BroadCastSlotChanged();

	/* Test Code */
	//auto TempItemSlot = TestContents[DestinationIndex];
	//TestContents[DestinationIndex] = SourceInventory->TestContents[SourceIndex];
	//SourceInventory->TestContents[SourceIndex] = TempItemSlot;
	//BroadCastSlotChanged();
	//SourceInventory->BroadCastSlotChanged();
}

void UInventorySystem::BroadCastSlotChanged()
{
	OnSlotChanged.Broadcast();
}

bool UInventorySystem::ConsumeItem(int32 ItemIDToUse)
{
	//if (nullptr == TestContents[IndexToUse]) return false;
	//auto OwnigPawn = Cast<APawn>(GetOwner());
	//bool bUsed = TestContents[IndexToUse]->Use(OwnigPawn);
	//if (bUsed)
	//{
	//	--TestContents[IndexToUse]->Quentity;
	//	if (0 == TestContents[IndexToUse]->Quentity)
	//	{
	//		//delete TestContents[IndexToUse];
	//		TestContents[IndexToUse] = nullptr;
	//		BroadCastSlotChanged();
	//	}
	//}
	//return true;

	// 원본 코드 /
	auto ItemIndex = GetItem(ItemIDToUse);
	//if (Contents[ItemIndex].Item.IsNull()) return false;
	if (-1 == ItemIndex) return false;

	auto OwnigPawn = Cast<APawn>(GetOwner());
	
	bool bUsed = Contents[ItemIndex].Use(OwnigPawn);
	if (bUsed)
	{
		--Contents[ItemIndex].Quentity;
		if (0 == Contents[ItemIndex].Quentity)
		{
			FItemSlot tempSlot;
			Contents[ItemIndex] = tempSlot;
		}
		BroadCastSlotChanged();
	}
	return bUsed;
}

int32 UInventorySystem::GetItem(int32 ItemID)
{
	for (int i = 0; i < Size; ++i)
	{
		if (0 != Contents[i].Quentity && ItemID == Contents[i].GetID())
		{
			return i;
		}
	}
	return -1; // Do Think
}