#include "PreCompile.h"
#include "BackGround.h"
#include "ContentsEnum.h"

#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/EngineCore.h>
#include <EnginePlatform/EngineWindow.h>

ABackGround::ABackGround()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	BackGroundRenderer = (CreateDefaultSubObject<USpriteRenderer>());
	BackGroundRenderer->SetSprite("PRLG_BG", 3);
	BackGroundRenderer->SetOrder(static_cast<int>(ERenderOrder::BACKGROUND));

	BackGroundRenderer->SetScale3D({ 1280.0f, 720.0f, 1.0f});
	BackGroundRenderer->AddRelativeLocation({ 0.0f, -360.0f, 1.0f });
	BackGroundRenderer->SetupAttachment(RootComponent);
}

ABackGround::~ABackGround()
{
}
