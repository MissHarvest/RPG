// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Recovery.generated.h"

DECLARE_DELEGATE(FBroadCastSingature);

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class URecovery : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class RPG_API IRecovery
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void Recovery(int32& Target, int32 Amount, FBroadCastSingature InDelegate, int32 Sec = 0) = 0;
};

UCLASS()
class RPG_API UNormalRecovery : public UObject, public IRecovery
{
	GENERATED_BODY()
public:
	virtual void Recovery(int32& Target, int32 Amount, FBroadCastSingature InDelegate, int32 Sec = 0);

};

UCLASS()
class RPG_API UTickRecovery : public UObject, public IRecovery
{
	GENERATED_BODY()
public:
	virtual void Recovery(int32& Target, int32 Amount, FBroadCastSingature InDelegate, int32 Sec = 0);

};