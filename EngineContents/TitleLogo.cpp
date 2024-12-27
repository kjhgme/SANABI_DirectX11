#include "PreCompile.h"
#include "TitleLogo.h"

#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>

ATitleLogo::ATitleLogo()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	LogoRenderer = CreateDefaultSubObject<USpriteRenderer>();
	LogoRenderer->SetSprite("SNB_01.png", 0);

	//LogoRenderer->CreateAnimation("Idle", "SNB_01.png", 0, 0, 0.1f);
	//{
	//	USpriteRenderer::FrameAnimation* Animation = LogoRenderer->FindAnimation("Idle");
	//	Animation->IsAutoScale = true;
	//	Animation->AutoScaleRatio = 4.0f;
	//}
	//
	//LogoRenderer->ChangeAnimation("Idle");

	LogoRenderer->SetRelativeScale3D({ 50, 50, 1.0f });
	LogoRenderer->SetupAttachment(RootComponent);
}

ATitleLogo::~ATitleLogo()
{
}

void ATitleLogo::BeginPlay()
{
	AActor::BeginPlay();
}

void ATitleLogo::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	// AddActorLocation(FVector{ 0.001f, 0.0f, 0.0f });
}