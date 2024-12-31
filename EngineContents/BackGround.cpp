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

	BGSkyRenderer = (CreateDefaultSubObject<USpriteRenderer>());
	BGSkyRenderer->SetSprite("PRLG_BG", 3);
	BGSkyRenderer->SetOrder(static_cast<int>(ERenderOrder::BACKGROUND));

	BGMountainRenderer = (CreateDefaultSubObject<USpriteRenderer>());
	BGMountainRenderer->SetSprite("PRLG_BG", 2);
	BGMountainRenderer->SetOrder(static_cast<int>(ERenderOrder::BACKGROUND) + 1);

	BGCloudRenderer = (CreateDefaultSubObject<USpriteRenderer>());
	BGCloudRenderer->SetSprite("PRLG_BG", 1);
	BGCloudRenderer->SetOrder(static_cast<int>(ERenderOrder::BACKGROUND) + 1);

	BGSkyRenderer->SetScale3D({ 1280.0f, 720.0f, 1.0f});
	BGSkyRenderer->AddRelativeLocation({ 0.0f, -360.0f, 1.0f });

	BGMountainRenderer->SetScale3D({ 1426.f, 582.0f, 1.0f });
	BGMountainRenderer->AddRelativeLocation({ 0.0f, -360.0f, 1.0f });

	BGCloudRenderer->SetScale3D({ 1171.f, 369.0f, 1.0f });
	BGCloudRenderer->AddRelativeLocation({ 0.0f, -360.0f, 1.0f });

	BGSkyRenderer->SetupAttachment(RootComponent);
	BGMountainRenderer->SetupAttachment(RootComponent);
	BGCloudRenderer->SetupAttachment(RootComponent);
}

ABackGround::~ABackGround()
{
}
