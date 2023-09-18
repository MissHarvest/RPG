// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UAIPerceptionComponent* AIPerception;

public:
	AEnemyAIController();

	static const FName HomePosKey;
	static const FName PatrolPosKey;
	static const FName TargetActor;
	static const FName CanAttack;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BehaviorTree")
	class UBlackboardData* BBD;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BehaviorTree")
	class UBehaviorTree* BehaviorTree;

protected:
	//virtual void BeginPlay() override;

	virtual void OnPossess(APawn* InPawn) override;
};
