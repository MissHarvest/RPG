// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Engine/DataTable.h>
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

	bool UseItem(class APawn* OwingPawn);
};

USTRUCT(Atomic, BlueprintType)
struct RPG_API FItemSlot
{
	GENERATED_BODY()

public:
	FItemSlot() 
	: Quentity(1) // Item 은 하지 않아도 되는가.
	{};

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Quentity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDataTableRowHandle Item;
};

USTRUCT(Atomic, BlueprintType)
struct RPG_API FQuickSlot
{
	GENERATED_BODY()

public:
	FQuickSlot() {}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ID;

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDataTableRowHandle Item;*/
};