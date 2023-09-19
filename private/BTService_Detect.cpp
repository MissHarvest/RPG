// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_Detect.h"
#include "AIController.h"
#include "EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_Detect::UBTService_Detect()
{
	NodeName = TEXT("Detect");
	Interval = 1.0f; 
}

void UBTService_Detect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	UE_LOG(LogTemp, Warning, TEXT("BT_AI_Detect_Tick"));
	auto ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();

	auto Target = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AEnemyAIController::TargetActor));
	auto Distance = ControllingPawn->GetDistanceTo(Target);

	OwnerComp.GetBlackboardComponent()->SetValueAsBool(AEnemyAIController::CanAttack, Distance > AttackRange ? false : true);
}
