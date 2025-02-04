#include "PreCompile.h"
#include "BossFloatingBomb.h"

#include <EngineBase/EngineRandom.h>
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/Collision.h>

ABossFloatingBomb::ABossFloatingBomb()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	FloatingBombRenderer = CreateDefaultSubObject<USpriteRenderer>();
	
	InitAnimation();

	FloatingBombRenderer->ChangeAnimation("FloatingBomb_Idle");
	FloatingBombRenderer->SetupAttachment(RootComponent);

	FloatingBombRenderer->SetAutoScaleRatio(0.9f);
	FloatingBombRenderer->AddWorldLocation({ 0.0f, -50.0f, -5.0f });

	FloatingBombCollision = CreateDefaultSubObject<UCollision>();
	FloatingBombCollision->SetupAttachment(RootComponent);
	FloatingBombCollision->SetCollisionProfileName("FloatingBomb");
	FloatingBombCollision->SetScale3D({ 38.0f, 38.0f });
	FloatingBombCollision->AddWorldLocation({ 0.0f, -14.f, 0.0f });
}

ABossFloatingBomb::~ABossFloatingBomb()
{
}

void ABossFloatingBomb::InitAnimation()
{
	FloatingBombRenderer->CreateAnimation("FloatingBomb_Deadparts", "FloatingBomb_Deadparts", false);
	FloatingBombRenderer->CreateAnimation("FloatingBomb_Excholded_Back", "FloatingBomb_Excholded_Back");
	FloatingBombRenderer->CreateAnimation("FloatingBomb_Excholded_Front", "FloatingBomb_Excholded_Front");
	FloatingBombRenderer->CreateAnimation("FloatingBomb_Excholded_Neu", "FloatingBomb_Excholded_Neu");
	FloatingBombRenderer->CreateAnimation("FloatingBomb_ExcholdedStart", "FloatingBomb_ExcholdedStart", false);
	FloatingBombRenderer->CreateAnimation("FloatingBomb_Idle", "FloatingBomb_Idle");
	FloatingBombRenderer->CreateAnimation("FloatingBomb_Knockback", "FloatingBomb_Knockback", false);
	FloatingBombRenderer->CreateAnimation("FloatingBomb_Stunned", "FloatingBomb_Stunned");
}

void ABossFloatingBomb::BeginPlay()
{
	AActor::BeginPlay();

	FloatingBombCollision->SetCollisionEnter([this](UCollision* _This, UCollision* _Other)
	{
		if ("PLATFORMWALL" == _Other->GetCollisionProfileName())
		{
				FVector Normal = (_Other->GetActor()->GetActorLocation() - GetActorLocation()).NormalizeReturn(); // 충돌 방향 계산
				FVector CurrentVelocity = GetVelocity();
				FVector ReflectedVelocity = CurrentVelocity - Normal * FVector::Dot(CurrentVelocity, Normal) * 2; // 반사 벡터 계산

				SetVelocity(ReflectedVelocity); // 반사된 속도로 업데이트			
		}
	});

	UEngineRandom ran;

	float Speed = 500.0f;

	FVector RandomDir = FVector(ran.Randomfloat(-1.0f, 1.0f), ran.Randomfloat(-1.0f, 1.0f), 0.0f).NormalizeReturn();
	SetVelocity(RandomDir * Speed);
}

void ABossFloatingBomb::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	if (GetActorLocation().X < -1100.0f || GetActorLocation().X > 1100.0f)
	{
		Velocity.X *= -1;
	}
	if (GetActorLocation().Y < -500.0f || GetActorLocation().Y > 500.0f)
	{
		Velocity.Y *= -1;
	}

	Velocity.Z = 0.0f;

	// 위치 업데이트
	AddActorLocation(Velocity * _DeltaTime);

	UEngineDebug::OutPutString(Velocity.ToString());
}
