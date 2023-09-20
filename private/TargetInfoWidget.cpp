// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetInfoWidget.h"

// Widget
#include <Components/TextBlock.h>
#include <Components/ProgressBar.h>

#include "EnemyCharacter.h"
#include "StatComponent.h"

void UTargetInfoWidget::SetInfo(class AActor* EnemyActor)
{
	//LvText->SetText(Lv);
	//NameText->SetText(Name);
	//HpBar->SetPercent(Percent);
	auto Actor = Cast<AEnemyCharacter>(EnemyActor);
	if (nullptr == Actor) return;
	if (Enemy == Actor) return;

	Enemy = Cast<AEnemyCharacter>(EnemyActor);
	if (Enemy->GetStat()->OnHpChanged.IsBound()) Enemy->GetStat()->OnHpChanged.Clear();
	Enemy->GetStat()->OnHpChanged.AddDynamic(this, &UTargetInfoWidget::SetHpPercent);
	SetHpPercent(Enemy->GetStat()->GetHpPercent());
	LvText->SetText(FText::FromString(FString::FromInt(Enemy->GetStat()->GetLevel())));
}

void UTargetInfoWidget::SetHpPercent(float Percent)
{
	UE_LOG(LogTemp, Warning, TEXT("SerHpPercent / TargetWidget(%f)"), Percent);
	HpBar->SetPercent(Percent);
	if (0 == Percent)
	{
		SetVisibility(ESlateVisibility::Hidden);
	}
}