// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "GameplayTagContainer.h"
#include "PlayerCharacter.generated.h"

class UWheelBase;
class UWidgetBase;
class ADroppedWeaponBase;
class ADroppedItem;
class USphereComponent;
class USpringArmComponent;
class UCameraComponent;
class UDataAsset_InputConfig;
class UHumanCombatComponent;
class UPlayerUIComponent;
class UInventoryComponent;
class AHumanWeaponBase;

struct FInputActionValue;
/**
 * 
 */
UCLASS()
class DAYSGONE_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();
	
private:
	virtual void BeginPlay() override;

private:
#pragma region Components
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, category = "Combat", meta = (AllowPrivateAccess = "true"))
	UHumanCombatComponent* HumanCombatComponent;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, category = "UI", meta = (AllowPrivateAccess = "true"))
	UPlayerUIComponent* PlayerUIComponent;
	
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, category = "Inventory", meta = (AllowPrivateAccess = "true"))
	UInventoryComponent* InventoryComponent;

	//혜민이가 추가한거
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, category = "Item Interact", meta = (AllowPrivateAccess = "true"))
	USphereComponent* ItemUICollision;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, category = "Npc Interact", meta = (AllowPrivateAccess = "true"))
	USphereComponent* NpcUICollision;
	
#pragma endregion

#pragma region Inputs
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, category = "CharacterData", meta = (AllowPrivateAccess = "true"))
	UDataAsset_InputConfig* InputConfigDataAsset;

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Input_Move(const FInputActionValue& InputActionValue);
	void Input_Look(const FInputActionValue& InputActionValue);
	void Input_Inventory(const FInputActionValue& InputActionValue);

	void Input_AbilityInputPressed(FGameplayTag InputTag);
	void Input_AbilityInputReleased(FGameplayTag InputTag);

	// 카메라 Get
public:
	
#pragma endregion

protected:
	virtual void PossessedBy(AController* NewController) override;
	virtual UPawnCombatComponent* GetPawnCombatComponent() const override;
	virtual UActorUIComponent* GetActorUIComponent() const override;
	virtual UPlayerUIComponent* GetPlayerUIComponent() const override;

	// 무기 등록 함수
	UFUNCTION(BlueprintCallable, Category = "Player")
	void SpawnWeapons(TArray<AHumanWeaponBase*> Weapons);
	
	// 캐릭터 설정 변수
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input")
	float MouseSensitivity;
	
	//혜민이가 추가한 변수들
	//하면서 Interface도 전방선언 해뒀음
	
	//오버랩중인 아이템(주울 수 있는 아이템만 추가.)
	UPROPERTY(VisibleAnyWhere,Category="ItemArray")
	TArray<ADroppedItem*> OverlappingActors;

	UPROPERTY(VisibleAnyWhere,Category="ItemArray")
	TArray<ADroppedItem*> CanEatItems;

	//오버랩중인 무기
	UPROPERTY(VisibleAnyWhere,Category="DroppedWeapon")
	ADroppedWeaponBase* OverlappingWeapon;

	//상호작용이 활성화된 무기
	UPROPERTY(VisibleAnyWhere,Category="DroppedWeapon")
	ADroppedWeaponBase* CurrentActiveInteractWeapon;

	UPROPERTY(VisibleAnyWhere,Category="InteractItem")
	ADroppedItem* CurrentActiveInteractItem;
	
	//오버랩이 끝난 아이템(임시로 관리 예정)
	UPROPERTY(VisibleAnyWhere,Category="TempItemArray")
	AActor* OverlapEndActors;

	UPROPERTY(VisibleAnyWhere,Category="TempItemArray")
	AActor* ClosetItem;

	FVector TargetLocation;
	
	float InteractionCheckFrequency;

	float InteractionCheckDistance;

	FTimerHandle TimerHandle_Interaction;
	
	FTimerHandle AttackTimerHandle;

	//==================================================
	//위젯 변수용
	//==================================================
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "InventoryWidget")
	UWidgetBase* Inventory_Widget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "InventoryWidget")
	UWheelBase* Inventory_Wheel;

	//==================================================
	//아이템 먹을땐 CanEatItem배열 돌려서 먹어야함.
	//==================================================
	UFUNCTION(BlueprintCallable)
	TArray<ADroppedItem*> GetCanEatItem(){return CanEatItems;}

	//==================================================
	//타이머 관련 함수
	//==================================================
	void StartTrace();
	void EndTrace();

	void PerformInteractionCheck(); //트레이스 발사할 interface

	
	//==================================================
	//콜리전 Overlap시 바인딩할 이벤트
	//==================================================
	UFUNCTION()
	void OnOverlapItemBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
						UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
						const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapItemEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
					  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	//==================================================
	//콜리전 Overlap시 바인딩할 이벤트(NPC)
	//==================================================
	
	
public:
	FORCEINLINE UHumanCombatComponent* GetHeroCombatComponent() const { return HumanCombatComponent; }

	UFUNCTION(BlueprintCallable)
	UInventoryComponent* GetInventoryUIComponent() const;
	//혜민이가 추가한 변수

	//interact가 가능한지의 기준 -> Trace가 충돌해서 배열이 존재할때
	bool IsCanInteract(){ return bIsCanInteract;  };
	bool bIsCanInteract;
	bool preIsCanInteract;

	UFUNCTION(BlueprintCallable, Category = "Camera")
	FORCEINLINE UCameraComponent* GetCameraComponent() const { return FollowCamera; }
	//여기까지

	// 상호작용 가능한 아이템 Get 함수
	UFUNCTION(BlueprintCallable, Category = "Item")
	FORCEINLINE ADroppedItem* GetCurrentInteractableItem() const { return CurrentActiveInteractItem; }

	UFUNCTION(BlueprintCallable, Category = "WeaponItem")
	ADroppedWeaponBase* GetCurrentInteractableWeapon() const {return CurrentActiveInteractWeapon;}
	
	UFUNCTION(BlueprintCallable, Category = "Item")
	FORCEINLINE TArray<ADroppedItem*> GetInteractableItems() const { return OverlappingActors; }

	UFUNCTION(BlueprintCallable, Category = "Input")
	FORCEINLINE void SetMouseSensitivity(float Interp) { MouseSensitivity = Interp; }

	UFUNCTION(BlueprintCallable, Category = "Input")
	FORCEINLINE ADroppedWeaponBase* GetCurrentActiveInteractWeapon() {return CurrentActiveInteractWeapon;}
};
