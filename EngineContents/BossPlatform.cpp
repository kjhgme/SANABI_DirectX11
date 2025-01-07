#include "PreCompile.h"
#include "BossPlatform.h"

#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/Collision.h>

ABossPlatform::ABossPlatform()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	PlatformBoxRenderer = CreateDefaultSubObject< USpriteRenderer>();
	PlatformBoosterRenderer = CreateDefaultSubObject<USpriteRenderer>();
	
	PlatformBoxRenderer->CreateAnimation("BossPlatform_A_Idle", "BossPlatform_A_Idle");
	PlatformBoosterRenderer->CreateAnimation("BossPlatform_A_BoosterLoop", "BossPlatform_A_BoosterLoop");
		
	PlatformBoxRenderer->ChangeAnimation("BossPlatform_A_Idle");
	PlatformBoosterRenderer->ChangeAnimation("BossPlatform_A_BoosterLoop");

	PlatformBoxRenderer->SetRelativeLocation({ 0.0f, -100.0f, 1.0f });
	PlatformBoosterRenderer->SetRelativeLocation({ 0.0f, -142.0f, 2.0f });

	PlatformBoxRenderer->SetupAttachment(RootComponent);
	PlatformBoosterRenderer->SetupAttachment(RootComponent);

	Collision = CreateDefaultSubObject<UCollision>();
	Collision->SetupAttachment(RootComponent);
	Collision->SetCollisionProfileName("BossPlatform");
	Collision->SetRelativeLocation({ { 0.0f, -48.0f, 0.0f } });
	Collision->SetScale3D({ 255.0f, 116.0f });

	Collision->SetCollisionEnter([](UCollision* _This, UCollision* _Other)
		{
			_Other->GetActor()->Destroy();
			UEngineDebug::OutPutString("Enter");
		});
}

ABossPlatform::~ABossPlatform()
{
}

void ABossPlatform::BeginPlay()
{
	AActor::BeginPlay();
}

void ABossPlatform::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}
