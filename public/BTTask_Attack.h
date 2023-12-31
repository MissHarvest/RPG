// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Attack.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API UBTTask_Attack : public UBTTaskNode
{
	GENERATED_BODY()
	
	float Timer;
	float Duration;
	bool bPlayAnimation;
	int num;

public:
	UBTTask_Attack();
		
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};

USTRUCT()
struct FAttackTaskMemory
{
	GENERATED_BODY()
public:
	float Timer;
};