#include "PreCompile.h"
#include "Boss.h"
#include "ContentsEnum.h"

#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/TimeEventComponent.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/CameraActor.h>
#include <EngineCore/Collision.h>

#include <EnginePlatform/EngineInput.h>
#include "BossAttack.h"
#include "BodySlap.h"

ABoss::ABoss()
{
	Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	BossWingRenderer = CreateDefaultSubObject<USpriteRenderer>();
	BossRenderer = CreateDefaultSubObject<USpriteRenderer>();

	InitBossAnimation();

	BossRenderer->ChangeAnimation("Boss_Slap");
	BossWingRenderer->ChangeAnimation("Boss_Wing_NoImage");

	BossRenderer->AddRelativeLocation({ 1800.0f, 100.0f, static_cast<float>(ERenderOrder::BOSS) });
	BossWingRenderer->AddRelativeLocation({ 1800.0f, 100.0f, static_cast<float>(ERenderOrder::BOSS) + 1 });

	BossRenderer->SetupAttachment(RootComponent);
	BossWingRenderer->SetupAttachment(RootComponent);
	
	BossRenderer->SetAutoScaleRatio(0.2f);
	BossWingRenderer->SetAutoScaleRatio(0.2f);

	bIsRight = false;
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

	if (true == bIsRight)
	{
		BossRenderer->SetRotation({ 0.0f, 0.0f, 0.0f });
		BossWingRenderer->SetRotation({ 0.0f, 0.0f, 0.0f });
	}
	else if (false == bIsRight)
	{
		BossRenderer->SetRotation({ 0.0f, 180.0f, 0.0f });
		BossWingRenderer->SetRotation({ 0.0f, 180.0f, 0.0f });
	}

	if (State == 0)
	{
	}
	else if (State == 1)
	{
		BossRenderer->AddRelativeLocation({ -1500.0f * _DeltaTime, 0.0f, 0.0f });
		BossWingRenderer->AddRelativeLocation({ -1500.0f * _DeltaTime, 0.0f, 0.0f });
	}
	else if (State == 2)
	{
		int a = 0;
	}

	if (UEngineInput::IsDown('1'))
	{
		SlapAttack();
	}
}

void ABoss::InitBossAnimation()
{
	// Body
	{
		BossRenderer->CreateAnimation("Boss_Slap", "Boss_Slap", false);
		BossRenderer->CreateAnimation("Boss_Body_Idle", "Boss_Body_Idle");
		BossRenderer->CreateAnimation("Boss_Body_Broken_Idle", "Boss_Body_Broken_Idle");
	}
	//Wing
	{
		BossWingRenderer->CreateAnimation("Boss_Wing_NoImage", "Boss_Wing_NoImage", false);
		BossWingRenderer->CreateAnimation("Boss_Wing_Neu_Idle", "Boss_Wing_Neu_Idle");
		BossWingRenderer->CreateAnimation("Boss_Wing_Up1", "Boss_Wing_Up1");
		BossWingRenderer->CreateAnimation("Boss_Wing_Up2", "Boss_Wing_Up2");
		BossWingRenderer->CreateAnimation("Boss_Wing_Up3", "Boss_Wing_Up3");
		BossWingRenderer->CreateAnimation("Boss_Wing_Up4", "Boss_Wing_Up4");
		BossWingRenderer->CreateAnimation("Boss_Wing_Down1", "Boss_Wing_Down1");
		BossWingRenderer->CreateAnimation("Boss_Wing_Down2", "Boss_Wing_Down2");
		BossWingRenderer->CreateAnimation("Boss_Wing_Down3", "Boss_Wing_Down3");
		BossWingRenderer->CreateAnimation("Boss_Wing_Down4", "Boss_Wing_Down4");
		BossWingRenderer->CreateAnimation("Boss_Wing_Broken_Up1", "Boss_Wing_Broken_Up1");
		BossWingRenderer->CreateAnimation("Boss_Wing_Broken_Up2", "Boss_Wing_Broken_Up2");
		BossWingRenderer->CreateAnimation("Boss_Wing_Broken_Up3", "Boss_Wing_Broken_Up3");
		BossWingRenderer->CreateAnimation("Boss_Wing_Broken_Up4", "Boss_Wing_Broken_Up4");
		BossWingRenderer->CreateAnimation("Boss_Wing_Broken_Down1", "Boss_Wing_Broken_Down1");
		BossWingRenderer->CreateAnimation("Boss_Wing_Broken_Down2", "Boss_Wing_Broken_Down2");
		BossWingRenderer->CreateAnimation("Boss_Wing_Broken_Down3", "Boss_Wing_Broken_Down3");
		BossWingRenderer->CreateAnimation("Boss_Wing_Broken_Down4", "Boss_Wing_Broken_Down4");
	}	
}

