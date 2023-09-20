// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Chase.h"
#include <AIController.h>
#include <NavigationSystem.h>
#include <BehaviorTree/BlackboardComponent.h>
#include "EnemyAIController.h"
#include <Kismet/KismetMathLibrary.h>
#include "EnemyCharacter.h"
#include <GameFramework/CharacterMovementComponent.h>

UBTTask_Chase::UBTTask_Chase()
{
	NodeName = TEXT("Chase");
}

EBTNodeResult::Type UBTTask_Chase::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn) return EBTNodeResult::Failed;

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(ControllingPawn->GetWorld());
	if(nullptr == NavSystem) return EBTNodeResult::Failed;

	auto Target = OwnerComp.GetBlackboardComponent()->GetValueAsObject(AEnemyAIController::TargetActor);
	if (nullptr == Target) return EBTNodeResult::Failed;

	auto TargetPos = Cast<AActor>(Target)->GetActorLocation();
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("TargetPos"), TargetPos);

	auto AIController = Cast<AEnemyAIController>(ControllingPawn->GetController());
	if (nullptr == AIController) return EBTNodeResult::Failed;
	Cast<AEnemyCharacter>(ControllingPawn)->GetCharacterMovement()->MaxWalkSpeed = 500;
	// Blackboard?
	AIController->MoveToActor(Cast<AActor>(Target));
	return EBTNodeResult::Succeeded;
}