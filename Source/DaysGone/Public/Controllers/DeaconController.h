// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GenericTeamAgentInterface.h"
#include "DeaconController.generated.h"

class IPawnUIInterface;

/**
 * 
 */
UCLASS()
class DAYSGONE_API ADeaconController : public APlayerController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()
	
public:
	ADeaconController();
	
	virtual void BeginPlay() override;
	
	virtual FGenericTeamId GetGenericTeamId() const override;

	// 인벤토리
	void InventoryToggle();
	
	bool bShowInventory;

	UFUNCTION(BlueprintCallable)
	void SetWeaponHUD(UTexture2D* Texture, float CurrentAmmo, float MaxAmmo);
private:
	FGenericTeamId PlayerTeamId;
	
	TWeakInterfacePtr<IPawnUIInterface> CachedUIInterface;
};
