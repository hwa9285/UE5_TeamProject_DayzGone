// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseType/BaseEnumType.h"
#include "GameFramework/Actor.h"
#include "Interfaces/ItemInterface.h"
#include "DroppedItem.generated.h"

class UWidgetBase;
class UWidgetComponent;
class USphereComponent;
class APlayerCharacter;

UCLASS()
class DAYSGONE_API ADroppedItem : public AActor, public IItemInterface
{
	GENERATED_BODY()

private:
	//maxquantity가 inventory개수보다 작을때 참.
	bool bCanPickup;

public:	
	// Sets default values for this actor's properties
	ADroppedItem();
	
public:
	//위젯
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	UWidgetComponent* InteractWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UWidgetBase> CanPickupWidget;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UWidgetBase> CanNotPickupWidget;

public:
	//아이템에 들어가는 정보들
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dropped Item")
	EItemType ItemType;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Dropped Item")
	int32 ItemID;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Dropped Item")
	UTexture2D* ItemIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dropped Item")
	int32 MaxQuantity;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Dropped Item")
	UStaticMeshComponent* ItemMesh;

	float HoldingTime;

	//WidgetSwitcher 하기 전, 변경할 파라미터
	void SetWidgetParameter();

public:
	//인터페이스 구현부
	virtual bool IsPickupable_Implementation() const override;

	virtual void OnInteract_Implementation(AActor* Interactor) override;

	virtual void OnItemOverlap_Implementation(bool Item_CanPickUp) override;

	virtual void OnItemOverlapEnd_Implementation() override;

	virtual void Set_Item_WidgetClass_Implementation(bool Item_CanPickUP) override;

	virtual void UpdateHoldProgress_Implementation(float Progress) override;

	virtual void Set_ItemWidget_CanNotPickup_Implementation() override;

	virtual void UpdateItemWidgetRotation_Implementation(FVector Target) override;

private:
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WidgetRotation")
	void StartRotation();
	void EndRotation();
	void SetWidgetRotation();
	FTimerHandle RotationTimer;
	
	

};

