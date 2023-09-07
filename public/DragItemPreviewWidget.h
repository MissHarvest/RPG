// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DragItemPreviewWidget.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API UDragItemPreviewWidget : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item", meta = (BindWidget, AllowPrivateAccess = "true"))
	class UImage* Thumbnail;

public:
	void SetThumbnail(class UTexture2D* Texture);
};
