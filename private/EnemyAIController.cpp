// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include <BehaviorTree/BehaviorTree.h>
#include "EnemyCharacter.h"
#include <Perception/AIPerceptionComponent.h>

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

//void AEnemyAIController::BeginPlay()
//{
//	UE_LOG(LogTemp, Warning, TEXT("Enemy AI Begin"));
//	//GetPawn()->OnTakeAnyDamage.AddDynamic(this, &AEnemyAIController::ReceiveDamage);
//}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	UBlackboardComponent* BlackboardComp = Blackboard;
	RunBehaviorTree(BehaviorTree);
	
	if (UseBlackboard(BBD, BlackboardComp))
	{
		BlackboardComp->SetValueAsVector(HomePosKey, InPawn->GetActorLocation());
	}
	GetPawn()->OnTakeAnyDamage.AddDynamic(this, &AEnemyAIController::ReceiveDamage);
}

void AEnemyAIController::ReceiveDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	UE_LOG(LogTemp, Warning, TEXT("Enemy AI Damaged"));
	UBlackboardComponent* BlackboardComp = Blackboard;
	--Cast<AEnemyCharacter>(DamagedActor)->CurrentHp;
	UE_LOG(LogTemp, Warning, TEXT("Enemy HP : %d"), Cast<AEnemyCharacter>(DamagedActor)->CurrentHp);
	if (Cast<AEnemyCharacter>(DamagedActor)->CurrentHp <= 0)
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
			BlackboardComp->SetValueAsObject(TargetActor, InstigatedBy->GetPawn());
		}
	}
}
