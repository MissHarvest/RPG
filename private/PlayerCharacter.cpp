// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "Arrow.h"

#include "EnhancedInputComponent.h"
//#include "EnhancedInputSubsystems.h"

APlayerCharacter::APlayerCharacter()
{
	GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -96.0f), FRotator(0, -90, 0));
}

void APlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {

		//Jumping
		EnhancedInputComponent->BindAction(DefaultAttackAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Attack);
	}
}

void APlayerCharacter::Attack(const FInputActionValue& Value)
{
	if (IsValid(ArrowClass))
	{
		auto spawnTransform = GetMesh()->GetSocketTransform("bow_SpawnSocket");
		GetWorld()->SpawnActor<AArrow>(ArrowClass, spawnTransform);
	}
}