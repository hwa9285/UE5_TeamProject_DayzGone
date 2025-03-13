// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/DroppedWeaponBase.h"

#include "Components/WidgetComponent.h"
#include "Widgets/WidgetBase.h"

void ADroppedWeaponBase::Drop()
{
	
}

void ADroppedWeaponBase::OnItemOverlap_Implementation(bool Item_CanPickUp)
{
	//Super::OnItemOverlap_Implementation(Item_CanPickUp);
	InteractWidget->SetWidgetClass(CanNotPickupWidget);
	InteractWidget->SetRelativeLocation(FVector(0,0,40));
	InteractWidget->SetDrawSize(FVector2d(100,20));
	UWidgetBase* CurrentWidget = Cast<UWidgetBase>(InteractWidget->GetUserWidgetObject());
	if (CurrentWidget)
	{
		CurrentWidget->SetMaterialParameter(Item_CanPickUp);
		CurrentWidget->SetTexture(ItemIcon);
		InteractWidget->SetVisibility(true);
	}
}

void ADroppedWeaponBase::Set_Item_WidgetClass_Implementation(bool Item_CanPickUP)
{
	//Super::Set_Item_WidgetClass_Implementation(Item_CanPickUP);

	if (Item_CanPickUP)
	{
		InteractWidget -> SetWidgetClass(CanPickupWidget);
		UWidgetBase* CurrentWidget = Cast<UWidgetBase>(InteractWidget->GetUserWidgetObject());
		if (CurrentWidget)
		{
			CurrentWidget->SetTexture(ItemIcon);
		}
		InteractWidget -> SetRelativeLocation(FVector(0,0,80));
		InteractWidget -> SetDrawSize(FVector2d(100,64));
		
	}
	else
	{
		InteractWidget -> SetWidgetClass(CanNotPickupWidget);
		InteractWidget -> SetRelativeLocation(FVector(0,0,40));
		InteractWidget -> SetDrawSize(FVector2d(100,20));
		
	}
}
