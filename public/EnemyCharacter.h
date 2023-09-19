// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AttackInterface.h"
#include "EnemyCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE(FAttackEndSignature, AEnemyCharacter, OnAttackEnd);

UCLASS()
class RPG_API AEnemyCharacter : public ACharacter, public IAttackInterface
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	class UAnimMontage* AttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	class UAnimMontage* DamagedMontage;

public:
	UPROPERTY()
	int32 CurrentHp;

public:
	// Sets default values for this character's properties
	AEnemyCharacter();

	UPROPERTY()
	FAttackEndSignature OnAttackEnd;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float Attack() override;

	float Damaged();

	float Death();

	UFUNCTION(BlueprintCallable)
	void BroadCastAttackEnd();

	int32 GetHP() const { return CurrentHp; }
};
