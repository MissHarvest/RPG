// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Attack.h"
#include "EnemyAIController.h"
#include "EnemyCharacter.h"
#include <Kismet/KismetSystemLibrary.h>

UBTTask_Attack::UBTTask_Attack()
{
	NodeName = TEXT("Attack");
	//bNotifyTick = true;
	Duration = 0;
	num = 0;
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto ControllingPawn = Cast<AEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == ControllingPawn) return EBTNodeResult::Failed;

	Duration = ControllingPawn->Attack();
	/*if (!ControllingPawn->OnAttackEnd.IsBound())
	{
		ControllingPawn->OnAttackEnd.AddDynamic(this, &UBTTask_Attack::Temp);
	}*/
	FTimerDelegate TimeCallBack;
	TimeCallBack.BindLambda([&] {
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		});
	FTimerHandle TimeHandle;		
	GetWorld()->GetTimerManager().SetTimer(TimeHandle, TimeCallBack, Duration, false);
	bPlayAnimation = true;
	return EBTNodeResult::InProgress;
	// Succeeded, Failed 무한 반복
}

void UBTTask_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	
	if (!bPlayAnimation)
	{
		/*Timer += DeltaSeconds;
		if (Timer > Duration)
		{
			UE_LOG(LogTemp, Warning, TEXT("EBT _ Attack"));
			
			Timer = 0;
			Duration = 0;
		}*/
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}

void UBTTask_Attack::Temp()
{
	//FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	UE_LOG(LogTemp, Warning, TEXT("Temp"));
	bPlayAnimation = false;
}