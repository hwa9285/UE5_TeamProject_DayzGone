// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/MeleeWeapon.h"

#include "BaseDebugHelper.h"
#include "BaseFunctionLibrary.h"
#include "Components/BoxComponent.h"

AMeleeWeapon::AMeleeWeapon()
{
	WeaponStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponStatic"));
	RootComponent = WeaponStaticMesh;
	WeaponStaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	WeaponCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("MeleeWeaponCollision"));
	WeaponCollisionBox -> SetupAttachment(RootComponent);
	WeaponCollisionBox->SetBoxExtent(FVector(20.f));
	WeaponCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	WeaponCollisionBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnCollisionBoxBeginOverlap);
	WeaponCollisionBox->OnComponentEndOverlap.AddUniqueDynamic(this, &ThisClass::OnCollisionBoxEndOverlap);
}
void AMeleeWeapon::OnCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
											 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APawn* WeaponOwningPawn = GetInstigator<APawn>();

	checkf(WeaponOwningPawn, TEXT("Forget to Assign an instigator as the owning pawn of the weapon: %s"), *GetName());

	if (APawn* HitPawn = Cast<APawn>(OtherActor))
	{
		if (UBaseFunctionLibrary::IsTargetPawnHostile(WeaponOwningPawn, HitPawn))
		{
			OnWeaponHitTarget.ExecuteIfBound(OtherActor);
		}
	}
}

void AMeleeWeapon::OnCollisionBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	APawn* WeaponOwningPawn = GetInstigator<APawn>();

	checkf(WeaponOwningPawn, TEXT("Forget to Assign an instigator as the owning pawn of the weapon: %s"), *GetName());

	if (APawn* HitPawn = Cast<APawn>(OtherActor))
	{
		if (UBaseFunctionLibrary::IsTargetPawnHostile(WeaponOwningPawn, HitPawn))
		{
			OnWeaponPulledFromTarget.ExecuteIfBound(OtherActor);
		}
	}
}

void AMeleeWeapon::InitializeItemFromDataTable(UDataTable* DataTable, int32 ItemId, TSubclassOf<AItemBase> ItemClass)
{
	Super::InitializeItemFromDataTable(DataTable, ItemId, ItemClass);
	FHumanWeaponData* WeaponData_Melee = DataTable->FindRow<FHumanWeaponData>(FName(*FString::FromInt(ItemId)),TEXT("MeleeWeapon Initialization"),true);
	WeaponData = *WeaponData_Melee;
	if (WeaponData_Melee)
	{
		WeaponAnimLayerToLink = WeaponData_Melee->WeaponAnimLayerToLink;
		
		WeaponInputMappingContext = WeaponData_Melee->WeaponInputMappingContext;
		
		WeaponAbilities = WeaponData_Melee->WeaponAbilities;
		
		Damage = WeaponData_Melee->Damage;
		
		StoppingPower = WeaponData_Melee->StoppingPower;
		
		Durability = WeaponData_Melee->Durability;

		WeaponType = WeaponData_Melee->WeaponType;
	}

	Initialize(*WeaponData_Melee);
}
