// Fill out your copyright notice in the Description page of Project Settings.


#include "QuickSlotSystem.h"
#include "ItemEffectManager.h"
#include "InventorySystem.h"
#include "CustomEnum.h"

// Sets default values for this component's properties
UQuickSlotSystem::UQuickSlotSystem()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UQuickSlotSystem::BeginPlay()
{
	Super::BeginPlay();

	// ...
	QuickSlots.SetNum(10);
}

// Called every frame
void UQuickSlotSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UQuickSlotSystem::Press(int32 index)
{
	int32 _index = QuickSlots[index - 1].Index;
	// index return
	QuickSlots[index - 1].SourceInventory->ConsumeItem(_index);
	/*auto OwingPawn = Cast<APawn>(GetOwner());
	OwingPawn->GetGameInstance()->GetSubsystem<UItemEffectManager>()->PrintID(_id, OwingPawn);*/
}

void UQuickSlotSystem::UpdateQuickSlot()
{
	if(OnQuickSlotChanged.IsBound())
	{
		OnQuickSlotChanged.Broadcast();
	}
}

void UQuickSlotSystem::SetQuickSlot(class UInventorySystem* InventoryToSoucre, int32 IndexToSoucre, int32 IndexToSet)
{
	//QuickSlots[IndexToSet].SlotType = ESlotType::Item;
	QuickSlots[IndexToSet].Index = IndexToSoucre;
	QuickSlots[IndexToSet].SourceInventory = InventoryToSoucre;
	UpdateQuickSlot();
}
