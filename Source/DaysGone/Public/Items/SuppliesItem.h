// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/ItemBase.h"
#include "SuppliesItem.generated.h"

/**
 * 
 */
UCLASS()
class DAYSGONE_API ASuppliesItem : public AItemBase
{
	GENERATED_BODY()

public:
	ASuppliesItem();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Supplies")
	int32 MaxQuantity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Supplies")
	ESuppliesType SuppliesType;

	virtual void InitializeItemFromDataTable(UDataTable* DataTable, int32 ItemId, TSubclassOf<AItemBase> ItemClass) override;
	
};
