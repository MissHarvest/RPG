// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageWidget.h"
#include <Components/TextBlock.h>

void UDamageWidget::SetTextOfDamage(FText Damage)
{
	DamageText->SetText(Damage);
}