// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BaseGameMode.generated.h"

/**
 * 
 */
UCLASS()
class DAYSGONE_API ABaseGameMode : public AGameModeBase
{
	GENERATED_BODY()

	virtual void BeginPlay() override;

protected:
	UFUNCTION(BlueprintCallable)
	void AutoSave();

	FTimerHandle AutoSaveTimerHandle;
	
};
