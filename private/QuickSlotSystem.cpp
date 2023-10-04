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
	
	// Do Anything , Slot Type == Item
	int32 Index = (int)QuickSlotKey;
	if (0 == QuickSlots[Index].ItemID) return;
	
	auto OwnigPawn = Cast<APawn>(GetOwner());
	bool bUsedIem = QuickSlots[Index].SourceInventory->ConsumeItem(QuickSlots[Index].ItemID);
	if (bUsedIem)
	{
		// inventory 에 해당 아이템이 있나?
		if (-1 != QuickSlots[Index].SourceInventory->GetItem(QuickSlots[Index].ItemID))
		{
			//QuickSlots[Index].
		}

		// 수량 업데이트

		// 위젯 업데이트		
		//UpdateQuickSlot();
	}

	//int32 Index = (int)QuickSlotKey;
	//if (nullptr == QuickSlots[Index].Ref_Item) return;
	//auto OwningPawn = Cast<APawn>(GetOwner());
	//bool bUsedItem = QuickSlots[Index].Ref_Item->Use(OwningPawn); // Inventory 정보를 가져야 한다.
	//if (bUsedItem) UpdateQuickSlot();

	// Do Anything , Slot Type == Skill
}

void UQuickSlotSystem::UpdateQuickSlot()
{
	if(OnQuickSlotChanged.IsBound())
	{
		OnQuickSlotChanged.Broadcast();
	}
}

//void UQuickSlotSystem::SetQuickSlot(int32 IndexToSet, class UInventorySystem* Ref_Inventory, int32 IndexToSource)
//{
//	QuickSlots[IndexToSet].SlotType = ESlotType::Item;
//	QuickSlots[IndexToSet].Index = IndexToSource;
//	QuickSlots[IndexToSet].SourceInventory = Ref_Inventory;
//	UpdateQuickSlot();
//}

void UQuickSlotSystem::SetQuickSlot(int32 IndexToSet, class UTestItem* RefItem)
{
	QuickSlots[IndexToSet].Ref_Item = RefItem;
	UpdateQuickSlot();
}

void UQuickSlotSystem::SetQuickSlot(int32 IndexToSet, class UInventorySystem* Ref_Inventory, int32 Ref_ItemID)
{
	QuickSlots[IndexToSet].SlotType = ESlotType::Item;
	QuickSlots[IndexToSet].SourceInventory = Ref_Inventory;
	QuickSlots[IndexToSet].ItemID = Ref_ItemID;
	UpdateQuickSlot();
}
