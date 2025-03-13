// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/DroppedItem.h"
#include "DroppedWeaponBase.generated.h"

class AHumanWeaponBase;
/**
 * 
 */
UCLASS

()
class DAYSGONE_API ADroppedWeaponBase : public ADroppedItem
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="DroppedWeapon")
	EEquipType EquipType;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="DroppedWeapon")
	TSubclassOf<AHumanWeaponBase> WeaponClass;

public:
	UFUNCTION(BlueprintCallable)
	void Drop();
	
public:
	virtual void OnItemOverlap_Implementation(bool Item_CanPickUp) override;
	virtual void Set_Item_WidgetClass_Implementation(bool Item_CanPickUP) override;

	
};
