// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SectionVolumBase.generated.h"

class UBoxComponent;

UCLASS()
class DAYSGONE_API ASectionVolumBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASectionVolumBase();

protected:
	UPROPERTY(EditAnywhere)
	UBoxComponent* SectionCollision;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="SectionID")
	int32 SectionID;
};
