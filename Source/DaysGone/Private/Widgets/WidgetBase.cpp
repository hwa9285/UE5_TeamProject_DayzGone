// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/WidgetBase.h"

#include "Components/Image.h"
#include "Interfaces/PawnUIInterface.h"
#include "Materials/MaterialInstanceDynamic.h"

void UWidgetBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (IPawnUIInterface* PawnUIInterface = Cast<IPawnUIInterface>(GetOwningPlayerPawn()))
	{
		if (UPlayerUIComponent* PlayerUIComponent = PawnUIInterface->GetPlayerUIComponent())
		{
			BP_OnOwningPlayerUIComponentInitialized(PlayerUIComponent);
		}
	}
}

void UWidgetBase::SetDynamicTexture(UMaterialInstanceDynamic* DynamicMaterial, UTexture2D* InventoryIcon)
{
	if (DynamicMaterial && InventoryIcon)
	{
		DynamicMaterial->SetTextureParameterValue("ItemTexture", InventoryIcon);
	}
}


void UWidgetBase::SetWidgetText(UTextBlock* TextWidget, FString _String)
{
	if (TextWidget)
	{
		TextWidget->SetText(FText::FromString(_String));
	}
}




