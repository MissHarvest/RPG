// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Patrol.h"
#include <AIController.h>
#include <NavigationSystem.h>
#include <BehaviorTree/BlackboardComponent.h>
#include "EnemyAIController.h"
#include <GameFramework/CharacterMovementComponent.h>
#include <GameFramework/Character.h>

UBTTask_Patrol::UBTTask_Patrol()
{
	NodeName = TEXT("FindPatrolPos");
}

EBTNodeResult::Type UBTTask_Patrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn) return EBTNodeResult::Failed;

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(ControllingPawn->GetWorld());
	if (nullptr == NavSystem) return EBTNodeResult::Failed;

	FVector Origin = OwnerComp.GetBlackboardComponent()->GetValueAsVector(AEnemyAIController::HomePosKey);
	FNavLocation NextPos;

	if (NavSystem->GetRandomReachablePointInRadius(Origin, 1000.0f, NextPos))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(AEnemyAIController::PatrolPosKey, NextPos.Location);
		Cast<ACharacter>(ControllingPawn)->GetCharacterMovement()->MaxWalkSpeed = 100.0f;
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}