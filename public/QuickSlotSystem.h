// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CustomStruct.h"
#include "QuickSlotSystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE(FQuickChangedSignature, UQuickSlotSystem, OnQuickSlotChanged);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RPG_API UQuickSlotSystem : public UActorComponent
{
	GENERATED_BODY()

	int32 Size;

public:	
	// Sets default values for this component's properties
	UQuickSlotSystem();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FQuickSlot> QuickSlots;

	/* Do : GetQuickSlot Function Make */

	void Press(EQuickSlotKey QuickSlotKey);

	UPROPERTY()
	FQuickChangedSignature OnQuickSlotChanged;

	/* Update Quick Slot Widget by index */
	void UpdateQuickSlot();

	void UpdateQuickSlotInfoByIndex(int32 IndexToSet, class UInventorySystem* Ref_Inventory, int32 IndexToSource);

	FORCEINLINE int32 GetSize() const { return Size; } 

	void ChangeLinkedIndex(int32 TargetIndex, int32 IndexToChange);

	void SwapQuickSlot(int32 SourceIndex, int32 DestinationIndex);

	void ClearQuickSlotByIndex(int32 index);

	int32 GetQuickSlotIndexByItemID(int32 ID);
};
