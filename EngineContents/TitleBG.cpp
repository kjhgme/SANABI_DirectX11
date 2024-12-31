#include "PreCompile.h"
#include "TitleBG.h"
#include "ContentsEnum.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>

ATitleBG::ATitleBG()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	BGRenderer = CreateDefaultSubObject<USpriteRenderer>();
	BGRenderer->SetSprite("Title", 2);
	BGRenderer->SetOrder(static_cast<int>(ERenderOrder::BACKGROUND));

	BGRenderer->SetScale3D({ 1280.0f, 720.0f, 1.0f });
	BGRenderer->AddRelativeLocation({ 0.0f, -360.0f, 1.0f });

	BGRenderer->SetupAttachment(RootComponent);
}

ATitleBG::~ATitleBG()
{
}

void ATitleBG::BeginPlay()
{
	AActor::BeginPlay();
}

void ATitleBG::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	if (UEngineInput::IsPress(VK_SPACE))
	{
		UEngineCore::OpenLevel("InGameLevel");
	}
}
