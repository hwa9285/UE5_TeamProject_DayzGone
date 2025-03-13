// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/WidgetBase.h"
#include "Components/Button.h"
#include "ButtonWidgetBase.generated.h"

class UTabWidgetBase;
/**
 * 
 */
UCLASS()
class DAYSGONE_API UButtonWidgetBase : public UWidgetBase
{
	GENERATED_BODY()

public:
	//버튼은 부모로 탭을 가짐
	//탭은 부모로 widgetbase
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OwningWidget")
	UTabWidgetBase* Owner;


};
