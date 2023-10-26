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
	{
		Item.DataTable = LoadObject<UDataTable>(NULL, TEXT("/Script/Engine.DataTable'/Game/Data/DT_ItemList.DT_ItemList'"));
	};

	FItemSlot(FName IID, int32 Count = 0)
		: Quantity(Count)
		, LinkedIndex(-1)
	{
		Item.DataTable = LoadObject<UDataTable>(NULL, TEXT("/Script/Engine.DataTable'/Game/Data/DT_ItemList.DT_ItemList'"));
		Item.RowName = IID;
	};

protected:
	/* 인벤토리 시스템에서 보인다. */
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
};

USTRUCT(Atomic, BlueprintType)
struct RPG_API FObjective
{
	GENERATED_BODY()

private:
	FName MID;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FDataTableRowHandle MonsterDataHandle;

public:
	EObjectiveType Type;

	FString Summary;

	FString Target;

	int32 ProgressCount;

	int32 RequestedCount;

	bool bCompleted;

public:
	FObjective()
		: Type(EObjectiveType::Hunting)
		, Summary("")
		, Target("")
		, ProgressCount(0)
		, RequestedCount(0)
		, bCompleted(false)
	{};

	FObjective(EObjectiveType ObjectiveType, FString ObjectSummary, FString TargetName, int32 ObjectiveCount)
		: MID(FName(*TargetName))
		, Type(ObjectiveType)
		, Summary(ObjectSummary)
		, ProgressCount(0)
		, RequestedCount(ObjectiveCount)
	{
		MonsterDataHandle.DataTable = LoadObject<UDataTable>(NULL, TEXT("/Script/Engine.DataTable'/Game/Data/DT_MonsterList.DT_MonsterList'"));
		Target = MonsterDataHandle.DataTable->FindRow<FMonsterData>(MID, TEXT("Failed"))->Name;
	};

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
		///Script/Engine.DataTable'/Game/Data/DT_QuestList.DT_QuestList'
		QuestManager.DataTable = LoadObject<UDataTable>(NULL, TEXT("/Script/Engine.DataTable'/Game/Data/DT_QuestList.DT_QuestList'"));
	};

	FQuest(FName QuestID)
	{
		QuestManager.DataTable = LoadObject<UDataTable>(NULL, TEXT("/Script/Engine.DataTable'/Game/Data/DT_QuestList.DT_QuestList'"));
		QuestManager.RowName = QuestID;
	}

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDataTableRowHandle QuestManager;
	
	UPROPERTY()
	TArray<FObjective> Objectives;

public:
	UPROPERTY(VisibleAnywhere)
	EQuestState QuestState;

public:
	/* Set Quest ID */
	void Set(int32 IDofQuest);

	/*  */
	void Set(FText Name);

	/*  */
	void Activate();

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