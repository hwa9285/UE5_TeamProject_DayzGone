// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/AmmoItem.h"

AAmmoItem::AAmmoItem()
{
	ItemType = EItemType::Ammo;
}

void AAmmoItem::Initialize(const FAmmoData& data)
{
	Super::Initialize(data);
}

void AAmmoItem::InitializeItemFromDataTable(UDataTable* DataTable, int32 ItemId, TSubclassOf<AItemBase> ItemClass)
{
	Super::InitializeItemFromDataTable(DataTable, ItemId, ItemClass);

	FAmmoData* AmmoData = DataTable->FindRow<FAmmoData>(FName(*FString::FromInt(ItemId)),TEXT("Ingredient Initialization"),true);
	if (AmmoData)
	{
		MaxQuantity = AmmoData->MaxQuantity;
		AmmoType = AmmoData->AmmoType;
	}

	Initialize(*AmmoData);
}
