// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Inventory/InventoryComponent.h"

#include "BaseType/BaseStructType.h"
#include "Items/AmmoItem.h"
#include "Items/DroppedWeaponBase.h"
#include "Items/IngredientItem.h"
#include "Items/RangeWeapon.h"
#include "Items/SuppliesItem.h"
#include "Slate/SGameLayerManager.h"

UInventoryComponent::UInventoryComponent()
{
	//RangeWeaponInventory.Add(EEquipType::Melee,0);
	
	RangeWeaponInventory.Add(EEquipType::Primary,PrimaryWeapon);
	RangeWeaponInventory.Add(EEquipType::Secondary,SecondaryWeapon);
	RangeWeaponInventory.Add(EEquipType::Special,SpeacialWeapon);
	OwningMeleeWeapon = MeleeWeapon;
	TotalAmmo = 10;
	TempAmmo = TotalAmmo;
}

bool UInventoryComponent::IsItemDiscovered(int32 ItemID)
{
	return DiscoverStatus.Contains(ItemID) && DiscoverStatus[ItemID];
}

void UInventoryComponent::DisCoverItem(int32 ItemID)
{
	DiscoverStatus.Add(ItemID,true);
}

void UInventoryComponent::InitializeInventory(UDataTable* IngredientTable, UDataTable* SuppliesTable, UDataTable* AmmoTable)
{
	if (SuppliesTable)
	{
		for (const FName& RowName : SuppliesTable->GetRowNames())
		{
			FSuppliesItemData* SuppliesItemData = SuppliesTable->FindRow<FSuppliesItemData>(RowName,TEXT("SuppliesData"));
			if (SuppliesItemData)
			{
				ASuppliesItem* NewItem = NewObject<ASuppliesItem>(this);
				NewItem->InitializeItemFromDataTable(SuppliesTable, SuppliesItemData->ItemID,ASuppliesItem::StaticClass());
				UE_LOG(LogTemp, Warning, TEXT("ItemID: %d"),NewItem->GetItemID());
				SuppliesInventory.Add(NewItem->GetItemID(),{NewItem->GetItemTag(),0});;

				DiscoverStatus.Add(NewItem->GetItemID(),0);
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
				NewItem->InitializeItemFromDataTable(IngredientTable,IngredientItemData->ItemID,AIngredientItem::StaticClass());
				UE_LOG(LogTemp, Warning, TEXT("ItemID: %d"),NewItem->GetItemID());
				IngredientInventory.Add(NewItem->GetItemID(),{NewItem->GetItemTag(),0});
				UE_LOG(LogTemp, Warning, TEXT("IngredientInventory Size After Add: %d"),IngredientInventory.Num());
				DiscoverStatus.Add(NewItem->GetItemID(),0);
			}
		}
	}
	if (AmmoTable)
	{
		for (const FName& RowName: AmmoTable->GetRowNames())
		{
			FAmmoData* AmmoData = AmmoTable->FindRow<FAmmoData>(RowName,TEXT("AmmoData"));
			if (AmmoData)
			{
				AAmmoItem* NewItem = NewObject<AAmmoItem>(this);
				NewItem->InitializeItemFromDataTable(AmmoTable,AmmoData->ItemID,AAmmoItem::StaticClass());
				AmmoInventory.Add(NewItem->AmmoType,{5,NewItem->MaxQuantity});
			}
		}
	}
}

void UInventoryComponent::AddItem(EItemType _Type,int32 ItemId)
{

	if (_Type != EItemType::Ammo)
	{
		if (!DiscoverStatus[ItemId])
		{
			//처음 발견한 아이템일 경우 true로 변환
			DisCoverItem(ItemId);
		}
	}
	
	switch (_Type)
	{
	case EItemType::Supplies:
		SuppliesInventory[ItemId].Quantity += 1;
		break;
	case EItemType::Ingredients:
		IngredientInventory[ItemId].Quantity += 1;
		break;
	case EItemType::Ammo:
		UE_LOG(LogTemp, Warning, TEXT("Ammo Add"));
		for (auto& OwningItem : RangeWeaponInventory)
		{
			if (OwningItem.Value)
			{
				FActorSpawnParameters SpawnParams;
				SpawnParams.Owner = GetOwner();

				ARangeWeapon* TempWeapon = GetWorld()->SpawnActor<ARangeWeapon>(OwningItem.Value,SpawnParams);

				if (TempWeapon)
				{
					EAmmoType WeaponAmmoType = TempWeapon->GetAmmoType();
					if (AmmoInventory.Contains(WeaponAmmoType))
					{
						OwningType.Add(OwningItem.Key);
						UE_LOG(LogTemp,Warning,TEXT("ItemType: %d"),OwningItem.Key);
					}
					TempWeapon->Destroy();
				}
			}
		}
		
		//총알을 먹을 수 있는 상태긴 해야함.
		while (TempAmmo>0 && OwningType.Num() > 0)
		{
			int32 RandomIndex = FMath::RandRange(0,OwningType.Num()-1);
			EEquipType SelectedEquipType = OwningType[RandomIndex];

			TSubclassOf<ARangeWeapon> WeaponClass = RangeWeaponInventory[SelectedEquipType];
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = GetOwner();
			ARangeWeapon* TempWeapon = GetWorld()->SpawnActor<ARangeWeapon>(WeaponClass,SpawnParams);

			if (TempWeapon)
			{
				EAmmoType SeletecAmmoType = TempWeapon->GetAmmoType();
				if (AmmoInventory.Contains(SeletecAmmoType))
				{
					FAmmoInfo& SelectedAmmoInfo = AmmoInventory[SeletecAmmoType];

					int32 AvailableSpace = SelectedAmmoInfo.MaxQuantity - SelectedAmmoInfo.CurrentQuantity;
					if (AvailableSpace > 0)
					{
						int32 AmmoToAdd = FMath::Min(FMath::RandRange(1,TempAmmo),AvailableSpace);

						SelectedAmmoInfo.CurrentQuantity += AmmoToAdd;
						TempAmmo -= AmmoToAdd;
					}
					else
					{
						OwningType.RemoveAt(RandomIndex);
					}
				}
			}
			TempWeapon->Destroy();
		}
		TempAmmo = TotalAmmo;
		OwningType.Empty();
	default:
		break;
	}
	
}

