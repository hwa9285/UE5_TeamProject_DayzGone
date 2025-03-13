// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/ItemBase.h"
#include "AmmoItem.generated.h"

/**
 * 
 */
UCLASS()
class DAYSGONE_API AAmmoItem : public AItemBase
{
	GENERATED_BODY()

public:
	
	AAmmoItem();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ingredient")
	int32 MaxQuantity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ingredient")
	EAmmoType AmmoType;
	
	void Initialize(const FAmmoData& data);

	virtual void InitializeItemFromDataTable(UDataTable* DataTable, int32 ItemId, TSubclassOf<AItemBase> ItemClass) override;
};
