// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RPGCharacter.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API APlayerCharacter : public ARPGCharacter
{
	GENERATED_BODY()
	
	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* DefaultAttackAction;

	// Character Spawn Arrow with this Variable
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AArrow> ArrowClass;

	UPROPERTY()
	class AArrow* Arrow;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	class UAnimMontage* FireAnimMontage;

public:
	APlayerCharacter();

protected:
	//UFUNCTION(BlueprintCallable)//, BlueprintReadOnly, Category = "Attack" , meta = (AllowPrivateAccess = "true")
	void Attack(const FInputActionValue& Value);

	FVector GetFocalPoint();

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
