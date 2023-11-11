// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CustomStruct.h"
#include "InventorySystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_TwoParams(FSlotChangedSignature, UInventorySystem, OnSlotChanged, int32, Index, FItemSlot, ItemSlot);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RPG_API UInventorySystem : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Items", meta = (AllowPrivateAccess = "true"))
	TArray<FItemSlot> Contents;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Items", meta = (AllowPrivateAccess = "true"))
	TArray<int32> RegistedItemsID;

	int32 Size;

	int32 EmptyIndex;

public:	
	// Sets default values for this component's properties
	UInventorySystem();

public:
	UPROPERTY()
	FSlotChangedSignature OnSlotChanged;

	UPROPERTY()
	class UQuickSlotSystem* QuickSlotSystem;

private:
	void UpdateEmptyIndex();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	int32 GetSize() const { return Size; }

	/* ������ ���� ������. ���� */
	FItemSlot& GetContent(int32 Index) { return Contents[Index]; }
	
	bool AddItem(const FItemSlot Item);

	/*  */
	bool AddItem(const TArray<FItemSlot> Items);

	void SwapItem(UInventorySystem* SourceInventory, int32 SourceIndex, int32 DestinationIndex);

	void ConsumeItemByIndex(int32 IndexToUse);

	/* �ߺ� ���� ��� - GetContent */
	FItemSlot GetItemByIndex(int32 IndexToFind);

private:
	/* Index �� �Ű������� �ѱ�°� ������� �����ؾ��Ѵ�. */
	void BroadCastSlotChanged(int32 Index, FItemSlot ItemSlot);
};
