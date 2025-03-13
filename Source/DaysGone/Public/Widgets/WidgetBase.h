// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "WidgetBase.generated.h"

class UImage;
class UPlayerUIComponent;
/**
 * 
 */
UCLASS()
class DAYSGONE_API UWidgetBase : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeOnInitialized() override;

	UFUNCTION(BlueprintImplementableEvent)
	void BP_OnOwningPlayerUIComponentInitialized(UPlayerUIComponent* PlayerUIComponent);
	
	//UPROPERTY(BlueprintReadOnly, Category = "Material")
	//class UMaterialInstanceDynamic* DynamicMaterialInstance;

public:
	UFUNCTION(BlueprintCallable,BlueprintImplementableEvent)
	void UpdateWidget(UTexture2D* Icon, bool value);

	UFUNCTION(BlueprintImplementableEvent)
	void SetMaterialParameter(bool Value);

	UFUNCTION(BlueprintImplementableEvent)
	void SetDynamicPercentParameter(float Percent);

	UFUNCTION(BlueprintImplementableEvent)
	void SetTexture(UTexture2D* Icon);
	
	UFUNCTION(BlueprintCallable)
	void SetDynamicTexture(UMaterialInstanceDynamic* DynamicMaterial, UTexture2D* InventoryIcon);
	
	UFUNCTION(BlueprintCallable)
	void SetWidgetText(UTextBlock* TextWidget, FString _String);

	
	
};
