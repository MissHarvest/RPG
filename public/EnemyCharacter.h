// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <Engine/DataTable.h>
#include "AttackInterface.h"
#include "EnemyCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE(FAttackEndSignature, AEnemyCharacter, OnAttackEnd);
DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(FDeathSignature, AEnemyCharacter, OnDeath, FName, Name);

UCLASS()
class RPG_API AEnemyCharacter : public ACharacter, public IAttackInterface
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FDataTableRowHandle MonsterDataHandle;
		
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	class UAnimMontage* AttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	class UAnimMontage* DamagedMontage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UStatComponent* Stat;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UDamageIndicatorComponent* DamageIndicatorComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UInventorySystem* TestInven;

public:
	UPROPERTY(VisibleAnywhere)
	FName MID = "130001";

	UPROPERTY()
	int32 CurrentHp;

	UPROPERTY()
	FString Name;

public:
	// Sets default values for this character's properties
	AEnemyCharacter();

	UPROPERTY()
	FAttackEndSignature OnAttackEnd;

	UPROPERTY()
	FDeathSignature OnDeath;

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

	UStatComponent* GetStat() const { return Stat; }
};
