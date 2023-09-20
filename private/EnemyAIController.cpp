// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include <BehaviorTree/BehaviorTree.h>
#include "EnemyCharacter.h"
#include <Perception/AIPerceptionComponent.h>
#include "StatComponent.h"

const FName AEnemyAIController::HomePosKey(TEXT("HomePos"));
const FName AEnemyAIController::PatrolPosKey(TEXT("PatrolPos"));
const FName AEnemyAIController::TargetActor(TEXT("TargetActor"));
const FName AEnemyAIController::CanAttack(TEXT("CanAttack"));
const FName AEnemyAIController::Damaged(TEXT("Damaged"));
const FName AEnemyAIController::Death(TEXT("Death"));

AEnemyAIController::AEnemyAIController()
{
	AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception"));
	UE_LOG(LogTemp, Warning, TEXT("Enemy AI Consructor"));
}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	UBlackboardComponent* BlackboardComp = Blackboard;
	RunBehaviorTree(BehaviorTree);
	
	if (UseBlackboard(BBD, BlackboardComp))
	{
		BlackboardComp->SetValueAsVector(HomePosKey, InPawn->GetActorLocation());
	}
}

void AEnemyAIController::ReceiveDamage(class AActor* Attacker)
{
	auto ControllingPawn = GetPawn();
	if (nullptr == ControllingPawn) return;

	auto Enemy = Cast<AEnemyCharacter>(ControllingPawn);
	if (nullptr == Enemy) return;

	UBlackboardComponent* BlackboardComp = Blackboard;

	if (Enemy->GetStat()->GetHpPercent() <= 0)
	{
		if (UseBlackboard(BBD, BlackboardComp))
		{
			BlackboardComp->SetValueAsBool(Death, true);
		}
	}
	else
	{
		if (UseBlackboard(BBD, BlackboardComp))
		{
			BlackboardComp->SetValueAsBool(Damaged, true);
			BlackboardComp->SetValueAsObject(TargetActor, Attacker);
		}
	}
}
