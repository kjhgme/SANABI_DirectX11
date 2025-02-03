#include "PreCompile.h"
#include "BossPlatform.h"

#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/TimeEventComponent.h>
#include <EngineCore/Collision.h>

ABossPlatform::ABossPlatform()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	PlatformBoxRenderer = CreateDefaultSubObject< USpriteRenderer>();
	PlatformBoosterRenderer = CreateDefaultSubObject<USpriteRenderer>();
	
	PlatformBoxRenderer->CreateAnimation("BossPlatform_A_Idle", "BossPlatform_A_Idle", true, 0.15f);
	PlatformBoosterRenderer->CreateAnimation("BossPlatform_A_BoosterLoop", "BossPlatform_A_BoosterLoop", true, 0.1f);
		
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

	WallCollision->SetCollisionEnter([](UCollision* _This, UCollision* _Other)
	{
		// UEngineDebug::OutPutString("Enter");
	});

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

void ABossPlatform::BeginPlay()
{
	AActor::BeginPlay();
}

void ABossPlatform::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}
