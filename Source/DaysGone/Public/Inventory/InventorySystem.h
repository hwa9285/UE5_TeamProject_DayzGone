// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseType/BaseStructType.h"
#include "UObject/NoExportTypes.h"
#include "InventorySystem.generated.h"

class AItemBase;
class ASuppliesItem;
class AIngredientItem;
class AHumanWeaponBase;
/**
 * 
 */
UCLASS()
class DAYSGONE_API UInventorySystem : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TArray<AHumanWeaponBase*> WeaponInventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TArray<AIngredientItem*> IngredientInventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TArray<ASuppliesItem*> SuppliesInventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TMap<int32, bool> DiscoverStatus;

	bool IsItemDiscovered(int32 ItemID);

	void DisCoverItem(int32 ItemID);

	void InitializeInventory(UDataTable* IngredientTable,UDataTable* SuppliesTable);

public:
	//void AddItem(EItemType _type,int32 ItemId);
	//void RemoveItem(EItemType _type,int32 ItemId);
	
};
