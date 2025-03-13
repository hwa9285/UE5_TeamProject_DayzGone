// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/DroppedItem.h"
#include "Components/WidgetComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Widgets/WidgetBase.h"

// Sets default values
ADroppedItem::ADroppedItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//bCanPickup = false;
	HoldingTime = 1.f;
	
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	RootComponent = ItemMesh;

	InteractWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractWidget"));
	InteractWidget->SetupAttachment(RootComponent);
	InteractWidget->SetVisibility(false);
	//InteractWidget->SetRelativeLocation(FVector(0,0,40));
	//InteractWidget->SetDrawSize(FVector2d(32,32));
	
	InteractWidget->SetWidgetClass(CanNotPickupWidget); //이미지 설정 해둬야함.

	UWidgetBase* CurrentWidget = Cast<UWidgetBase>(InteractWidget->GetUserWidgetObject());
	if (CurrentWidget)
	{
		CurrentWidget->SetTexture(ItemIcon);
	}

	ItemID = 0;
	
}

bool ADroppedItem::IsPickupable_Implementation() const
{
	return bCanPickup;
}

void ADroppedItem::OnInteract_Implementation(AActor* Interactor)
{
	if (bCanPickup)
	{
		Destroy();
	}
}

void ADroppedItem::OnItemOverlap_Implementation(bool Item_CanPickUp)
{
	InteractWidget->SetWidgetClass(CanNotPickupWidget);
	InteractWidget->SetRelativeLocation(FVector(0,0,40));
	InteractWidget->SetDrawSize(FVector2d(20,20));
	UWidgetBase* CurrentWidget = Cast<UWidgetBase>(InteractWidget->GetUserWidgetObject());
	if (CurrentWidget)
	{
		CurrentWidget->SetMaterialParameter(Item_CanPickUp);
		CurrentWidget->SetTexture(ItemIcon);
		InteractWidget->SetVisibility(true);
	}
}

void ADroppedItem::OnItemOverlapEnd_Implementation()
{
	InteractWidget->SetVisibility(false);
}

void ADroppedItem::Set_Item_WidgetClass_Implementation(bool Item_CanPickUP)
{
	//캐릭터에서 값 비교후 넘겨줄것임. 개수에따른 위젯 변경이 필요 할때만 호출.
	if (Item_CanPickUP)
	{
		InteractWidget -> SetWidgetClass(CanPickupWidget);
		UWidgetBase* CurrentWidget = Cast<UWidgetBase>(InteractWidget->GetUserWidgetObject());
		if (CurrentWidget)
		{
			CurrentWidget->SetTexture(ItemIcon);
		}
		InteractWidget -> SetRelativeLocation(FVector(0,0,80));
		InteractWidget -> SetDrawSize(FVector2d(20,40));
		
	}
	else
	{
		InteractWidget -> SetWidgetClass(CanNotPickupWidget);
		InteractWidget -> SetRelativeLocation(FVector(0,0,40));
		InteractWidget -> SetDrawSize(FVector2d(20,20));
		
	}
}

void ADroppedItem::UpdateHoldProgress_Implementation(float Progress)
{
	UWidgetBase* CurrentWidget = Cast<UWidgetBase>(InteractWidget->GetUserWidgetObject());
	if (CurrentWidget)
	{
		//위젯 블루프린트에서 호출할거임. 상호작용중인 위젯만 적용할것.
		CurrentWidget->SetDynamicPercentParameter(Progress);
	}
}

void ADroppedItem::Set_ItemWidget_CanNotPickup_Implementation()
{
	
	
	
}

void ADroppedItem::UpdateItemWidgetRotation_Implementation(FVector Target)
{
	InteractWidget->SetWorldRotation(Target.Rotation());
	//InteractWidget -> SetRelativeRotation(TargetRotator);
}

void ADroppedItem::StartRotation()
{
}

void ADroppedItem::EndRotation()
{
}

void ADroppedItem::SetWidgetRotation()
{
}








