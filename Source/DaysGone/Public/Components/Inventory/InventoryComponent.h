// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseType/BaseStructType.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"


class AMeleeWeapon;
class AMeleeWeaponBase;
class ARangeWeapon;
class AItemBase;
class ASuppliesItem;
class AIngredientItem;
class AHumanWeaponBase;


UCLASS()
class DAYSGONE_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInventoryComponent();
private:
	int32 TotalAmmo;
	int32 TempAmmo;
	TArray<EEquipType> OwningType;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ARangeWeapon> PrimaryWeapon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ARangeWeapon> SecondaryWeapon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ARangeWeapon> SpeacialWeapon;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AMeleeWeapon> MeleeWeapon;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TMap<EEquipType,TSubclassOf<ARangeWeapon>> RangeWeaponInventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TSubclassOf<AMeleeWeapon> OwningMeleeWeapon;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TMap<int32,FInventoryItem> IngredientInventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TMap<int32,FInventoryItem> SuppliesInventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TMap<EAmmoType,FAmmoInfo> AmmoInventory;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TMap<int32, bool> DiscoverStatus;

	bool IsItemDiscovered(int32 ItemID);

	void DisCoverItem(int32 ItemID);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void InitializeInventory(UDataTable* IngredientTable,UDataTable* SuppliesTable,UDataTable* AmmoTable);

public:
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void AddItem(EItemType _Type,int32 ItemId);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool RemoveItem(EItemType _Type,int32 ItemId);

	UFUNCTION(BlueprintCallable, Category = "AmmoInventory")
	bool GetCurrentAmmoInfo();

	UFUNCTION(BlueprintCallable,Category="AmmoAddTest")
	TArray<FAmmoInfo> GetCurrentAmmo();
	
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	int32 GetItemQuantity(EItemType _Type,int32 ItemId);

	UFUNCTION(BlueprintCallable,BlueprintPure, Category = "AmmoInventory")
	int32 GetCurrentAmmoQuantity(EAmmoType AmmoType);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool RemoveAmmo(EAmmoType AmmoType);

	UFUNCTION(BlueprintCallable, Category = "Crafting")
	bool CanCrafting(FRecipeData Recipe);

	//무기 변경
	UFUNCTION(BlueprintCallable, Category = "WeaponInventory")
	void AddWeapon(EEquipType _type, TSubclassOf<AHumanWeaponBase> NewWeapon);
	
	
	UFUNCTION(BlueprintCallable, Category = "Drop Weapon")
	void DropWeapon(TSubclassOf<AHumanWeaponBase> PreWeapon);
	
	
};

inline bool UInventoryComponent::RemoveAmmo(EAmmoType AmmoType)
{
	if (AmmoInventory[AmmoType].CurrentQuantity > 0)
	{
		AmmoInventory[AmmoType].CurrentQuantity -=1;
		return true;
	}
	else
	{
		return false;
	}
}
