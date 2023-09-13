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

public:
	static const FName HomePosKey;
	static const FName PatrolPosKey;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BehaviorTree")
	class UBlackboardData* BBD;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BehaviorTree")
	class UBehaviorTree* BehaviorTree;

protected:
	virtual void OnPossess(APawn* InPawn) override;
};
