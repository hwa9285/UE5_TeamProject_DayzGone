// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseType/BaseStructType.h"
#include "GameFramework/Actor.h"
#include "ItemBase.generated.h"

UCLASS()
class DAYSGONE_API AItemBase : public AActor
{
	GENERATED_BODY()
public:	
	// Sets default values for this actor's properties
	AItemBase();

	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	EItemType ItemType; 
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Item")
	FItemDataBase ItemData;

	EItemType GetItemType() { return ItemType; };
	
	void Initialize(const FItemDataBase& _itemData)
	{
		ItemData = _itemData;
	}

	int32 GetItemID();
	
	FGameplayTag GetItemTag();
	
	UFUNCTION(BlueprintCallable,Category="Item")
	virtual void InitializeItemFromDataTable(UDataTable* DataTable, int32 ItemId,TSubclassOf<AItemBase> ItemClass);
};




