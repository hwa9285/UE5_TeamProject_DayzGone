// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/PlayerCharacter.h"
#include "Controllers/DeaconController.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/Input/BaseInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "DataAssets/Input/DataAsset_InputConfig.h"
#include "BaseGamePlayTags.h"
#include "AbilitySystem/BaseAbilitySystemComponent.h"
#include "DataAssets/StartupData/DataAsset_StartupBase.h"
#include "Components/Combat/HumanCombatComponent.h"
#include "Components/Widget/PlayerUIComponent.h"
#include "Components/Inventory/InventoryComponent.h"

#include "BaseDebugHelper.h"
#include "ViewportInteractionTypes.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "Interfaces/ItemInterface.h"
#include "Items/DroppedItem.h"
#include "Items/DroppedWeaponBase.h"
#include "Items/HumanWeaponBase.h"
#include "Kismet/KismetArrayLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

APlayerCharacter::APlayerCharacter()
{
	//캡슐컴포넌트 초기사이즈 세팅
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);
	
	//회전 사용 비활성화
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	//케릭터움직임 초기세팅
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = 400.0f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.0f;

	//매시 세팅
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Game/Assets/Character/Deacon/Deacon_Skeletal.Deacon_Skeletal"));

	if (MeshAsset.Succeeded()) {
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);
	}

	//스프링암 초기세팅
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	const FName CameraBornNameSpace = FName(TEXT("Align"));
	//CameraBoom->SetupAttachment(GetMesh(), CameraBornNameSpace);
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 180.0f;
	CameraBoom->SocketOffset = FVector(0.f, 55.f, 45.f);
	CameraBoom->bUsePawnControlRotation = true;

	//카메라 초기세팅
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
	
	// 매시 초기위치 세팅 Z방향으로 -100 내리고 Yaw축으로 -90도 회전
	GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -100.0f), FRotator(0, -90.0f, 0));

	// CombatComponent 세팅
	HumanCombatComponent = CreateDefaultSubobject<UHumanCombatComponent>(TEXT("HumanCombatComponent"));

	// UIComponent 세팅
	PlayerUIComponent = CreateDefaultSubobject<UPlayerUIComponent>(TEXT("PlayerUIComponent"));
	
	// InventoryComponent 세팅
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));

	//ItemInteractComponent 세팅(혜민이가 추가한거)
	ItemUICollision = CreateDefaultSubobject<USphereComponent>(TEXT("ItemCollision"));
	ItemUICollision->SetupAttachment(GetRootComponent());
	ItemUICollision->SetSphereRadius(200.f);
	ItemUICollision->OnComponentBeginOverlap.AddDynamic(this,&APlayerCharacter::OnOverlapItemBegin);
	ItemUICollision->OnComponentEndOverlap.AddDynamic(this,&APlayerCharacter::OnOverlapItemEnd);

	InteractionCheckFrequency = 0.1f;
	InteractionCheckDistance = 10.f;
	bIsCanInteract = false;

	// 마우스 감도 설정
	MouseSensitivity = 0.6f;

	//Npc상호작용 콜리전
	NpcUICollision = CreateDefaultSubobject<USphereComponent>(TEXT("NpcUICollision"));
	NpcUICollision->SetupAttachment(GetRootComponent());
	NpcUICollision->SetSphereRadius(150.f);
	//ItemUICollision->OnComponentBeginOverlap.AddDynamic(this,&APlayerCharacter::);
	//ItemUICollision->OnComponentEndOverlap.AddDynamic(this,&APlayerCharacter::);
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	// TODO::Inventory Initializing Param Set
	// InventoryComponent->InitializeInventory()
}

void APlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	checkf(InputConfigDataAsset, TEXT("Forgot to assign a valid data asset as input config"));

	ULocalPlayer* LocalPlayer = GetController<APlayerController>()->GetLocalPlayer();
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);
	check(Subsystem);
	Subsystem->AddMappingContext(InputConfigDataAsset->DefaultMappingContext, 0);

	UBaseInputComponent* BaseInputComponent = CastChecked<UBaseInputComponent>(PlayerInputComponent);
	BaseInputComponent->BindNativeInputAction(InputConfigDataAsset, BaseGamePlayTags::InputTag_Move, ETriggerEvent::Triggered, this, &APlayerCharacter::Input_Move);
	BaseInputComponent->BindNativeInputAction(InputConfigDataAsset, BaseGamePlayTags::InputTag_Look, ETriggerEvent::Triggered, this, &APlayerCharacter::Input_Look);
	BaseInputComponent->BindNativeInputAction(InputConfigDataAsset, BaseGamePlayTags::InputTag_Inventory, ETriggerEvent::Started, this, &APlayerCharacter::Input_Inventory);
	
	BaseInputComponent->BindAbilityInputAction(InputConfigDataAsset, this, &APlayerCharacter::Input_AbilityInputPressed, &APlayerCharacter::Input_AbilityInputReleased);

}

