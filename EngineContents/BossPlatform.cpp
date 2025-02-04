#include "PreCompile.h"
#include "BossPlatform.h"

#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/TimeEventComponent.h>
#include <EngineCore/Collision.h>

#include "BossFloatingBomb.h"

ABossPlatform::ABossPlatform()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	PlatformBoxRenderer = CreateDefaultSubObject< USpriteRenderer>();
	PlatformBoosterRenderer = CreateDefaultSubObject<USpriteRenderer>();
	
	InitAnimation();

	PlatformBoxRenderer->ChangeAnimation("BossPlatform_A_Idle");
	PlatformBoosterRenderer->ChangeAnimation("BossPlatform_A_BoosterLoop");

	PlatformBoxRenderer->SetRelativeLocation({ 0.0f, -100.0f, 1.0f });
	PlatformBoosterRenderer->SetRelativeLocation({ 0.0f, -142.0f, 2.0f });

	PlatformBoxRenderer->SetupAttachment(RootComponent);
	PlatformBoosterRenderer->SetupAttachment(RootComponent);

	PlatformCollision = CreateDefaultSubObject<UCollision>();
	PlatformCollision->SetupAttachment(RootComponent);
	PlatformCollision->SetCollisionProfileName("BossPlatform");
	PlatformCollision->SetWorldLocation({ { 0.0f, 8.0f, 0.0f } });
	PlatformCollision->SetScale3D({ 255.0f, 5.0f });
	
	WallCollision = CreateDefaultSubObject<UCollision>();
	WallCollision->SetupAttachment(RootComponent);
	WallCollision->SetCollisionProfileName("PlatformWall");
	WallCollision->SetWorldLocation({ { 0.0f, -44.0f, 0.0f } });
	WallCollision->SetScale3D({ 255.0f, 110.0f });

	TimeEventComponent = CreateDefaultSubObject<UTimeEventComponent>();
}

ABossPlatform::~ABossPlatform()
{
}

void ABossPlatform::GoToPlace(FVector _Pos)
{
	FVector TargetPosition = _Pos;
	
	TimeEventComponent->AddUpdateEvent(3.0f, [this, TargetPosition](float DeltaTime, float CurTime)
	{
		auto Lerp = [](FVector A, FVector B, float Alpha)
		{
			return A * (1 - Alpha) + B * Alpha;
		};

		float Alpha = UEngineMath::Clamp(DeltaTime / 3.0f, 0.0f, 1.0f);
		FVector NewPosition = Lerp(FVector::ZERO, TargetPosition, Alpha);

		AddActorLocation(NewPosition);
	},	
		false
	);
}

void ABossPlatform::TakeDamage()
{
	// Destroy();

	if (false == bIsInfinity)
	{
		HP -= 1;

		if (HP == 3 || HP == 2)
		{
			PlatformBoxRenderer->ChangeAnimation("BossPlatform_A_Damaged");
		}
		else if (HP == 1)
		{
			PlatformBoxRenderer->ChangeAnimation("BossPlatform_A_DamagedWarning");
		}
		else if (HP == 0)
		{
			PlatformBoxRenderer->ChangeAnimation("BossPlatform_A_Deadparts");

			std::shared_ptr<ABossFloatingBomb> FloatingBomb = GetWorld()->SpawnActor<ABossFloatingBomb>();
			FloatingBomb->SetActorLocation(GetActorLocation());
		}

		bIsInfinity = true;
	}

	TimeEventComponent->AddEndEvent(2.0f, [this]() {
		bIsInfinity = false;
	});
}

void ABossPlatform::InitAnimation()
{
	PlatformBoxRenderer->CreateAnimation("BossPlatform_A_Idle", "BossPlatform_A_Idle", true, 0.15f);
	PlatformBoxRenderer->CreateAnimation("BossPlatform_A_Damaged", "BossPlatform_A_Damaged", false, 0.15f);
	PlatformBoxRenderer->CreateAnimation("BossPlatform_A_DamagedWarning", "BossPlatform_A_DamagedWarning", false, 0.15f);
	PlatformBoxRenderer->CreateAnimation("BossPlatform_A_Deadparts", "BossPlatform_A_Deadparts", false, 0.15f);
	PlatformBoxRenderer->CreateAnimation("BossPlatform_A_Destroy", "BossPlatform_A_Destroy", false, 0.15f);
	PlatformBoxRenderer->CreateAnimation("BossPlatform_A_IdleDoubleWarning", "BossPlatform_A_IdleDoubleWarning", true, 0.15f);
	PlatformBoxRenderer->CreateAnimation("BossPlatform_A_IdleWarning", "BossPlatform_A_IdleWarning", true, 0.15f);

	PlatformBoosterRenderer->CreateAnimation("BossPlatform_A_BoosterLoop", "BossPlatform_A_BoosterLoop", true, 0.1f);
}

void ABossPlatform::BeginPlay()
{
	AActor::BeginPlay();
}

void ABossPlatform::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	if (PlatformBoxRenderer->IsCurAnimationEnd())
	{
		if (PlatformBoxRenderer->GetCurSpriteName() == "BOSSPLATFORM_A_DAMAGED")
		{
			if (HP == 3)
			{
				PlatformBoxRenderer->ChangeAnimation("BossPlatform_A_Idle");
			}
			else if (HP == 2)
			{
				PlatformBoxRenderer->ChangeAnimation("BossPlatform_A_IdleWarning");
			}
		}
		else if (PlatformBoxRenderer->GetCurSpriteName() == "BOSSPLATFORM_A_DAMAGEDWARNING")
		{
			PlatformBoxRenderer->ChangeAnimation("BossPlatform_A_IdleDoubleWarning");			
		}
	}

	if (HP <= 0)
	{
		AddActorLocation({ 0.0f, -100.0f * _DeltaTime, 0.0f });
	}
}
