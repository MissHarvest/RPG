// Fill out your copyright notice in the Description page of Project Settings.

// DefaultScreen
#include "DefaultScreenWidget.h"

// Widget
#include <Components/ProgressBar.h>
#include <Components/TextBlock.h>
#include <Components/Image.h>

// Other Class
#include "StatComponent.h"

void UDefaultScreenWidget::LinkStatController(class UStatComponent* StatComponent)
{
	StatComponent->OnHpChanged.AddDynamic(this, &UDefaultScreenWidget::SetHpPercent);
}

void UDefaultScreenWidget::SetHpPercent(float Percent)
{
	HpBar->SetPercent(Percent);
}