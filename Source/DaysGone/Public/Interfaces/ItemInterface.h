// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ItemInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UItemInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DAYSGONE_API IItemInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool IsPickupable() const;

	//오버랩 시작시
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnItemOverlap(bool Item_CanPickUp);
	
	//오버랩 끝날 때
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnItemOverlapEnd();

	//위젯의 위치를 지속적으로 돌리기 위한 인터페이스 메시지 호출
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void UpdateItemWidgetRotation(FVector Target);
	
	//상호작용 발생시(아이템 먹기->Item은 Destroy되어야함.)
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnInteract(AActor* Interactor);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Set_Item_WidgetClass(bool Item_CanPickUP);

	//UI를 Cannot으로 바꿔줘야할때
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Set_ItemWidget_CanNotPickup();
	
	//초기화떄랑 Timer에서 반복 수행 예정
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void UpdateHoldProgress(float Progress);
	
};
