// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/RangeWeapon.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "BaseDebugHelper.h"
#include "BaseFunctionLibrary.h"
#include "BaseGamePlayTags.h"
#include "AbilitySystem/BaseAbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "Characters/EnemyCharacter.h"
#include "Characters/PlayerCharacter.h"
#include "Components/Inventory/InventoryComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/MapErrors.h"

ARangeWeapon::ARangeWeapon()
{
	WeaponSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMesh");
	RootComponent = WeaponSkeletalMesh;
	WeaponSkeletalMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ARangeWeapon::Fire(APlayerCharacter* Player)
{
	//단발무기시 실행할 함수
	
	if (CurrentAmmo>0)
	{
		PerformTrace(Player);
	}
	else
	{
		if ( Player->GetInventoryUIComponent()->GetCurrentAmmoQuantity(GetAmmoType()) > 0)
		{
			//장전되어있는 총알은 없지만 플레이어가 총알을 가지고있을경우
			//재장전 실행
			//SetAddAmmoAmount로 최대로 장전하거나, 플레이어가 가지고 있는 개수만큼 장전하거나
			SetAddAmmoAmount(Player->GetInventoryUIComponent());
			Reload(AddAmmoAmount);
			for (int i = 0; i < AddAmmoAmount; i++)
			{
				Player->GetInventoryUIComponent()->RemoveAmmo(GetAmmoType());	
			}
		}
		else
		{
			EndTrace();	
		}
		
	}
}

void ARangeWeapon::PerformTrace(APlayerCharacter* Player)
{
	CurrentAmmo--;
	//라인트레이스 발사
	FVector StartLocation = WeaponSkeletalMesh->GetSocketLocation(TEXT("FireSocket"));
	FVector EndLocation = Player->GetCameraComponent()->GetForwardVector() * Range * 1000.f + StartLocation;
	FHitResult Hit;
	FCollisionQueryParams TraceParams;

	// 커스텀 히트스캔 라인트레이스 채널
	bool bHit = GetWorld()->LineTraceSingleByChannel(Hit,StartLocation,EndLocation,
		ECC_Visibility,TraceParams);
	
	//히트시 적한테 데미지
	if (bHit)
	{
		AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(Hit.GetActor());
		if (Enemy)
		{
			OnHitScanTarget.ExecuteIfBound(Enemy);
		}
	}
	if (FireSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), FireSound, GetActorLocation());
	}
}

void ARangeWeapon::EndTrace()
{
	if (GetWorld()->GetTimerManager().IsTimerActive(FireTimer))
	{
		GetWorld()->GetTimerManager().ClearTimer(FireTimer);
	}
}

void ARangeWeapon::Reload(int32 AddAmmo)
{
	CurrentAmmo = AddAmmo;
	if (ReloadSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ReloadSound, GetActorLocation());
	}
}

EAmmoType ARangeWeapon::GetAmmoType()
{
	return AmmoType;
}

void ARangeWeapon::SetAddAmmoAmount(UInventoryComponent* AmmoInven)
{
	if (AmmoInven->AmmoInventory[AmmoType].CurrentQuantity > MaxMagazine)
	{
		AddAmmoAmount = MaxMagazine;
	}
	else
	{
		AddAmmoAmount = AmmoInven->AmmoInventory[AmmoType].CurrentQuantity;
	}
}

void ARangeWeapon::InitializeItemFromDataTable(UDataTable* DataTable, int32 ItemId, TSubclassOf<AItemBase> ItemClass)
{
	Super::InitializeItemFromDataTable(DataTable, ItemId, ItemClass);

	FHumanWeaponData* WeaponData_Range = DataTable->FindRow<FHumanWeaponData>(FName(*FString::FromInt(ItemId)),TEXT("Ingredient Initialization"),true);
	WeaponData = *WeaponData_Range;
	if (WeaponData_Range)
	{
		WeaponAnimLayerToLink = WeaponData_Range->WeaponAnimLayerToLink;

		WeaponInputMappingContext = WeaponData_Range->WeaponInputMappingContext;

		WeaponAbilities = WeaponData_Range->WeaponAbilities;

		WeaponSkeletalMesh -> SetSkeletalMesh(WeaponData_Range->WeaponSkeletalMesh);
		
		Damage = WeaponData_Range->Damage;
		
		Range = WeaponData_Range->Range;
		
		Accuracy =WeaponData_Range->Accuracy;
		
		FireRate = WeaponData_Range->FireRate;

		Penetration = WeaponData_Range->Penetration;
		
		StoppingPower = WeaponData_Range->StoppingPower;
		
		MaxMagazine = WeaponData_Range->MaxMagazine;
		
		AmmoType = WeaponData_Range->AmmoType;

		WeaponType = WeaponData_Range->WeaponType;
	}

	Initialize(*WeaponData_Range);
}



