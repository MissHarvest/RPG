// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Death.h"
#include "EnemyCharacter.h"
#include "EnemyAIController.h"
#include <BehaviorTree/BlackboardComponent.h>

UBTTask_Death::UBTTask_Death()
{
	NodeName = TEXT("Death");
	bNotifyTick = true;
	Duration = 0;
}

EBTNodeResult::Type UBTTask_Death::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto ControllingPawn = Cast<AEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == ControllingPawn) return EBTNodeResult::Failed;

	Duration = ControllingPawn->Death();
	Timer = Duration;
	return EBTNodeResult::InProgress;
}

void UBTTask_Death::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	Timer -= DeltaSeconds;
	if (Timer <= 0)
	{
		OwnerComp.StopTree();
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}