bool UInventoryComponent::RemoveItem(EItemType _Type, int32 ItemId)
{
	if (GetItemQuantity(_Type,ItemId) > 0)
	{
		switch (_Type)
		{
		case EItemType::Supplies:
			SuppliesInventory[ItemId].Quantity -= 1;
			return true;
		case EItemType::Ingredients:
			IngredientInventory[ItemId].Quantity -= 1;
			return true;
		case EItemType::Ammo:
			return true;
		case EItemType::Weapon:
			return true; // 착용로직
			
		default:
				return false;
		}	
	}
	else
	{
		return false;
	}
}

bool UInventoryComponent::GetCurrentAmmoInfo()
{
	//플레이어가 착용중인 무기의 총알 타입에 따라 AmmoInventory에서 Value값을 전부 반환해줘야함.
	TArray<FAmmoInfo> CurrentEquipAmmo;
	
	
	TArray<TSubclassOf<ARangeWeapon>> RangeWeapons;
	RangeWeaponInventory.GenerateValueArray(RangeWeapons);
	
	for (TSubclassOf<ARangeWeapon> Weapon: RangeWeapons)
	{
		if (Weapon)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = GetOwner();
			SpawnParams.Instigator = GetOwner()->GetInstigator();

			ARangeWeapon* WeaponInstance = GetWorld()->SpawnActor<ARangeWeapon>(Weapon, SpawnParams);
			//총알 인벤토리에서 플레이어가 착용중인 무기의 총알 타입이 총알 인벤토리에 몇개가 있는지
			//이대로 반환하면 총알의 현재 개수와 Max개수만 반환함. 타입을 반환하지 않음.
			//구조체를 하나 더 만들어서 AmmoType과 Maxquantity를 반환?
			//이렇게 할 경우 캐릭터가
			if (AmmoInventory[WeaponInstance->GetAmmoType()].CurrentQuantity < AmmoInventory[WeaponInstance->GetAmmoType()].MaxQuantity)
			{
				WeaponInstance->Destroy();
				return true;
			}
			WeaponInstance->Destroy();
			return false;
		}
	}
	
	return false;
}

TArray<FAmmoInfo> UInventoryComponent::GetCurrentAmmo()
{
	TArray<FAmmoInfo> CurrentAmmo;
	for (auto& Quantity :AmmoInventory)
	{
		CurrentAmmo.Add(Quantity.Value);
	}
	return CurrentAmmo;
}

int32 UInventoryComponent::GetItemQuantity(EItemType _Type,int32 ItemId)
{
	switch (_Type)
	{
		case EItemType::Supplies:
			return SuppliesInventory[ItemId].Quantity;
		case EItemType::Ingredients:
			return IngredientInventory[ItemId].Quantity;
		case EItemType::Ammo:
			return 0;
		default:
			return 0;
	}
}

int32 UInventoryComponent::GetCurrentAmmoQuantity(EAmmoType AmmoType)
{
	return AmmoInventory[AmmoType].CurrentQuantity;
}



bool UInventoryComponent::CanCrafting(FRecipeData Recipe)
{
	for (const FGameplayTag& RequiredTag:Recipe.RecipeTags)
	{
		//int32 Quantity = GetItemQuantity();
	}
	return true;
}

void UInventoryComponent::AddWeapon(EEquipType _type, TSubclassOf<AHumanWeaponBase> NewWeapon)
{
	switch (_type)
	{
	case EEquipType::Melee:
		OwningMeleeWeapon = NewWeapon;
		break;
	default:
		RangeWeaponInventory.Add(_type ,TSubclassOf<ARangeWeapon>(NewWeapon));
		break;
	}
}

void UInventoryComponent::DropWeapon(TSubclassOf<AHumanWeaponBase> PreWeapon)
{
	FActorSpawnParameters PreWeaponSpawnParams;
	PreWeaponSpawnParams.Owner = GetOwner();
	PreWeaponSpawnParams.Instigator = GetOwner()->GetInstigator();

	AHumanWeaponBase* WeaponInstance = GetWorld()->SpawnActor<AHumanWeaponBase>(PreWeapon, PreWeaponSpawnParams);
	
	FVector DropLocation = GetOwner()->GetActorLocation();

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = GetOwner();
	SpawnParams.Instigator = GetOwner()->GetInstigator();
	
	ADroppedWeaponBase* DroppedWeapon = GetWorld()->SpawnActor<ADroppedWeaponBase>
	(WeaponInstance->GetDroppedWeaponClass(),
		DropLocation,
		FRotator::ZeroRotator,
		SpawnParams);

	if (DroppedWeapon)
	{
		WeaponInstance->Destroy();
	}
	
}

