// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetInfoWidget.h"

// Widget
#include <Components/TextBlock.h>
#include <Components/ProgressBar.h>

void UTargetInfoWidget::SetInfo(FText Lv, FText Name, float Percent)
{
	LvText->SetText(Lv);
	NameText->SetText(Name);
	HpBar->SetPercent(Percent);
}