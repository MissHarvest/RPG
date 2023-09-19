// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Attack.h"
#include "EnemyAIController.h"
#include "EnemyCharacter.h"
#include <Kismet/KismetSystemLibrary.h>
#include <BehaviorTree/BlackboardComponent.h>
UBTTask_Attack::UBTTask_Attack()
{
	NodeName = TEXT("Attack");
	INIT_TASK_NODE_NOTIFY_FLAGS();
	Duration = 0;
	num = 0;
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto ControllingPawn = Cast<AEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == ControllingPawn) return EBTNodeResult::Failed;

	Duration = ControllingPawn->Attack();
	bPlayAnimation = true;
	FAttackTaskMemory* MyMemory = reinterpret_cast<FAttackTaskMemory*>(NodeMemory);
	MyMemory->Timer = Duration;
	UE_LOG(LogTemp, Warning, TEXT("BT_AI_Attack_Task_Execute"));
	return EBTNodeResult::InProgress;
}

void UBTTask_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	
	FAttackTaskMemory* MyMemory = reinterpret_cast<FAttackTaskMemory*>(NodeMemory);
	MyMemory->Timer -= DeltaSeconds;
	UE_LOG(LogTemp, Warning, TEXT("BT_AI_Attack_Task_Tick(%f)"), MyMemory->Timer);
	if (MyMemory->Timer <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("BT_AI_Attack_Task_Finish"));
		bPlayAnimation = false;
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);		
	}
}

EBTNodeResult::Type UBTTask_Attack::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (bPlayAnimation)
	{
		return EBTNodeResult::InProgress;
	}
	return EBTNodeResult::Aborted;	
}