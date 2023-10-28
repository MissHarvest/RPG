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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Content;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UTexture2D> Texture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Price;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DropRate;
};

// class ? 
USTRUCT(Atomic, BlueprintType)
struct RPG_API FItemSlot
{
	GENERATED_BODY()

public:
	FItemSlot() 
	: Quantity(0)
	, LinkedIndex(-1)
	{
		
	};

	FItemSlot(FItem* ItemData)
		: Quantity(0)
		, LinkedIndex(-1)
	{
		Item.Name = ItemData->Name;
		Item.Content = ItemData->Content;
		Item.Texture = ItemData->Texture;
		Item.Price = ItemData->Price;
		Item.DropRate = ItemData->DropRate;
	};

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName IID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FItem Item;

	/* 인벤토리 시스템에서 보인다. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Quantity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 LinkedIndex;

public:
	//bool Use(class APawn* OwingPawn);
	 
	TObjectPtr<class UTexture2D> GetTexture();

	FName GetID();

	bool IsEmpty();

	void SetEmpty();

	int32 GetQuantity() const { return Quantity; }

	void AddQuantity(int32 CountToAdd);

	void LinkQuickSlotIndex(int32 IndexToLink);

	bool IsLinked();

	/* Function const */
	int32 GetLinkedIndex() const { return LinkedIndex;  }

	void SetLinkedIndex(int32 IndexToChanage);

	/*  */
	FString GetName();
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

USTRUCT(Atomic, BlueprintType)
struct RPG_API FQuestInfo : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Index;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Content;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Summary;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Objectives;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Reward;
};

USTRUCT(Atomic, BlueprintType)
struct RPG_API FMonsterData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 EXP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString DropItems;
};

USTRUCT(Atomic, BlueprintType)
struct RPG_API FObjective
{
	GENERATED_BODY()

public:
	EObjectiveType Type;

	FString Target;

	int32 ProgressCount;

	int32 RequestedCount;

	bool bCompleted;

public:
	FObjective()
		: Type(EObjectiveType::Hunting)
		, Target("")
		, ProgressCount(0)
		, RequestedCount(0)
		, bCompleted(false)
	{};

	FObjective(EObjectiveType ObjectiveType, FString TargetName, int32 ObjectiveCount)
		: Type(ObjectiveType)
		, Target(TargetName)
		, ProgressCount(0)
		, RequestedCount(ObjectiveCount)
		, bCompleted(false)
	{};

	bool IsTarget(FName Name);
};

USTRUCT(Atomic, BlueprintType)
struct RPG_API FQuest
{
	GENERATED_BODY()

public:
	FQuest()
		:QuestState(EQuestState::Stay)
	{

	};

	FQuest(FQuestInfo* QuestData, TArray<FItemSlot> QuestRewards, TArray<FObjective> QuestObjectives)
		: Rewards(QuestRewards)
		, Objectives(QuestObjectives)
	{
		Quest.Name = QuestData->Name;
		Quest.Content = QuestData->Content;
		Quest.Summary = QuestData->Summary;
		Quest.Index = QuestData->Index;		
	}

protected:
	UPROPERTY()
	TArray<FItemSlot> Rewards;
	
	UPROPERTY()
	TArray<FObjective> Objectives;
	
	UPROPERTY()
	FQuestInfo Quest;	

public:
	UPROPERTY(VisibleAnywhere)
	EQuestState QuestState;

public:
	/* Get Quest Name */
	FString GetName() const;

	/*  */
	TArray<FObjective> GetObjectives();

	/*  */
	TArray<FItemSlot> GetReward();

	/*  */
	int32 GetIndex();

	/*  */
	FString GetContent();

	/*  */
	FString GetSummary();

	/*  */
	bool UpdateObjective(FName Name);

	/*  */
	bool operator==(const FQuest& Other) const
	{
		return (GetName() == Other.GetName());
	}
};


USTRUCT(Atomic, BlueprintType)
struct RPG_API FStatus
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FDataTableRowHandle MonsterDataHandle;

public:
	FStatus()
		: Level(0)
		, CurrentHP(0)
		, MaxHP(0)
		, EXP(0)
	{};

	FStatus(FMonsterData* MonsterData)
	{
		Level = MonsterData->Level;
		MaxHP = MonsterData->MaxHP;
		CurrentHP = MaxHP;
		EXP = MonsterData->EXP;
	};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CurrentHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxHP;
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 EXP;
};

USTRUCT(Atomic, BlueprintType)
struct RPG_API FPlayerQuest : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Quest;
};

USTRUCT(Atomic, BlueprintType)
struct RPG_API FNPCQuest : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Quest;
};