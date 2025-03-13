// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/ItemBase.h"

// Sets default values
AItemBase::AItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void AItemBase::BeginPlay()
{
	Super::BeginPlay();
}

int32 AItemBase::GetItemID()
{
	return ItemData.ItemID;
}

FGameplayTag AItemBase::GetItemTag()
{
	return ItemData.ItemTag;
}

void AItemBase::InitializeItemFromDataTable(UDataTable* DataTable, int32 ItemId, TSubclassOf<AItemBase> ItemClass)
{
	if (!DataTable || !ItemClass)
	{
		UE_LOG(LogTemp, Error, TEXT("DataTable or ItemClass is null"));
		//return nullptr;
	}
	FItemDataBase *Data = DataTable->FindRow<FItemDataBase>(FName(*FString::FromInt(ItemId)),TEXT("Item Initialization"),true);
	if (!Data)
	{
		UE_LOG(LogTemp, Error, TEXT("DataTable or ItemClass is null"));
		//return nullptr;
	}

	AItemBase* NewItem = NewObject<AItemBase>(GetTransientPackage(),ItemClass);
	if (!NewItem)
	{
		UE_LOG(LogTemp, Error, TEXT("NewObject Failed"));
		//return nullptr;
	}

	NewItem->Initialize(*Data);
}





