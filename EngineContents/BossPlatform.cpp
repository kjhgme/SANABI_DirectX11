#include "PreCompile.h"
#include "BossPlatform.h"

#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>

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

	PlatformBoxRenderer->SetRelativeLocation({ 0.0f, -100.0f, 2.0f });
	PlatformBoosterRenderer->SetRelativeLocation({ 0.0f, -120.0f, 1.0f });

	PlatformBoxRenderer->SetupAttachment(RootComponent);
	PlatformBoosterRenderer->SetupAttachment(RootComponent);

	PlatformBoxRenderer->SetAutoScaleRatio(1.0f);
	PlatformBoosterRenderer->SetAutoScaleRatio(1.0f);
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
