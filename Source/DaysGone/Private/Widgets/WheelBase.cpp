// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/WheelBase.h"

#include "Kismet/KismetMathLibrary.h"

float UWheelBase::GetMouseRotation()
{
	
	FVector PlayerRotation;
	float MouseX, MouseY;
	GetOwningPlayer()->GetMousePosition(MouseX,MouseY);
	PlayerRotation = FVector(MouseX, MouseY, 0.0f);
	
	FVector2D ViewportSize;
	GEngine->GameViewport->GetViewportSize(ViewportSize);
	FVector ResultVector(ViewportSize.X * 0.75 , ViewportSize.Y * 0.5 , 0);

	FRotator MouseRotation = UKismetMathLibrary::FindLookAtRotation(PlayerRotation,ResultVector);
	
	return 180 - MouseRotation.Yaw;
}


