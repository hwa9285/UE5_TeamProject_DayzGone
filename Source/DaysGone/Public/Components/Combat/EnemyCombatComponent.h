// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Combat/PawnCombatComponent.h"
#include "EnemyCombatComponent.generated.h"

class AWeaponBase;
// UENUM(BlueprintType)
// enum class EToggleDamageType : uint8
// {
// 	CurrentEquippedWeapon,
// 	LeftHand,
// 	RightHand,
// };
/**
 * 
 */
UCLASS()
class DAYSGONE_API UEnemyCombatComponent : public UPawnCombatComponent
{
	GENERATED_BODY()

private:
	UPROPERTY()
	TArray<AWeaponBase*> Weapons;

public:
	virtual void OnHitTargetActor(AActor* HitActor) override;
	
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void ToggleWeaponCollision(bool bUse);

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void SetWeapons(AWeaponBase* Weapon);
};
