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

	void Press(int32 index);

	UPROPERTY()
	FQuickChangedSignature OnQuickSlotChanged;

	void UpdateQuickSlot();

	void SetQuickSlot(class UInventorySystem* InventoryToSoucre, int32 IndexToSoucre, int32 IndexToSet);
};
