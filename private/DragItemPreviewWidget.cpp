// Fill out your copyright notice in the Description page of Project Settings.


#include "DragItemPreviewWidget.h"
#include <Components/Image.h>
#include <Engine/Texture2D.h>

void UDragItemPreviewWidget::SetThumbnail(class UTexture2D* Texture)
{
	Thumbnail->SetBrushFromTexture(Texture);
}