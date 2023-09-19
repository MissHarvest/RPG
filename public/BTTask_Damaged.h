// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Damaged.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API UBTTask_Damaged : public UBTTaskNode
{
	GENERATED_BODY()
	
	float Timer;
	float Duration;

public:
	UBTTask_Damaged();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
