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
	
	// OnHpChanged �� Clear �ϴ°� �������� �����Ѱ� �ƴұ�
	// ������ ü���� ����Ǹ� UI �� �����ϸ� ������, �� �ܿ� �ٸ� ����� �ش� ��������Ʈ�� ���ε� �Ǿ������� ������ �� �� ����.
	 
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