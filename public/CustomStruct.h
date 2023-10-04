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
	: Quentity(0) // Item 은 하지 않아도 되는가.
	{};

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Quentity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDataTableRowHandle Item;

	bool Use(class APawn* OwingPawn); // not need //
	 
	TObjectPtr<class UTexture2D> GetTexture(); // not need //

	int32 GetID();
};


UCLASS(BlueprintType)
class RPG_API UTestItem : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Quentity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDataTableRowHandle Item;

	bool Use(class APawn* OwingPawn);

	TObjectPtr<class UTexture2D> GetTexture();
};

USTRUCT(Atomic, BlueprintType)
struct RPG_API FQuickSlot
{
	GENERATED_BODY()

public:
	FQuickSlot()
		: SourceInventory(nullptr)
		, Index(-1)
		, ItemID(0)
		, SlotType(ESlotType::Item)
		, Ref_Item(nullptr)
	{};

public:
	UPROPERTY()
	class UInventorySystem* SourceInventory;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 Index;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 ItemID;

	// 수량?

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	ESlotType SlotType;

	/* Test Code */
	UPROPERTY()
	class UTestItem* Ref_Item;
};