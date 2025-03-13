// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Widget/ActorUIComponent.h"
#include "PlayerUIComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnWeaponInfoChangeDelegate, UTexture2D*, WeaponTexture, float, CurrentAmmo, float, MaxAmmo);

/**
 * 
 */
UCLASS()
class DAYSGONE_API UPlayerUIComponent : public UActorUIComponent
{
	GENERATED_BODY()
		
public:
	UPROPERTY(BlueprintAssignable)
	FOnWeaponInfoChangeDelegate OnCurrentWeaponChanged;
};
