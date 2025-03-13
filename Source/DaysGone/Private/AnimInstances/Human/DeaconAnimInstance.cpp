// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/Human/DeaconAnimInstance.h"
#include "Characters/PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

#include "BaseDebugHelper.h"
#include "VectorTypes.h"
#include "Camera/CameraComponent.h"

void UDeaconAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (OwningCharacter)
	{
		OwningDeaconCharacter = Cast<APlayerCharacter>(OwningCharacter);
	}
	
	LocomotionState = ELocomotionState::Idle;
	InputVector = FVector::ZeroVector;
}

// void UDeaconAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
// {
// 	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
// }

void UDeaconAnimInstance::NativePostEvaluateAnimation()
{
	Super::NativePostEvaluateAnimation();

	if (OwningCharacter)
	{
		ResetTransitions();
	}
}

void UDeaconAnimInstance::DetermineLocomotionState()
{
	if (!bIsFalling && !bZoom)
	{
		//if ((UKismetMathLibrary::Dot_VectorVector(UKismetMathLibrary::Normal(OwningMovementComponent->Velocity), UKismetMathLibrary::Normal(OwningMovementComponent->GetCurrentAcceleration())) < -0.5f) && (OwningMovementComponent->GetCurrentAcceleration().Length() <= 0))
		if ((UKismetMathLibrary::Dot_VectorVector(UKismetMathLibrary::Normal(OwningMovementComponent->Velocity), UKismetMathLibrary::Normal(OwningMovementComponent->GetCurrentAcceleration())) < -0.5f))
		{
			LocomotionState = ELocomotionState::Idle;
		}
		else if (IsMovementWithinThresholds(0, 800, 0.1))
		{
			LocomotionState = ELocomotionState::Sprinting;
		}
		else if (IsMovementWithinThresholds(0, 400, 0.5))
		// else if (IsMovementWithinThresholds(1, 0.5))
		{
			LocomotionState = ELocomotionState::Jogging;
		}
		else if (IsMovementWithinThresholds(0, 0, 0.01))
		// else if (IsMovementWithinThresholds(1, 0.01))
		{
			LocomotionState = ELocomotionState::Walking;
		}
		else
		{
			LocomotionState = ELocomotionState::Idle;
		}
	}
	else if (bZoom)
	{
		LocomotionState = ELocomotionState::Zoom;
	}
}

void UDeaconAnimInstance::SetDeaconLocomotionData(float DeltaSeconds)
{
	if (bHasAcceleration)
	{
		IdleElapsedTime = 0.f;
		bShouldEnterRelaxState = false;
	}
	else
	{
		IdleElapsedTime += DeltaSeconds;
		bShouldEnterRelaxState = (IdleElapsedTime >= EnterRelaxStateThreshold);
	}
	if (OwningCharacter)
	{
		InputVector = UKismetMathLibrary::ClampVectorSize(OwningMovementComponent->GetLastInputVector(), 0.f, 1.f);
		InputAxis = UKismetMathLibrary::NormalizeAxis((UKismetMathLibrary::DegAtan2(OwningDeaconCharacter->GetActorForwardVector().Y, OwningDeaconCharacter->GetActorForwardVector().X) - UKismetMathLibrary::DegAtan2(InputVector.Y, InputVector.X)) * -1.f);
		// InputAxis = UKismetMathLibrary::NormalizeAxis((UKismetMathLibrary::DegAtan2(OwningDeaconCharacter->GetCameraComponent()->GetForwardVector().Y, OwningDeaconCharacter->GetCameraComponent()->GetForwardVector().X) - UKismetMathLibrary::DegAtan2(InputVector.Y, InputVector.X)) * -1.f);

		DetermineLocomotionState();
	}
}

void UDeaconAnimInstance::UpdateOnLocomotionEntry()
{
	float MinSpeed = 0.f;
	switch (LocomotionState)
	{
		case ELocomotionState::Walking:
			MinSpeed = 50.f;
			break;
		case ELocomotionState::Jogging:
			MinSpeed = 200.f;
			break;
		case ELocomotionState::Sprinting:
			MinSpeed = 400.f;
			break;
		default:
			break;
	}
	if (GroundSpeed < MinSpeed)
	{
		StartRotation = OwningDeaconCharacter->GetActorRotation();
		PrimaryTargetRotation = UKismetMathLibrary::Conv_VectorToRotator(InputVector);
		// SecondaryTargetRotation = PrimaryTargetRotation;
		SecondaryTargetRotation = StartRotation;
		MoveStartAngle = UKismetMathLibrary::NormalizedDeltaRotator(PrimaryTargetRotation, StartRotation).Yaw;
		switch (LocomotionState)
		{
		case ELocomotionState::Walking:
			bWalkStart = true;
			break;
		case ELocomotionState::Jogging:
			bJogStart = true;
			break;
		case ELocomotionState::Sprinting:
			bSprintStart = true;
			break;
		default:
			break;
		}
	}
	else
	{
		ResetTargetRotation();
	}
}

void UDeaconAnimInstance::ResetTargetRotation()
{
	PrimaryTargetRotation = OwningDeaconCharacter->GetActorRotation();
	SecondaryTargetRotation = PrimaryTargetRotation;
}

FRotator UDeaconAnimInstance::GetTargetRotation()
{
	if (bDoInputVectorRotation)
	{
		return FRotator(0.f, UKismetMathLibrary::Conv_VectorToRotator(InputVector).Yaw, 0.f);
	}
	
	return FRotator(0.f, UKismetMathLibrary::Conv_VectorToRotator(OwningMovementComponent->Velocity).Yaw, 0.f);
}

FRotator UDeaconAnimInstance::GetLookingRotation() const
{
	// -180 ~ 180으로 노멀라이즈 하기
	return UKismetMathLibrary::NormalizedDeltaRotator(OwningDeaconCharacter->GetControlRotation(), OwningDeaconCharacter->GetActorRotation());
}
