// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Engine/DataTable.h>
#include "CustomEnum.h"
#include <UObject/Object.h>
#include "CustomStruct.generated.h"

UCLASS()
class RPG_API ACustomStruct : public AActor
{
	GENERATED_BODY()
};

USTRUCT(Atomic, BlueprintType)
struct RPG_API FItem : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UStaticMesh> Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UTexture2D> Texture;
};

USTRUCT(Atomic, BlueprintType)
struct RPG_API FItemSlot
{
	GENERATED_BODY()

public:
	FItemSlot() 
	: Quantity(0)
	, LinkedIndex(-1)
	{};

protected:
	/* �κ��丮 �ý��ۿ��� ���δ�. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Quantity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 LinkedIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDataTableRowHandle Item;

public:
	bool Use(class APawn* OwingPawn);
	 
	TObjectPtr<class UTexture2D> GetTexture();

	TObjectPtr<class UStaticMesh> GetMesh();

	int32 GetID();

	bool IsEmpty();

	void SetEmpty();

	int32 GetQuantity() const { return Quantity; }

	void AddQuantity(int32 CountToAdd);

	void LinkQuickSlotIndex(int32 IndexToLink);

	bool IsLinked();

	/* Function const */
	int32 GetLinkedIndex() const { return LinkedIndex;  }

	void SetLinkedIndex(int32 IndexToChanage);
};

USTRUCT(Atomic, BlueprintType)
struct RPG_API FQuickSlot
{
	GENERATED_BODY()

public:
	FQuickSlot()
		: SourceInventory(nullptr)
		, LinkedIndex(-1)
		, SlotType(ESlotType::None)
		, ItemID(-1)
	{};

public:
	UPROPERTY()
	class UInventorySystem* SourceInventory;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 LinkedIndex;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	ESlotType SlotType;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 ItemID;

	bool IsEmpty();

	void Clear();
};