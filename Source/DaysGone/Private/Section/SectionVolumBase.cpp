// Fill out your copyright notice in the Description page of Project Settings.


#include "Section/SectionVolumBase.h"

#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
ASectionVolumBase::ASectionVolumBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SectionCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("SectionVolum"));
	RootComponent = SectionCollision;
}


