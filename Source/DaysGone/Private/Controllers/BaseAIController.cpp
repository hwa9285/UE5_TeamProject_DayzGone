// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/BaseAIController.h"
#include "Navigation/CrowdFollowingComponent.h"
#include "BaseDebugHelper.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionTypes.h"
#include "BehaviorTree/BlackboardComponent.h"

ABaseAIController::ABaseAIController(const FObjectInitializer& ObjectInitializer):
Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>("PathFollowingComponent"))
{
	if (UCrowdFollowingComponent* CrowdFollowingComponent = Cast<UCrowdFollowingComponent>(GetPathFollowingComponent()))
	{
		// Debug::Print(TEXT("CrowdFollowingComponent valid"), FColor::Green);
	}
	//생성자
	AISenseConfig_Sight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("AISenseConfig_Sight"));

	//적 감지
	AISenseConfig_Sight->DetectionByAffiliation.bDetectEnemies = true;
	//아군 감지
	AISenseConfig_Sight->DetectionByAffiliation.bDetectFriendlies = false;
	//중립 감지
	AISenseConfig_Sight->DetectionByAffiliation.bDetectNeutrals = false;
	//시아 반경설정
	AISenseConfig_Sight->SightRadius = 2000.0f;
	//대상을 잃는 시아 범위 설정
	AISenseConfig_Sight->LoseSightRadius = 0.f;
	//주변 시아각
	AISenseConfig_Sight->PeripheralVisionAngleDegrees = 90.0f;

	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("AIPerceptionComponent");
	//센서 설정
	AIPerceptionComponent->ConfigureSense(*AISenseConfig_Sight);
	AIPerceptionComponent->SetDominantSense(UAISenseConfig_Sight::StaticClass());
	AIPerceptionComponent->OnTargetPerceptionUpdated.AddUniqueDynamic(this, &ABaseAIController::OnEnemyPerceptionUpdated);
}

void ABaseAIController::BeginPlay()
{
	Super::BeginPlay();
	
	if (UCrowdFollowingComponent* CrowdFollowingComponent = Cast<UCrowdFollowingComponent>(GetPathFollowingComponent()))
	{
		CrowdFollowingComponent->SetCrowdSimulationState(bDetourCrowdAvoidence ? ECrowdSimulationState::Enabled : ECrowdSimulationState::Disabled);
        
		switch (DetourCrowdAvoidenceQuality)
		{
		case 1: CrowdFollowingComponent->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Low);    break;
		case 2: CrowdFollowingComponent->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Medium); break;
		case 3: CrowdFollowingComponent->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Good);   break;
		case 4: CrowdFollowingComponent->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::High);   break;
		default: break;
		}

		CrowdFollowingComponent->SetAvoidanceGroup(1);
		CrowdFollowingComponent->SetGroupsToAvoid(1);
		CrowdFollowingComponent->SetCrowdCollisionQueryRange(CollisionQueryRange);
	}
}

void ABaseAIController::OnEnemyPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	//update
	// if (Stimulus.WasSuccessfullySensed() && Actor)
	// {
	// 	if (UBlackboardComponent* BlackboardComponent = GetBlackboardComponent())
	// 	{
	// 		BlackboardComponent->SetValueAsObject(FName(TEXT("TargetActor")), Actor);
	// 	}
	// }
	if (UBlackboardComponent* BlackboardComponent = GetBlackboardComponent())
	{
		if (!BlackboardComponent->GetValueAsObject(FName("TargetActor")))
		{
			if (Stimulus.WasSuccessfullySensed() && Actor)
			{
				BlackboardComponent->SetValueAsObject(FName(TEXT("TargetActor")), Actor);
			}
		}
	}
}


ETeamAttitude::Type ABaseAIController::GetTeamAttitudeTowards(const AActor& Other) const
{
	//SetGenericTeamId(FGenericTeamId(1));
	
	const APawn* PawnCheck = Cast<const APawn>(&Other);
	const IGenericTeamAgentInterface* OtherTeamAgent = Cast<IGenericTeamAgentInterface>(PawnCheck->GetController());

	if (OtherTeamAgent && OtherTeamAgent->GetGenericTeamId() != GetGenericTeamId())
	{
		//TeamID가 다르면 적
		return ETeamAttitude::Hostile;
	}

    
	return ETeamAttitude::Friendly;
}
