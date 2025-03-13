// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/WidgetBase.h"
#include "WheelBase.generated.h"

class APlayerCharacter;
class UInventoryComponent;
/**
 * 
 */
UCLASS()
class DAYSGONE_API UWheelBase : public UWidgetBase
{
	GENERATED_BODY()

	//Wheel이 가지고 있어야 할 것
	//그냥 캐릭터의 인벤토리를 가지고 있어야함.
public:
	//UFUNCTION(BlueprintCallable, Category = "Inventory")
	//void UpdateInventoryDisplay();

	UFUNCTION(BlueprintPure)
	float GetMouseRotation();
	
protected:
	//UPROPERTY(meta = (BindWidget))
	//UVerticalBox* InventoryListBox;
	
	UPROPERTY()
	APlayerCharacter* PlayerCharacter;

	
	
	
};
