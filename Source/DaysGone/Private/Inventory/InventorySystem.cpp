// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/InventorySystem.h"

#include "Items/IngredientItem.h"
#include "Items/SuppliesItem.h"

bool UInventorySystem::IsItemDiscovered(int32 ItemID)
{
	return DiscoverStatus.Contains(ItemID) && DiscoverStatus[ItemID];
}

void UInventorySystem::DisCoverItem(int32 ItemID)
{
	DiscoverStatus.Add(ItemID,true);
}

void UInventorySystem::InitializeInventory(UDataTable* IngredientTable, UDataTable* SuppliesTable)
{
	if (SuppliesTable)
	{
		for (const FName& RowName : SuppliesTable->GetRowNames())
		{
			FSuppliesItemData* SuppliesItemData = SuppliesTable->FindRow<FSuppliesItemData>(RowName,TEXT("SuppliesItemData"));
			if (SuppliesItemData)
			{
				ASuppliesItem* NewItem = NewObject<ASuppliesItem>(this);
				NewItem->InitializeItemFromDataTable(SuppliesTable, FCString::Atoi(*RowName.ToString()),ASuppliesItem::StaticClass());
			}
		}
	}
	if (IngredientTable)
	{
		for (const FName& RowName : IngredientTable->GetRowNames())
		{
			FIngredientItemData* IngredientItemData = IngredientTable->FindRow<FIngredientItemData>(RowName,TEXT("IngredientItemData"));
			if (IngredientItemData)
			{
				AIngredientItem* NewItem = NewObject<AIngredientItem>(this);
				NewItem->InitializeItemFromDataTable(IngredientTable,FCString::Atoi(*RowName.ToString()),AIngredientItem::StaticClass());
			}
		}
	}
}
