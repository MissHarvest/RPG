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

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	int32 GetSize() const { return Size; }

	/* 변수를 직접 참조함. 주의 */
	FItemSlot& GetContent(int32 Index) { return Contents[Index]; }
	
	bool AddItem(const FItemSlot Item);

	void SwapItem(UInventorySystem* SourceInventory, int32 SourceIndex, int32 DestinationIndex);

	void ConsumeItemByIndex(int32 IndexToUse);

	/* 중복 삭제 요망 - GetContent */
	FItemSlot GetItemByIndex(int32 IndexToFind);

	void ChangedLinkedIndex(int32 TargetIndex, int32 ChangedIndex);

	/*  */
	void RegisterItemID(int32 ID);

	/*  */
	void DeleteRegistedID(int32 ID);

private:
	/* Index 를 매개변수로 넘기는건 방식으로 변경해야한다. */
	void BroadCastSlotChanged();
};
