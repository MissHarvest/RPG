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
	StatComponent->OnMpChanged.AddDynamic(this, &UDefaultScreenWidget::SetMpPercent);
	StatComponent->OnXpChanged.AddDynamic(this, &UDefaultScreenWidget::SetXpPercent);
}

void UDefaultScreenWidget::SetHpPercent(float Percent)
{
	HpBar->SetPercent(Percent);
}

void UDefaultScreenWidget::SetMpPercent(float Percent)
{
	MpBar->SetPercent(Percent);
}

void UDefaultScreenWidget::SetXpPercent(float Percent)
{
	XpBar->SetPercent(Percent);
}