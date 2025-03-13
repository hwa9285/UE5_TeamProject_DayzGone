// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/WidgetBase.h"
#include "TabWidgetBase.generated.h"

UENUM(Blueprintable)
enum class ETabType: uint8
{
	Equip,
	Supplies,
	Ingredient,
	Recipe
};
/**
 * 
 */
UCLASS()
class DAYSGONE_API UTabWidgetBase : public UWidgetBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TabType")
	ETabType TabName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OwningWidget")
	UWidgetBase* Ownner;
	
};
