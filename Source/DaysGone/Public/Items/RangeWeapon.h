// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/HumanWeaponBase.h"
#include "RangeWeapon.generated.h"

class APlayerCharacter;
class UInventoryComponent;

UENUM(Blueprintable)
enum class EFireType : uint8
{
	Single,
	Auto
};

/**
 * 
 */
UCLASS()
class DAYSGONE_API ARangeWeapon : public AHumanWeaponBase
{
	GENERATED_BODY()

public:
	ARangeWeapon();

public:
	UFUNCTION(BlueprintCallable, Category = "RangeWeapon")
	void Fire(APlayerCharacter*Player);

	void PerformTrace(APlayerCharacter* Player);
	void EndTrace();
	
	FTimerHandle FireTimer;

	UFUNCTION(BlueprintCallable, Category = "RangeWeapon")
	virtual void Reload(int32 AddAmmo);

	EAmmoType GetAmmoType();

	UFUNCTION(BlueprintCallable, Category = "RangeWeapon")
	void SetAddAmmoAmount(UInventoryComponent* AmmoInven);
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<ULinkedAnimLayer> WeaponAnimLayerToLink;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputMappingContext* WeaponInputMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty = "InputTag"))
	TArray<FHumanAbilitySet> WeaponAbilities;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	USkeletalMeshComponent* WeaponSkeletalMesh;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="FireType")
	EFireType FireType;
	
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

	//쓰는 탄약 종류
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Range")
	EAmmoType AmmoType;
	
	//현재 탄약 수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Range")
	float CurrentAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Range")
	int32 AddAmmoAmount;

	//혜민 - 총 사운드 추가
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Range")
	USoundBase* FireSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Range")
	USoundBase* ReloadSound;

	// 주원 - 무기 타입 추가함
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	FGameplayTag WeaponType;

private:
	TArray<FGameplayAbilitySpecHandle> GrantedAbilitySpecHandles;
	
public:
	virtual void InitializeItemFromDataTable(UDataTable* DataTable, int32 ItemId, TSubclassOf<AItemBase> ItemClass) override;
};
