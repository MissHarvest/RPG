// Fill out your copyright notice in the Description page of Project Settings.


#include "QuickSlotSystem.h"
#include "ItemEffectManager.h"
#include "InventorySystem.h"

//#include "CustomEnum.h"

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
	
	// Do Anything
	int32 Index = (int)QuickSlotKey;
	if (-1 == QuickSlots[Index].Index) return;
	
	auto OwnigPawn = Cast<APawn>(GetOwner());
	QuickSlots[Index].SourceInventory->GetContent(QuickSlots[Index].Index).Use(OwnigPawn);
}

void UQuickSlotSystem::UpdateQuickSlot()
{
	if(OnQuickSlotChanged.IsBound())
	{
		OnQuickSlotChanged.Broadcast();
	}
}

void UQuickSlotSystem::SetQuickSlot(int32 IndexToSet, class UInventorySystem* Ref_Inventory, int32 IndexToSource)
{
	QuickSlots[IndexToSet].SlotType = ESlotType::Item;
	QuickSlots[IndexToSet].Index = IndexToSource;
	QuickSlots[IndexToSet].SourceInventory = Ref_Inventory;
	UpdateQuickSlot();
}
