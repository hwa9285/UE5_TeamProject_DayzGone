// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/ItemBase.h"
#include "IngredientItem.generated.h"

/**
 * 
 */
UCLASS()
class DAYSGONE_API AIngredientItem : public AItemBase
{
	GENERATED_BODY()

public:
	AIngredientItem();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ingredient")
	int32 MaxQuantity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ingredient")
	FGameplayTag RecipeTag;
	
	void Initialize(const FIngredientItemData& data);

	virtual void InitializeItemFromDataTable(UDataTable* DataTable, int32 ItemId, TSubclassOf<AItemBase> ItemClass) override;
	
};
