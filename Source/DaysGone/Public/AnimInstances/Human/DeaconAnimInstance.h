// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/Human/HumanAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DeaconAnimInstance.generated.h"

struct FCachedAnimStateData;
class APlayerCharacter;

UENUM(BlueprintType)
enum class ELocomotionState : uint8 {
	Idle,
	Walking,
	Jogging,
	Sprinting,
	Zoom,
};
/**
 * 
 */
UCLASS()
class DAYSGONE_API UDeaconAnimInstance : public UHumanAnimInstance
{
	GENERATED_BODY()
		
public:
	virtual void NativeInitializeAnimation() override; 
	// virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;
	virtual void NativePostEvaluateAnimation() override;

	UFUNCTION(Blueprintable, meta = (NotBlueprintThreadSafe))
	void DetermineLocomotionState();
	
	UFUNCTION(BlueprintCallable)
	void SetDeaconLocomotionData(float DeltaSeconds);
	
	UFUNCTION(BlueprintCallable)
	void UpdateOnLocomotionEntry();
	
	UFUNCTION(BlueprintCallable, Category = "Rotation")
	void ResetTargetRotation();
	
	UFUNCTION(BlueprintPure, Category = "Rotation")
	FRotator GetTargetRotation();
	
	UFUNCTION(BlueprintPure, Category = "Rotation", meta = (BlueprintThreadSafe))
	FRotator GetLookingRotation() const;
	
	UFUNCTION(Blueprintable)
	FORCEINLINE bool IsMovementWithinThresholds(const float MinCurrentSpeed, const float MinMaxSpeed, const float MinInputAcceleration) const
	{
		return (((MinCurrentSpeed <= GroundSpeed)
			&& (MinMaxSpeed <= OwningMovementComponent->GetMaxSpeed()))
			&& (MinInputAcceleration <= InputVector.Length()));
	}
	
	// UFUNCTION(Blueprintable)
	// FORCEINLINE bool IsMovementWithinThresholds(const float MinCurrentSpeed, const float MinInputAcceleration) const
	// {
	// 	return ((MinCurrentSpeed <= GroundSpeed) && (MinInputAcceleration <= InputVector.Length()));
	// }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void ResetTransitions()
	{
		bWalkStart = false;
		bJogStart = false;
		bSprintStart = false;
	}

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetZoom(bool isZoom)
	{
		bZoom = isZoom;
	}
	
protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|Refrences")
	APlayerCharacter* OwningDeaconCharacter;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	bool bShouldEnterRelaxState;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	float EnterRelaxStateThreshold = 5.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AnimData|LocomotionData")
	float DeltaTimeX;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AnimData|LocomotionData")
	float MoveStartAngle;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AnimData|LocomotionData")
	float PlayRates;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimData|LocomotionData")
	ELocomotionState LocomotionState;

	float IdleElapsedTime;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	FVector InputVector;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	float InputAxis;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	FVector InputVectorFromCamera;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	float InputAxisFromCamera;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "AnimData|LocomotionData")
	bool bWalkStart;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "AnimData|LocomotionData")
	bool bJogStart;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "AnimData|LocomotionData")
	bool bSprintStart;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "AnimData|LocomotionData")
	bool bZoom;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Rotation")
	bool bDoInputVectorRotation;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Rotation")
	FRotator StartRotation;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Rotation")
	FRotator PrimaryTargetRotation;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Rotation")
	FRotator SecondaryTargetRotation;
};
