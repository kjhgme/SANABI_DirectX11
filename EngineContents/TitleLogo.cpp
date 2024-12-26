#include "PreCompile.h"
#include "TitleLogo.h"

#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>

ATitleLogo::ATitleLogo()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	LogoRenderer = CreateDefaultSubObject<USpriteRenderer>();
	LogoRenderer->SetSprite("test.png", 0);

	LogoRenderer->SetRelativeScale3D({ 50, 50, 1.0f });
	LogoRenderer->SetupAttachment(RootComponent);

	Child = CreateDefaultSubObject<USpriteRenderer>();
	Child->SetSprite("Player.png", 2);
	Child->SetRelativeLocation({ 100.0f, 0.0f, 0.0f });
	Child->SetScale3D({ 50.0f, 50.0f, 1.0f });
	Child->SetupAttachment(RootComponent);
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