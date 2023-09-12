// Fill out your copyright notice in the Description page of Project Settings.

// DefaultScreen
#include "DefaultScreenWidget.h"

// Widget
#include <Components/ProgressBar.h>
#include <Components/TextBlock.h>
#include <Components/Image.h>
#include "TargetInfoWidget.h"
#include "InventoryWidget.h"

// Other Class
#include "StatComponent.h"

//
#include <Blueprint/WidgetBlueprintLibrary.h>

void UDefaultScreenWidget::LinkStatController(class UStatComponent* StatComponent)
{
	StatComponent->OnHpChanged.AddDynamic(this, &UDefaultScreenWidget::SetHpPercent);
	StatComponent->OnMpChanged.AddDynamic(this, &UDefaultScreenWidget::SetMpPercent);
	StatComponent->OnXpChanged.AddDynamic(this, &UDefaultScreenWidget::SetXpPercent);

	SetHpPercent(StatComponent->GetHpPercent());
	SetMpPercent(StatComponent->GetMpPercent());
	SetXpPercent(StatComponent->GetXpPercent());
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

void UDefaultScreenWidget::ActivateTargetInfo()
{
	TargetInfo->SetVisibility(ESlateVisibility::Visible);
}

void UDefaultScreenWidget::DeactivateTargetInfo()
{
	TargetInfo->SetVisibility(ESlateVisibility::Hidden);
}

void UDefaultScreenWidget::LinkInventory(class UInventorySystem* PlayerInventory)
{
	Inventory->LinkInventory(PlayerInventory);
}

void UDefaultScreenWidget::LinkStorage(class UInventorySystem* StorageInventory)
{
	Storage->LinkInventory(StorageInventory);
}

void UDefaultScreenWidget::ShowInventory()
{
	Inventory->SetVisibility(ESlateVisibility::Visible);
	GetOwningPlayer()->SetShowMouseCursor(true);
	UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(GetOwningPlayer(), Inventory);
}

void UDefaultScreenWidget::HideInventory()
{
	Inventory->SetVisibility(ESlateVisibility::Hidden);
	GetOwningPlayer()->SetShowMouseCursor(false);
	UWidgetBlueprintLibrary::SetInputMode_GameOnly(GetOwningPlayer());
}

void UDefaultScreenWidget::ToggleInventory()
{
	auto InvenVisible = Inventory->GetVisibility();
	switch (InvenVisible)
	{
	case ESlateVisibility::Visible:
		HideInventory();
		break;
	case ESlateVisibility::Hidden:
		ShowInventory();
		break;
	}
}

void UDefaultScreenWidget::ShowStorage()
{
	Storage->SetVisibility(ESlateVisibility::Visible);
	ShowInventory();
}

void UDefaultScreenWidget::HideStorage()
{
	Storage->SetVisibility(ESlateVisibility::Hidden);
	HideInventory();
}

void UDefaultScreenWidget::ToggleStorage()
{
	auto StorageVisible = Storage->GetVisibility();
	switch (StorageVisible)
	{
	case ESlateVisibility::Visible:
		HideStorage();
		break;
	case ESlateVisibility::Hidden:
		ShowStorage();
		break;
	}
}
