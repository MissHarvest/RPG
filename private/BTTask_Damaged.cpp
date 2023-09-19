// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Damaged.h"
#include "EnemyCharacter.h"
#include "EnemyAIController.h"
#include <BehaviorTree/BlackboardComponent.h>

UBTTask_Damaged::UBTTask_Damaged()
{
	NodeName = TEXT("Damaged");
	bNotifyTick = true;
	Duration = 0;
}

EBTNodeResult::Type UBTTask_Damaged::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto ControllingPawn = Cast<AEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == ControllingPawn) return EBTNodeResult::Failed;
	
	Duration = ControllingPawn->Damaged();
	Timer = Duration;	
	return EBTNodeResult::InProgress;
}

void UBTTask_Damaged::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	
	Timer -= DeltaSeconds;
	if (Timer <= 0)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(AEnemyAIController::Damaged, false);
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(AEnemyAIController::CanAttack, false);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
