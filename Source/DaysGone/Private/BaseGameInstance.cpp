// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGameInstance.h"

#include "AbilitySystem/BaseAttributeSet.h"
#include "Characters/EnemyCharacter.h"
#include "Characters/PlayerCharacter.h"
#include "Components/Inventory/InventoryComponent.h"

void UBaseGameInstance::SaveGame(UInventoryComponent* CurrentInventory, FVector CurrentLocation, APlayerCharacter* CurrentPlayer)
{
	SaveData.RangeWeaponInventory = CurrentInventory->RangeWeaponInventory;
	SaveData.OwningMeleeWeapon = CurrentInventory->OwningMeleeWeapon;
	SaveData.IngredientInventory = CurrentInventory->IngredientInventory;
	SaveData.SuppliesInventory = CurrentInventory->SuppliesInventory;
	SaveData.AmmoInventory = CurrentInventory->AmmoInventory;
	SaveData.DiscoverStatus = CurrentInventory->DiscoverStatus;
	
	SaveData.PlayerLocation = CurrentLocation;

	//SaveData.PlayerHealth = CurrentPlayer->GetBaseAttributeSet()->GetCurrentHP();
	
	CurrentSaveID += 1;
	SaveData.SaveID = CurrentSaveID;
}

void UBaseGameInstance::LoadGame(FPlayerSaveData LoadPreSaveData)
{
	LoadPreSaveData = SaveData;
}

