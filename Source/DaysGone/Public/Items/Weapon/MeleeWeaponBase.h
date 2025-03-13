// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Weapon/WeaponBase.h"
#include "BaseType/BaseStructType.h"
#include "GameplayAbilitySpecHandle.h"
#include "MeleeWeaponBase.generated.h"

DECLARE_DELEGATE_OneParam(FOnTargetInteractedDelegate, AActor*)

class UBoxComponent;
/**
 * 
 */
UCLASS()
class DAYSGONE_API AMeleeWeaponBase : public AWeaponBase
{
public:
	
	GENERATED_BODY()

private:
	TArray<FGameplayAbilitySpecHandle> GrantedAbilitySpecHandles;
};
