// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/EnemyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/Combat/EnemyCombatComponent.h"
#include "DataAssets/StartupData/DataAsset_StartupBase.h"
#include "Components/Widget/EnemyUIComponent.h"
#include "BaseDebugHelper.h"
#include "Engine/AssetManager.h"


AEnemyCharacter::AEnemyCharacter()
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 180.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = 750.0f;
	GetCharacterMovement()->BrakingDecelerationWalking = 1000.0f;
	
	EnemyCombatComponent = CreateDefaultSubobject<UEnemyCombatComponent>(TEXT("EnemyCombatComponent"));
	
	// UIComponent 세팅
	EnemyUIComponent = CreateDefaultSubobject<UEnemyUIComponent>(TEXT("EnemyUIComponent"));

	GetCharacterMovement()->bOrientRotationToMovement = true;
}

void AEnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	InitEnemyStartUpData();
}

void AEnemyCharacter::InitEnemyStartUpData()
{
	if (StartupData.IsNull())
	{
		return;
	}
	
	//Startup Data를 비동기 로딩으로 불러온다.
	UAssetManager::GetStreamableManager().RequestAsyncLoad(
		StartupData.ToSoftObjectPath(),
		FStreamableDelegate::CreateLambda(
			[this]()
			{
				if (UDataAsset_StartupBase* LoadedData = StartupData.Get())
				{
					LoadedData->GiveToAbilitySystemComponent(BaseAbilitySystemComponent);
				}
			}
		)
	);
}

UActorUIComponent* AEnemyCharacter::GetActorUIComponent() const
{
	return EnemyUIComponent;
}

UEnemyUIComponent* AEnemyCharacter::GetEnemyUIComponent() const
{
	return EnemyUIComponent;
}

UPawnCombatComponent* AEnemyCharacter::GetPawnCombatComponent() const
{
	return EnemyCombatComponent;
}
