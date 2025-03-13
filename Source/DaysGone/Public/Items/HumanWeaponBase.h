// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/ItemBase.h"
#include "BaseType/BaseStructType.h"
#include "GameplayAbilitySpecHandle.h"
#include "HumanWeaponBase.generated.h"

class ADroppedWeaponBase;
class UBoxComponent;
DECLARE_DELEGATE_OneParam(FOnTargetInteractedDelegate, AActor*)
/**
 * 
 */
UCLASS()
class DAYSGONE_API AHumanWeaponBase : public AItemBase
{
	GENERATED_BODY()

public:
	FOnTargetInteractedDelegate OnWeaponHitTarget;
	FOnTargetInteractedDelegate OnWeaponPulledFromTarget;
	FOnTargetInteractedDelegate OnHitScanTarget;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	UBoxComponent* WeaponCollisionBox;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Dropped")
	TSubclassOf<ADroppedWeaponBase> DroppedWeaponClass;
	
public:
    AHumanWeaponBase();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "WeaponData")
	FHumanWeaponData WeaponData;

	UFUNCTION(BlueprintCallable)
	TSubclassOf<ADroppedWeaponBase> GetDroppedWeaponClass(){return DroppedWeaponClass;};
	
	UFUNCTION(BlueprintCallable)
	void AssignGrantedAbilitySpecHandles(const TArray<FGameplayAbilitySpecHandle>& SpecHandles);

	UFUNCTION(BlueprintPure)
	TArray<FGameplayAbilitySpecHandle> GetGrantedAbilitySpecHandles() const;

	UFUNCTION()
	virtual void OnCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	virtual void OnCollisionBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable)
	FHumanWeaponData GetWeaponData() const {return WeaponData;}
	
	FORCEINLINE UBoxComponent* GetWeaponCollisionBox() const { return WeaponCollisionBox; }
	
	
private:
	TArray<FGameplayAbilitySpecHandle> GrantedAbilitySpecHandles;

	

	//무기는 다른 위젯
	//virtual void UpdateInteractWidget() override;

	
	//베이스 웨폰엔 기본 성능, 메쉬 설정
	//자식에서 상세설정 + 무기종류 및 분류(range,melee,throw / main, sub, sp, th?)

	
};
