// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/HumanWeaponBase.h"
#include "MeleeWeapon.generated.h"


DECLARE_DELEGATE_OneParam(FOnTargetInteractedDelegate, AActor*)

class UBoxComponent;
/**
 * 
 */
UCLASS()
class DAYSGONE_API AMeleeWeapon : public AHumanWeaponBase
{
	GENERATED_BODY()

public:
	AMeleeWeapon();

	
public:
	virtual void InitializeItemFromDataTable(UDataTable* DataTable, int32 ItemId, TSubclassOf<AItemBase> ItemClass) override;
	
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	UStaticMeshComponent* WeaponStaticMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<ULinkedAnimLayer> WeaponAnimLayerToLink;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputMappingContext* WeaponInputMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty = "InputTag"))
	TArray<FHumanAbilitySet> WeaponAbilities;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float StoppingPower;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Melee")
	float Durability;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Melee")
	FGameplayTag WeaponType;

public:
	virtual void OnCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                                        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                                        const FHitResult& SweepResult) override;
	
	virtual void OnCollisionBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
								  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;
	
	FORCEINLINE UBoxComponent* GetWeaponCollisionBox() const { return WeaponCollisionBox; }
	
	
private:
	TArray<FGameplayAbilitySpecHandle> GrantedAbilitySpecHandles;

};
