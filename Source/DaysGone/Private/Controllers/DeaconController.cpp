// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/DeaconController.h"
#include "Components/Widget/PlayerUIComponent.h"
#include "Interfaces/PawnUIInterface.h"
#include "Kismet/GameplayStatics.h"

#include "BaseDebugHelper.h"

ADeaconController::ADeaconController()
{
	PlayerTeamId = FGenericTeamId(0);
	bShowInventory = false;
}

FGenericTeamId ADeaconController::GetGenericTeamId() const
{
	return PlayerTeamId;
}

void ADeaconController::InventoryToggle()
{
	// UWorld* World = GetWorld();
	// if (!World)
	// 	return;
	//
	// if (!bShowInventory)
	// {
	// 	SetInputMode(FInputModeGameAndUI());
	// 	bShowMouseCursor = true;
	// 	
	// 	bShowInventory = false;
	// 	// TODO::UI visible이나 Add To Viewport 추가?
	// }
	// else
	// {
	// 	SetInputMode(FInputModeGameOnly());
	// 	bShowMouseCursor = false;
	// 	bShowInventory = true;
	// }
	
}

void ADeaconController::SetWeaponHUD(UTexture2D* Texture, float CurrentAmmo, float MaxAmmo)
{
	if (!CachedUIInterface.IsValid())
	{
		CachedUIInterface = TWeakInterfacePtr<IPawnUIInterface>(GetPawn());
	}
	
	UPlayerUIComponent* PlayerUIComponent = CachedUIInterface->GetPlayerUIComponent();
	PlayerUIComponent->OnCurrentWeaponChanged.Broadcast(Texture, CurrentAmmo, MaxAmmo);
}

void ADeaconController::BeginPlay()
{
	Super::BeginPlay();
}
