// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/IngredientItem.h"

AIngredientItem::AIngredientItem()
{
	ItemType = EItemType::Ingredients;
}

void AIngredientItem::Initialize(const FIngredientItemData& data)
{
	Super::Initialize(data);

	//MaxQuantity = data.MaxQuantity;
	//RecipeTag = data.RecipeTag;
}

void AIngredientItem::InitializeItemFromDataTable(UDataTable* DataTable, int32 ItemId, TSubclassOf<AItemBase> ItemClass)
{
	Super::InitializeItemFromDataTable(DataTable, ItemId, ItemClass);

	FIngredientItemData* IngredientItemData = DataTable->FindRow<FIngredientItemData>(FName(*FString::FromInt(ItemId)),TEXT("Ingredient Initialization"),true);
	if (IngredientItemData)
	{
		MaxQuantity = IngredientItemData->MaxQuantity;
		RecipeTag = IngredientItemData->RecipeTag;
	}

	Initialize(*IngredientItemData);
}