void APlayerCharacter::Input_Move(const FInputActionValue& InputActionValue)
{
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();
	const FRotator MovementRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
	if (MovementVector.Y != 0.f)
	{
		const FVector ForwardDirection = MovementRotation.RotateVector(FVector::ForwardVector);
		// const FVector ForwardDirection = UKismetMathLibrary::GetForwardVector(UKismetMathLibrary::MakeRotator(0.f, GetControlRotation().Yaw, 0.f));
		AddMovementInput(ForwardDirection, MovementVector.Y);
	}
	if (MovementVector.X != 0.f)
	{
		const FVector RightDirection = MovementRotation.RotateVector(FVector::RightVector);
		// const FVector RightDirection = UKismetMathLibrary::GetRightVector(UKismetMathLibrary::MakeRotator(0.f, GetControlRotation().Yaw, 0.f));
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void APlayerCharacter::Input_Look(const FInputActionValue& InputActionValue)
{
	const FVector2D LookAxisVector = InputActionValue.Get<FVector2D>() * MouseSensitivity;

	if (LookAxisVector.X != 0.f)
	{
		AddControllerYawInput(LookAxisVector.X);
	}
	if (LookAxisVector.Y != 0.f)
	{
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void APlayerCharacter::Input_Inventory(const FInputActionValue& InputActionValue)
{
	if (ADeaconController* PlayerController = Cast<ADeaconController>(Controller))
	{
		PlayerController->InventoryToggle();
	}
}

void APlayerCharacter::Input_AbilityInputPressed(FGameplayTag InputTag)
{
	BaseAbilitySystemComponent->OnAbilityInputPressed(InputTag);
}

void APlayerCharacter::Input_AbilityInputReleased(FGameplayTag InputTag)
{
	BaseAbilitySystemComponent->OnAbilityInputReleased(InputTag);
}

void APlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (!StartupData.IsNull())
	{
		if (UDataAsset_StartupBase* LoadedData = StartupData.LoadSynchronous())
		{
			//Startup데이터가 Null이 아닌경우 StartupData는 동기화로드를 거쳐서 최종적으로 게임어빌리티시스템이 발동된다. GA_HeroSpawnAxe
			LoadedData->GiveToAbilitySystemComponent(GetBaseAbilitySystemComponent());
		}
	}
}

UPawnCombatComponent* APlayerCharacter::GetPawnCombatComponent() const
{
	return HumanCombatComponent;
}

UActorUIComponent* APlayerCharacter::GetActorUIComponent() const
{
	return PlayerUIComponent;
}

UPlayerUIComponent* APlayerCharacter::GetPlayerUIComponent() const
{
	return PlayerUIComponent;
}

void APlayerCharacter::SpawnWeapons(TArray<AHumanWeaponBase*> Weapons)
{
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	TArray<FName> SocketNames = {TEXT("RangedSocket"), TEXT("PistolSocket"), TEXT("SpecialSocket"), TEXT("MeleeSocket")};
	int32 SocketIndex = 0;
	
	for (AHumanWeaponBase* Weapon: Weapons)
	{
		AHumanWeaponBase* SpawnedWeapon = GetWorld()->SpawnActorDeferred<AHumanWeaponBase>(Weapon->GetClass(), FTransform::Identity, GetOwner(), Cast<APawn>(GetOwner()), ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
		SpawnedWeapon->AttachToComponent(GetMesh(), AttachmentRules, SocketNames[SocketIndex++]);
		HumanCombatComponent->RegisterSpawnedWeapon(Weapon->WeaponData.ItemTag, SpawnedWeapon);
	}
}

UInventoryComponent* APlayerCharacter::GetInventoryUIComponent() const
{
	return InventoryComponent;
}

//여기도 추가한거
void APlayerCharacter::StartTrace()
{
	GetWorld()->GetTimerManager().SetTimer(TimerHandle_Interaction,this,&APlayerCharacter::PerformInteractionCheck,0.1f,true);
}

void APlayerCharacter::EndTrace()
{
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle_Interaction);
}

//무기상호작용은 하나씩만 해야하니까 무기일경우에 활성화할 trace 별도로 생성필요?


//아이템을 전체적으로 탐지하는것. e키 상호작용 활성화.
//무기일땐 수행하면 안됨.
void APlayerCharacter::PerformInteractionCheck()
{
	FVector TraceStart{GetPawnViewLocation()};
	FVector TraceEnd{TraceStart+(GetViewRotation().Vector() * InteractionCheckDistance)};
	
	TArray<FHitResult> HitArray;
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);
	
	for (auto& Item:OverlappingActors)
	{
		IItemInterface::Execute_UpdateItemWidgetRotation(Item, (GetCameraComponent()->GetForwardVector())*-1);	
	}
	

	const bool bHit = UKismetSystemLibrary::SphereTraceMulti(GetWorld(),TraceStart,TraceEnd,150.f,
		UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel1),false, ActorsToIgnore ,
		 EDrawDebugTrace::None,HitArray,
		true,FLinearColor::Red,FLinearColor::Blue,1.f);
	
	if (HitArray.Num() > 0)
	{
		for (auto& Hit : HitArray)
		{
			if (Hit.GetActor()->GetClass()->ImplementsInterface(UItemInterface::StaticClass()))
			{
				TargetLocation = Hit.ImpactNormal;
				ADroppedItem* Item = Cast<ADroppedItem>(Hit.GetActor());
				if (Item)
				{
					UInventoryComponent* Inven = GetInventoryUIComponent();
					if (Inven)
					{
						//아이템일땐 최대개수 비교 필요
						//무기일땐 무조건 뜸. 근데 추가로 UI가 뜨느냐 마느냐는 인벤에서 비교를 해줘야함.
						if (Item->ItemType == EItemType::Ammo)
						{
							bIsCanInteract = Inven->GetCurrentAmmoInfo();
							preIsCanInteract = bIsCanInteract;
						}
						else if (Item->ItemType == EItemType::Weapon)
						{
							//무기일경우
							bIsCanInteract = true;
						}
						else
						{
							bIsCanInteract = (Inven->GetItemQuantity(Item->ItemType,Item->ItemID) < Item->MaxQuantity);
							preIsCanInteract = bIsCanInteract;
						}
							
						if (!bIsCanInteract)
						{
							continue;
						}
					}

					//무기일 때
					if (Item->ItemType == EItemType::Weapon )
					{
						//상호작용 R활성화
						
						
						if (!CurrentActiveInteractWeapon)
						{
							CurrentActiveInteractWeapon = Cast<ADroppedWeaponBase>(Item);
							IItemInterface::Execute_Set_Item_WidgetClass(CurrentActiveInteractWeapon,bIsCanInteract);	
						}
						else
						{
							if (CurrentActiveInteractWeapon != Item)
							{
								IItemInterface::Execute_OnItemOverlap(CurrentActiveInteractWeapon,preIsCanInteract);
							
								IItemInterface::Execute_Set_Item_WidgetClass(Item,bIsCanInteract);
								CurrentActiveInteractWeapon = Cast<ADroppedWeaponBase>(Item);
							}
						}
					}
					else
					{
						//무기 제외 다른 아이템일때
						if (!CurrentActiveInteractItem)
						{
							CurrentActiveInteractItem = Item;
							IItemInterface::Execute_Set_Item_WidgetClass(CurrentActiveInteractItem,bIsCanInteract);
						}
						else
						{
							if (CurrentActiveInteractItem != Item)
							{
								//위젯 변경 호출
								IItemInterface::Execute_OnItemOverlap(CurrentActiveInteractItem,preIsCanInteract);
							
								IItemInterface::Execute_Set_Item_WidgetClass(Item,bIsCanInteract);
								CurrentActiveInteractItem = Item;
							}
						}
						break;
					}
				}
				
			}
		}
	}
}

void APlayerCharacter::OnOverlapItemBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->GetClass()->ImplementsInterface(UItemInterface::StaticClass()))
	{
		//플레이어에서 인벤토리 컴포넌트의 아이템 개수, othereactor의 max와 비교
		ADroppedItem* Item = Cast<ADroppedItem>(OtherActor);
		if (Item)
		{
			OverlappingActors.AddUnique(Item);	
			
			
			UInventoryComponent* Inven = GetInventoryUIComponent();
			if (Inven)
			{

				if (Item->ItemType == EItemType::Ammo)
				{
					bIsCanInteract = Inven->GetCurrentAmmoInfo();
					if (bIsCanInteract)
					{
						CanEatItems.AddUnique(Item);
					}
					IItemInterface::Execute_OnItemOverlap(Item,bIsCanInteract);
				}
				else if (Item->ItemType == EItemType::Weapon)
				{
					bIsCanInteract = true;
					IItemInterface::Execute_OnItemOverlap(Item,bIsCanInteract);
				}
				else
				{
					bIsCanInteract = (Inven->GetItemQuantity(Item->ItemType,Item->ItemID) < Item->MaxQuantity);
					if (bIsCanInteract)
					{
						CanEatItems.AddUnique(Item);
					}
					IItemInterface::Execute_OnItemOverlap(Item,bIsCanInteract);
				}
			}
			
			if (!GetWorld()->GetTimerManager().IsTimerActive(TimerHandle_Interaction))
			{
				StartTrace();
			}
			
		}
	}
}

void APlayerCharacter::OnOverlapItemEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor->GetClass()->ImplementsInterface(UItemInterface::StaticClass()))
	{
		ADroppedItem* Item = Cast<ADroppedItem>(OtherActor);
		if (Item)
		{

			if (Item->ItemType == EItemType::Weapon)
			{
				IItemInterface::Execute_OnItemOverlapEnd(Item);
			}
			else
			{
				IItemInterface::Execute_OnItemOverlapEnd(Item);
				OverlappingActors.Remove(Item);
				CanEatItems.Remove(Item);
			}

			if (OverlappingActors.IsEmpty())
			{
				if (GetWorld()->GetTimerManager().IsTimerActive(TimerHandle_Interaction))
				{
					EndTrace();
				}
				CanEatItems.Empty();
			}
		}
		CurrentActiveInteractItem = nullptr;
		CurrentActiveInteractWeapon = nullptr;
	}
}



