// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Combat/PawnCombatComponent.h"
#include "GameplayTagContainer.h"
#include "Interfaces/PawnUIInterface.h"
#include "HumanCombatComponent.generated.h"

//class AMeleeWeaponBase;

class AHumanWeaponBase;

UENUM(BlueprintType)
enum class EActivatedWeaponType : uint8
{
	Primary,
	Secondary,
	Special,
	Melee,
	None
};

UENUM(BlueprintType)
enum class EToggleDamageType : uint8
{
	CurrentEquippedWeapon,
	LeftHand,
	RightHand,
};
/**
 * 
 */
UCLASS()
class DAYSGONE_API UHumanCombatComponent : public UPawnCombatComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Player")
	void RegisterSpawnedWeapon(FGameplayTag WeaponTag, AHumanWeaponBase* Weapon, bool bRegisterAsEquippedWeapon = false);
	
	UFUNCTION(BlueprintCallable, Category = "Player")
	void UnregisterSpawnedWeapon(AHumanWeaponBase* Weapon);

	// 무기를 장착할 때 사용
	UFUNCTION(BlueprintCallable, Category = "Player")
	AHumanWeaponBase* GetCharacterCarriedWeaponByTag(FGameplayTag WeaponTag) const;
	
	// 무기를 장착할 때 사용
	UFUNCTION(BlueprintCallable, Category = "Player")
	AHumanWeaponBase* GetCharacterCarriedWeaponByEnum(EEquipType WeaponType) const;

	UPROPERTY(BlueprintReadWrite, Category = "Player")
	FGameplayTag CurrentEquippedWeaponTag;

	UFUNCTION(BlueprintCallable, Category = "Player")
	AHumanWeaponBase* GetCharacterCurrentEquippedWeapon() const;

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void ToggleWeaponCollision(bool bUse, EToggleDamageType ToggleDamageType = EToggleDamageType::CurrentEquippedWeapon);

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void SetActivatedWeapon(const EActivatedWeaponType WeaponType)
	{
		ActivatedType = WeaponType;
	}
	
	UFUNCTION(BlueprintPure, Category = "Weapon")
	EActivatedWeaponType GetActivatedWeapon() const
	{
		return ActivatedType;
	}

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void SpawnWeaponInCharacterBackSocket(TSubclassOf<AHumanWeaponBase> Weapon);

	//HitDetection
	virtual void OnHitTargetActor(AActor* HitActor);
	virtual void OnHitScanTargetActor(AActor* HitActor);
	virtual void OnWeaponPulledFromTargetActor(AActor* InteractedActor);

protected:
	TArray<AActor*> OverlappedActors;
	EActivatedWeaponType ActivatedType;

private:
	TMap<FGameplayTag, AHumanWeaponBase*> CharacterCarriedWeaponMap;
};