// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseType/BaseEnumType.h"
#include "BaseType/BaseStructType.h"
#include "Engine/GameInstance.h"
#include "BaseGameInstance.generated.h"

class APlayerCharacter;
class ARangeWeapon;
class AMeleeWeapon;
class UInventoryComponent;

USTRUCT(BlueprintType)
struct FPlayerSaveData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SaveID;
	
	// 원거리 무기
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EEquipType, TSubclassOf<ARangeWeapon>> RangeWeaponInventory;

	// 근접 무기
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AMeleeWeapon> OwningMeleeWeapon;

	// 재료 아이템
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<int32, FInventoryItem> IngredientInventory;

	// 보급품 아이템
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<int32, FInventoryItem> SuppliesInventory;

	// 탄약
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EAmmoType, FAmmoInfo> AmmoInventory;

	// 발견 상태
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<int32, bool> DiscoverStatus;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector PlayerLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PlayerHealth;
};

USTRUCT(BlueprintType)
struct FEnemySaveData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SaveID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector EnemyLocation;
};

/**
 * 
 */
UCLASS()
class DAYSGONE_API UBaseGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CurrentSaveID = 0;
	
	//저장할 변수, 컴포넌트들
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FPlayerSaveData SaveData;

	//HP컴포넌트 추가시 구조체에 추가 필요 

public:
	UFUNCTION(BlueprintCallable,BlueprintImplementableEvent)
	void Initialize_Data();

	//저장 및 로드
	UFUNCTION(BlueprintCallable)
	void SaveGame(UInventoryComponent* CurrentInventory, FVector CurrentLocation, APlayerCharacter* CurrentPlayer);

	UFUNCTION(BlueprintCallable,BlueprintImplementableEvent)
	void RespawnEnemy();

	UFUNCTION(BlueprintCallable)
	void LoadGame(FPlayerSaveData LoadPreSaveData);

	//퀘스트 관련
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
	TArray<FQuestData> Quests;
	
	UFUNCTION(BlueprintCallable,BlueprintImplementableEvent, Category = "Quest")
	void StartQuest(const FQuestData& Quest);

	UFUNCTION(BlueprintCallable,BlueprintImplementableEvent, Category = "Quest")
	void CompletQuest();
};
