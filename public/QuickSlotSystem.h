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

	void Press(EQuickSlotKey QuickSlotKey);

	UPROPERTY()
	FQuickChangedSignature OnQuickSlotChanged;

	void UpdateQuickSlot();

	//void SetQuickSlot(int32 IndexToSet, class UInventorySystem* Ref_Inventory, int32 IndexToSource);

	/* Test Code */
	void SetQuickSlot(int32 IndexToSet, class UTestItem* RefItem);

	/* Test Code */
	void SetQuickSlot(int32 IndexToSet, class UInventorySystem* Ref_Inventory, int32 Ref_ItemID);

	int32 GetSize() const { return Size; } // FORCEINLINE ?
};
