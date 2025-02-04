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
	BGRenderer->SetSprite("Title", 3);

	BGRenderer->SetAutoScaleRatio(0.42f);
	BGRenderer->AddRelativeLocation({ 0.0f, -300.0f, 0.0f });

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
