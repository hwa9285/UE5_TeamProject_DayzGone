// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/SuppliesItem.h"

ASuppliesItem::ASuppliesItem()
{
	ItemType = EItemType::Supplies;
}

void ASuppliesItem::InitializeItemFromDataTable(UDataTable* DataTable, int32 ItemId, TSubclassOf<AItemBase> ItemClass)
{
	Super::InitializeItemFromDataTable(DataTable, ItemId, ItemClass);
	
	FSuppliesItemData* SuppliesItemData = DataTable->FindRow<FSuppliesItemData>(FName(*FString::FromInt(ItemId)),TEXT("Ingredient Initialization"),true);
	if (SuppliesItemData)
	{
		MaxQuantity = SuppliesItemData->MaxQuantity;
		SuppliesType = SuppliesItemData->SuppliesType;
	}

	Initialize(*SuppliesItemData);
	
}
