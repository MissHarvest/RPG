// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(FHpChangedSignature, UStatComponent, OnHpChanged, float, Percent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RPG_API UStatComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stat" , meta = (AllowPrivateAccess = "true"))
	int32 CurrentHp; // unsinged?

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stat", meta = (AllowPrivateAccess = "true"))
	int32 MaxHp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stat", meta = (AllowPrivateAccess = "true"))
	int32 CurrentMp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stat", meta = (AllowPrivateAccess = "true"))
	int32 MaxMp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stat", meta = (AllowPrivateAccess = "true"))
	int32 CurrentXp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stat", meta = (AllowPrivateAccess = "true"))
	int32 MaxXp;

	UPROPERTY()
	TScriptInterface<class IRecovery> Normal;

	UPROPERTY()
	TScriptInterface<class IRecovery> Tick;

private:
	void BroadCastHpChange();

	float GetHpPercent();

public:	
	// Sets default values for this component's properties
	UStatComponent();

	UPROPERTY()
	FHpChangedSignature OnHpChanged;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void RecoveryHp(int32 Amount);

	void RecoveryHp(int32 Amount, int32 Sec);

	void RecoveryHp(int32 Amount, TScriptInterface<class IRecovery> RecoveryStrategy);
};
