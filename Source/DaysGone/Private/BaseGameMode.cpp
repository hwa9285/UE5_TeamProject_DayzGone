// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGameMode.h"

#include "BaseGameInstance.h"
#include "Characters/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

void ABaseGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetGameInstance());
	if (GameInstance)
	{
		GameInstance->Initialize_Data();
	}
	
	GetWorld()->GetTimerManager().SetTimer(AutoSaveTimerHandle,this,&ABaseGameMode::AutoSave,60.f,true);
	
}

void ABaseGameMode::AutoSave()
{
	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetGameInstance());
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics:: GetPlayerCharacter(this,0));
	if (GameInstance && PlayerCharacter)
	{
		GameInstance->SaveGame(PlayerCharacter->GetInventoryUIComponent(),PlayerCharacter->GetActorLocation(),PlayerCharacter);
		UE_LOG(LogTemp,Warning,TEXT("SaveGame!"));
		UE_LOG(LogTemp,Warning,TEXT("PlayerLocation: %f , %f, %f"),GameInstance->SaveData.PlayerLocation.X,GameInstance->SaveData.PlayerLocation.Y,GameInstance->SaveData.PlayerLocation.Z );
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("null"));
	}
}


