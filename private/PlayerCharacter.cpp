// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include <GameFramework/CharacterMovementComponent.h>
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>

#include "Arrow.h"

#include "EnhancedInputComponent.h"

#include <Kismet/GameplayStatics.h>
#include <Kismet/KismetMathLibrary.h>
//#include "EnhancedInputSubsystems.h"

APlayerCharacter::APlayerCharacter()
{
	GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -96.0f), FRotator(0, -90, 0));

	GetCharacterMovement()->GravityScale = 1.75f;

	GetCameraBoom()->SetRelativeLocation(FVector(0, 0, 125));
	GetCameraBoom()->TargetArmLength = 700.0f;
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
		if(IsValid(FireAnimMontage))
			PlayAnimMontage(FireAnimMontage, 1.0f, FName("Play"));
		auto FocalPoint = GetFocalPoint();
		auto SpawnLocation = GetMesh()->GetSocketLocation("bow_SpawnSocket");
		auto SpawnRotation = UKismetMathLibrary::MakeRotFromX(FocalPoint - SpawnLocation);
		GetWorld()->SpawnActor<AArrow>(ArrowClass, SpawnLocation, SpawnRotation);
	}
}

FVector APlayerCharacter::GetFocalPoint() // name..
{
	FHitResult HitResult;
	auto Camera = GetFollowCamera();
	FVector StartPoint = Camera->K2_GetComponentLocation();
	FVector FocalPoint = StartPoint + Camera->GetForwardVector() * 15000.0f;
	bool IsHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartPoint, FocalPoint, ECollisionChannel::ECC_Visibility);
	if (IsHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit : %s"), *(HitResult.GetActor()->GetName()));
		return HitResult.ImpactPoint; 
	}
	return FocalPoint;
}