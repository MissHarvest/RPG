// Fill out your copyright notice in the Description page of Project Settings.


#include "Recovery.h"

// Add default functionality here for any IRecovery functions that are not pure virtual.

void UNormalRecovery::Recovery(int32& Target, int32 Amount, FBroadCastSingature InDelegate, int32 Sec)
{
	if (InDelegate.IsBound())
	{
		Target += Amount;
		InDelegate.ExecuteIfBound();
	}
}

void UTickRecovery::Recovery(int32& Target, int32 Amount, FBroadCastSingature InDelegate, int32 Sec)
{
	if (InDelegate.IsBound())
	{
		// ���� ��� while
		Target += Amount;
		InDelegate.ExecuteIfBound();
	}
}