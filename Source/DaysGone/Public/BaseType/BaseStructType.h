// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/DataTable.h"
#include "BaseEnumType.h"
#include "GameplayTagContainer.h"
#include "ScalableFloat.h"
#include "BaseStructType.generated.h"

class ULinkedAnimLayer;
class UPlayerGameplayAbility;
class UInputMappingContext;
class USkeletalMesh;

USTRUCT(BlueprintType)
struct FHumanAbilitySet
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "InputTag"))
	FGameplayTag InputTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UPlayerGameplayAbility> AbilityToGrant;

	bool IsValid() const;
};

USTRUCT(BlueprintType)
struct FWeaponData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<ULinkedAnimLayer> WeaponAnimLayerToLink;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputMappingContext* WeaponInputMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty = "InputTag"))
	TArray<FHumanAbilitySet> WeaponAbilities;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FScalableFloat WeaponBaseDamage;

};

// 무기 타입에 따른 이벤트들
USTRUCT(BlueprintType)
struct FWeaponEventData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag WeaponTag;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName BackSocketName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag EquipEventTag;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAnimMontage* equipMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag UnquipEventTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAnimMontage* UnequipMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAnimMontage* ShotMontage;
};

USTRUCT(BlueprintType)
struct FItemDataBase:public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ItemID;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ItemName;
	
	//아이템 설명
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ItemDescription;

	//장비 탭에 들어가는 택스쳐
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* EquipInventoryTexture;
	
	//인벤토리에 들어가는 텍스쳐
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* InventoryTexture;
	
	//Wheel에 들어가는 텍스쳐
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* ItemWheelIcon;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag ItemTag;
};

USTRUCT(BlueprintType)
struct FWeaponAttackMontageData:public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag ItemTag;
};

USTRUCT(BlueprintType)
struct FAmmoData :public FItemDataBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
	EAmmoType AmmoType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
	int32 MaxQuantity;
};

USTRUCT(BlueprintType)
struct FIngredientItemData : public FItemDataBase
{
	GENERATED_BODY()

	//최대 소지개수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ingredient")
	int32 MaxQuantity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ingredient")
	FGameplayTag RecipeTag;
};

USTRUCT(BlueprintType)
struct FSuppliesItemData : public FItemDataBase
{
	GENERATED_BODY()

	//최대 소지개수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Supplies")
	int32 MaxQuantity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Supplies")
	ESuppliesType SuppliesType;
};
USTRUCT(BlueprintType)
struct FHumanWeaponData : public FItemDataBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<ULinkedAnimLayer> WeaponAnimLayerToLink;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputMappingContext* WeaponInputMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty = "InputTag"))
	TArray<FHumanAbilitySet> WeaponAbilities;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	USkeletalMesh* WeaponSkeletalMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float Damage;
	
	//총알 사거리
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Range")
	float Range;

	//정확도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Range")
	float Accuracy;

	//발사속도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Range")
	float FireRate;

	//관통
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Range")
	float Penetration;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float StoppingPower;
	
	//최대 탄약수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Range")
	float MaxMagazine;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Melee")
	float Durability;

	//쓰는 탄약 종류
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Range")
	EAmmoType AmmoType;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	FGameplayTag WeaponType;
};

USTRUCT(BlueprintType)
struct FRecipeData
{
	GENERATED_BODY()

	//제작에 필요한 아이템 태그
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Recipe")
	TArray<FGameplayTag> RecipeTags;

	//제작하고 나온 아이템 결과
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Recipe")
	FGameplayTag Result;

	//제작된 아이템 수량
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Recipe")
	int32 Quantity;
};

USTRUCT(BlueprintType)
struct FQuestData
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Quest")
	FString QuestName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Quest")
	FString QuestDescription;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Quest")
	bool bIsComplete;
};

USTRUCT(BlueprintType)
struct FInventoryItem
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag ItemTag;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Quantity;
};

USTRUCT(BlueprintType)
struct FAmmoInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CurrentQuantity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxQuantity;
	
};