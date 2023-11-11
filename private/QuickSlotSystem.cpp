// Fill out your copyright notice in the Description page of Project Settings.


#include "QuickSlotSystem.h"
#include "ItemEffectManager.h"
#include "InventorySystem.h"
#include "PlayerCharacter.h"

// Sets default values for this component's properties
UQuickSlotSystem::UQuickSlotSystem()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
	Size = 10;
}


// Called when the game starts
void UQuickSlotSystem::BeginPlay()
{
	Super::BeginPlay();
	
	// ...
	QuickSlots.SetNum(Size);
	Cast<APlayerCharacter>(GetOwner())->GetInventory()->OnSlotChanged.AddDynamic(this, &UQuickSlotSystem::UpdateLink);
}

// Called every frame
void UQuickSlotSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	// ...
}

void UQuickSlotSystem::Press(EQuickSlotKey QuickSlotKey)
{
	// Check Slot Type
	
	// Do Anything , Slot Type == Item
	int32 Index = (int)QuickSlotKey;
	if (QuickSlots[Index].IsEmpty()) return;
	
	auto OwnigPawn = Cast<APawn>(GetOwner());
	QuickSlots[Index].SourceInventory->ConsumeItemByIndex(QuickSlots[Index].LinkedIndex);
	
	/* check bUsed ? */
	BroadCastQuickSlotChange(Index, QuickSlots[Index]);
	
	// Do Anything , Slot Type == Skill
}

// name Change
void UQuickSlotSystem::BroadCastQuickSlotChange(int32 Index, FQuickSlot QuickSlot)
{
	if(OnChangedQuickSlot.IsBound())
	{
		OnChangedQuickSlot.Broadcast(Index, QuickSlot);
	}
}

void UQuickSlotSystem::UpdateQuickSlot(int32 IndexToSet, class UInventorySystem* Ref_Inventory, int32 IndexToSource)
{
	QuickSlots[IndexToSet].SlotType = ESlotType::Item;
	QuickSlots[IndexToSet].LinkedIndex = IndexToSource;
	QuickSlots[IndexToSet].SourceInventory = Ref_Inventory;
	QuickSlots[IndexToSet].Name = Ref_Inventory->GetItemByIndex(IndexToSource).GetName();
	
	BroadCastQuickSlotChange(IndexToSet, QuickSlots[IndexToSet]); // index /
}

void UQuickSlotSystem::SwapQuickSlot(int32 SourceIndex, int32 DestinationIndex)
{
	auto temp = QuickSlots[SourceIndex];
	QuickSlots[SourceIndex] = QuickSlots[DestinationIndex];
	QuickSlots[DestinationIndex] = temp;

	BroadCastQuickSlotChange(SourceIndex, QuickSlots[SourceIndex]);
	BroadCastQuickSlotChange(DestinationIndex, QuickSlots[DestinationIndex]);
}

void UQuickSlotSystem::ClearQuickSlotByIndex(int32 index)
{	
	QuickSlots[index].Clear();
	BroadCastQuickSlotChange(index, QuickSlots[index]);
}

void UQuickSlotSystem::UpdateLink(int32 Index, FItemSlot Item)
{
	for (int i = 0; i < QuickSlots.Num(); ++i)
	{
		if (QuickSlots[i].SlotType != ESlotType::Item) continue;

		if (Item.GetName() == QuickSlots[i].GetName())
		{
			QuickSlots[i].LinkedIndex = Index;
			BroadCastQuickSlotChange(i, QuickSlots[i]);
		}
	}
}