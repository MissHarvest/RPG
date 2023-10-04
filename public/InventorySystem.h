// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CustomStruct.h"
#include "InventorySystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE(FSlotChangedSignature, UInventorySystem, OnSlotChanged);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RPG_API UInventorySystem : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Items", meta = (AllowPrivateAccess = "true"))
	TArray<FItemSlot> Contents;

	int32 Size;

	int32 EmptyIndex;

public:	
	// Sets default values for this component's properties
	UInventorySystem();

public:
	UPROPERTY()
	FSlotChangedSignature OnSlotChanged;

	/* Test Code */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Items", meta = (AllowPrivateAccess = "true"))
	TArray<class UTestItem*> TestContents;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	int32 GetSize() const { return Size; }

	FItemSlot GetContent(int32 Index) const { return Contents[Index]; }
	
	/* Test Code */
	class UTestItem* GetTestContent(int32 Index) const { return TestContents[Index]; }

	bool AddItem(const FItemSlot Item); // ¡÷¿«

	/* Test Code */
	bool AddItem(class UTestItem* RefItem);

	void SwapItem(UInventorySystem* SourceInventory, int32 SourceIndex, int32 DestinationIndex);

	bool ConsumeItem(int32 ItemIDToUse);

	/* Change Return Value FIemSlot& , after FItemSlot's Empty Function maked */
	/* GetItemIndex */
	int32 GetItem(int32 ItemID);

private:
	void BroadCastSlotChanged();
};
