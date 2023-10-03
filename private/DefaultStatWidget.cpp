// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultStatWidget.h"
#include "PlayerCharacter.h"

#include "StatComponent.h"
#include <Components/ProgressBar.h>

void UDefaultStatWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	auto OwingPawn = Cast<APlayerCharacter>(GetOwningPlayerPawn());
	if (nullptr == OwingPawn) return;

	StatModel = OwingPawn->GetStatComponent();
	if (nullptr == StatModel) return;

	StatModel->OnHpChanged.AddDynamic(this, &UDefaultStatWidget::SetHpPercent);
	StatModel->OnMpChanged.AddDynamic(this, &UDefaultStatWidget::SetMpPercent);
}

void UDefaultStatWidget::SetHpPercent(float Percent)
{
	HpBar->SetPercent(Percent);
}

void UDefaultStatWidget::SetMpPercent(float Percent)
{
	MpBar->SetPercent(Percent);
}