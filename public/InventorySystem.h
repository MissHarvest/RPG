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

	UPROPERTY()
	class UQuickSlotSystem* QuickSlotSystem;

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

	void SwapItem(UInventorySystem* SourceInventory, int32 SourceIndex, int32 DestinationIndex);

	void ConsumeItemByIndex(int32 IndexToUse);

	/* �ߺ� ���� ��� - GetContent */
	FItemSlot GetItemByIndex(int32 IndexToFind);

	void ChangedLinkedIndex(int32 TargetIndex, int32 ChangedIndex);

private:
	/* Index �� �Ű������� �ѱ�°� ������� �����ؾ��Ѵ�. */
	void BroadCastSlotChanged();
};
