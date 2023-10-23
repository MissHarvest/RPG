// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetInfoWidget.h"

// Widget
#include <Components/TextBlock.h>
#include <Components/ProgressBar.h>

#include "EnemyCharacter.h"
#include "StatComponent.h"

void UTargetInfoWidget::SetInfo(class AActor* EnemyActor)
{
	auto Actor = Cast<AEnemyCharacter>(EnemyActor);
	if (nullptr == Actor) return;
	if (Enemy == Actor) return;

	Enemy = Cast<AEnemyCharacter>(EnemyActor);
	auto EnemyStat = Enemy->GetStat();
	if (nullptr == EnemyStat) return;
	
	if (EnemyStat->OnHpChanged.IsBound()) EnemyStat->OnHpChanged.Clear();
	EnemyStat->OnHpChanged.AddUniqueDynamic(this, & UTargetInfoWidget::SetHpPercent);
	
	// OnHpChanged 를 Clear 하는거 생각보다 위험한거 아닐까
	// 지금은 체력이 변경되면 UI 만 변경하면 되지만, 그 외에 다른 기능이 해당 델리게이트에 바인딩 되어있으면 문제가 될 것 같음.
	 
	SetHpPercent(EnemyStat->GetHpPercent());
	MonsterLvText->SetText(FText::FromString(FString::FromInt(Enemy->GetStat()->GetLevel())));
	MonsterNameText->SetText(FText::FromString(Enemy->Name));
}

void UTargetInfoWidget::SetHpPercent(float Percent)
{
	UE_LOG(LogTemp, Warning, TEXT("SerHpPercent / TargetWidget(%f)"), Percent);
	MonsterHpBar->SetPercent(Percent);
	if (0 == Percent)
	{
		SetVisibility(ESlateVisibility::Hidden);
	}
}