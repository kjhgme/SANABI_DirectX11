#include "PreCompile.h"
#include "Boss.h"
#include "ContentsEnum.h"

#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/TimeEventComponent.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/Collision.h>

ABoss::ABoss()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	BossWingRenderer = CreateDefaultSubObject<USpriteRenderer>();
	BossRenderer = CreateDefaultSubObject<USpriteRenderer>();

	InitBossAnimation();

	BossRenderer->ChangeAnimation("Boss_Slap");
	BossWingRenderer->ChangeAnimation("Boss_Wing_NoImage");

	BossRenderer->AddRelativeLocation({ 1800.0f, 0.0f, static_cast<float>(ERenderOrder::BOSS) });
	BossWingRenderer->AddRelativeLocation({ 1800.0f, 0.0f, static_cast<float>(ERenderOrder::BOSS) + 1 });

	BossRenderer->SetupAttachment(RootComponent);
	BossWingRenderer->SetupAttachment(RootComponent);
	
	BossRenderer->SetAutoScaleRatio(0.5f);
	BossWingRenderer->SetAutoScaleRatio(0.5f);

	BossRenderer->SetRotation({ 0.0f, 180.0f, 0.0f });
	BossWingRenderer->SetRotation({ 0.0f, 180.0f, 0.0f });

	TimeEventComponent = CreateDefaultSubObject<UTimeEventComponent>();
}

ABoss::~ABoss()
{
}

void ABoss::BeginPlay()
{
	AActor::BeginPlay();
}

void ABoss::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	if (State == 0)
	{
		BossRenderer->AddRelativeLocation({ -2000.0f * _DeltaTime, 0.0f, 0.0f });
		BossWingRenderer->AddRelativeLocation({ -2000.0f * _DeltaTime, 0.0f, 0.0f });
	}
	else if (State == 1)
	{

	}
}

void ABoss::InitBossAnimation()
{
	BossRenderer->CreateAnimation("Boss_Slap", "Boss_Slap", false);
	BossRenderer->CreateAnimation("Boss_Body_Idle", "Boss_Body_Idle");

	BossWingRenderer->CreateAnimation("Boss_Wing_NoImage", "Boss_Wing_NoImage", false);
	BossWingRenderer->CreateAnimation("Boss_Wing_Neu_Idle", "Boss_Wing_Neu_Idle");
}



void ABoss::StareAtPlayer()
{
	BossRenderer->ChangeAnimation("Boss_Body_Idle");
	BossWingRenderer->ChangeAnimation("Boss_Wing_Neu_Idle");

	BossRenderer->SetAutoScaleRatio(1.0f);
	BossWingRenderer->SetAutoScaleRatio(1.0f);

	// BossRenderer->SetRelativeLocation({ 20.0f, -130.0f, 100.0f });
	// BossWingRenderer->SetRelativeLocation({ 20.0f, -130.0f, 101.0f });
	
	BossRenderer->SetRelativeLocation({ 20.0f, -600.0f, 100.0f });
	BossWingRenderer->SetRelativeLocation({ 20.0f, -600.0f, 101.0f });

	FVector TargetPosition1 = { 0.0f, 550.0f, 0.0f };
	FVector TargetPosition2 = { 0.0f, 470.0f, 0.0f };

	TimeEventComponent->AddUpdateEvent(4.0f, [this, TargetPosition1, TargetPosition2](float DeltaTime, float CurTime)
	{
		auto Lerp = [](FVector A, FVector B, float Alpha)
		{
			return A * (1 - Alpha) + B * Alpha;
		};

		float Alpha = UEngineMath::Clamp(DeltaTime / 4.0f, 0.0f, 1.0f);
		FVector NewPosition = Lerp(FVector::ZERO, TargetPosition1, Alpha);

		AddActorLocation(NewPosition);
	},
		false
	);
}