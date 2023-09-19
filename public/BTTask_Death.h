// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Death.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API UBTTask_Death : public UBTTaskNode
{
	GENERATED_BODY()
	
	float Timer;
	float Duration;

public:
	UBTTask_Death();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