void ABoss::StareAtPlayer()
{
	BossRenderer->ChangeAnimation("Boss_Body_Idle");
	BossWingRenderer->ChangeAnimation("Boss_Wing_Neu_Idle");

	BossRenderer->SetAutoScaleRatio(1.2f);
	BossWingRenderer->SetAutoScaleRatio(1.2f);

	// BossRenderer->SetRelativeLocation({ 20.0f, -130.0f, 100.0f });
	// BossWingRenderer->SetRelativeLocation({ 20.0f, -130.0f, 101.0f });
	
	BossRenderer->SetRelativeLocation({ 20.0f, -600.0f, static_cast<float>(ERenderOrder::BOSS) });
	BossWingRenderer->SetRelativeLocation({ 20.0f, -600.0f, static_cast<float>(ERenderOrder::BOSS) + 1 });

	FVector TargetPosition1 = { 0.0f, 520.0f, 0.0f };
	FVector TargetPosition2 = { 0.0f, -50.0f, 0.0f };
	FVector TargetPosition3 = { 0.0f, 1500.0f, 0.0f };

	TimeEventComponent->AddUpdateEvent(4.0f, [this, TargetPosition1](float DeltaTime, float CurTime)
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

	TimeEventComponent->AddEndEvent(4.0f, [this, TargetPosition2]()
	{
		TimeEventComponent->AddUpdateEvent(1.0f, [this, TargetPosition2](float DeltaTime, float CurTime)
		{
			auto Lerp = [](FVector A, FVector B, float Alpha)
			{
				return A * (1 - Alpha) + B * Alpha;
			};

			float Alpha = UEngineMath::Clamp(DeltaTime / 1.0f, 0.0f, 1.0f);
			FVector NewPosition = Lerp(FVector::ZERO, TargetPosition2, Alpha);

			AddActorLocation(NewPosition);
		},
			false
		);
	},
		false
	);

	TimeEventComponent->AddEndEvent(6.0f, [this, TargetPosition3]()
	{
		TimeEventComponent->AddUpdateEvent(5.0f, [this, TargetPosition3](float DeltaTime, float CurTime)
		{
			auto Lerp = [](FVector A, FVector B, float Alpha)
			{
				return A * (1 - Alpha) + B * Alpha;
			};

			float Alpha = UEngineMath::Clamp(DeltaTime / 5.0f, 0.0f, 1.0f);
			FVector NewPosition = Lerp(FVector::ZERO, TargetPosition3, Alpha);

			AddActorLocation(NewPosition);
		},
			false
		);
	},
		false
	);
}

void ABoss::StartBattle()
{
	BossWingRenderer->ChangeAnimation("Boss_Wing_Up1");

	BossRenderer->SetAutoScaleRatio(1.2f);
	BossWingRenderer->SetAutoScaleRatio(1.2f);

	BossRenderer->SetRelativeLocation({ 20.0f, -800.0f, 100.0f });
	BossWingRenderer->SetRelativeLocation({ 20.0f, -800.0f, 101.0f });

	FVector TargetPosition1 = { 0.0f, 720.0f, 0.0f };
	FVector TargetPosition2 = { 0.0f, -1000.0f, 0.0f };

	TimeEventComponent->AddUpdateEvent(2.0f, [this, TargetPosition1](float DeltaTime, float CurTime)
	{
		auto Lerp = [](FVector A, FVector B, float Alpha)
		{
			return A * (1 - Alpha) + B * Alpha;
		};

		float Alpha = UEngineMath::Clamp(DeltaTime / 2.0f, 0.0f, 1.0f);
		FVector NewPosition = Lerp(FVector::ZERO, TargetPosition1, Alpha);

		AddActorLocation(NewPosition);
	},
		false
	);

	TimeEventComponent->AddEndEvent(2.0f, [this, TargetPosition2]()
	{
		TimeEventComponent->AddUpdateEvent(1.0f, [this, TargetPosition2](float DeltaTime, float CurTime)
		{
			auto Lerp = [](FVector A, FVector B, float Alpha)
			{
				return A * (1 - Alpha) + B * Alpha;
			};

			float Alpha = UEngineMath::Clamp(DeltaTime / 1.0f, 0.0f, 1.0f);
			FVector NewPosition = Lerp(FVector::ZERO, TargetPosition2, Alpha);

			AddActorLocation(NewPosition);
		},
			false
		);
	},
		false
	);
}

void ABoss::SlapAttack()
{
	FVector PlayerPos = GetWorld()->GetMainPawn()->GetActorLocation();
	
	UEngineDebug::OutPutString(PlayerPos.ToString());

	if (true == bIsRight)
	{
		for (int i = 0; i < 50; ++i)
		{
			TimeEventComponent->AddEndEvent(0.05f * i, [this, i, PlayerPos]() {
				std::shared_ptr<ABossAttack> BodySlapAlert = GetWorld()->SpawnActor<ABodySlap>();
				BodySlapAlert->SetActorLocation(PlayerPos);
				BodySlapAlert->AddActorLocation({ i * 35.0f - (35.0f * 15), -176.0f, 5.0f });
			}
			, false);
		}
	}
	else if (false == bIsRight)
	{
		for (int i = 0; i < 50; ++i)
		{
			TimeEventComponent->AddEndEvent(0.05f * i, [this, i, PlayerPos]() {
				std::shared_ptr<ABossAttack> BodySlapAlert = GetWorld()->SpawnActor<ABodySlap>();
				BodySlapAlert->SetActorLocation(PlayerPos);
				BodySlapAlert->AddActorLocation({ -i * 35.0f + (35.0f * 15), -176.0f, 5.0f });
			}
			, false);
		}
	}
}