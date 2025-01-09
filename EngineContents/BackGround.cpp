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
	BGMountainRenderer = (CreateDefaultSubObject<USpriteRenderer>());
	BGCloudRenderer = (CreateDefaultSubObject<USpriteRenderer>());

	BGSkyRenderer->SetSprite("PRLG_BG", 3);
	BGMountainRenderer->SetSprite("PRLG_BG", 2);
	BGCloudRenderer->SetSprite("PRLG_BG", 1);

	BGSkyRenderer->AddRelativeLocation({ 0.0f, -360.0f, static_cast<int>(ERenderOrder::BACKGROUND)-1 });
	BGMountainRenderer->AddRelativeLocation({ 0.0f, -360.0f, static_cast<int>(ERenderOrder::BACKGROUND) - 2 });
	BGCloudRenderer->AddRelativeLocation({ 0.0f, -360.0f, static_cast<int>(ERenderOrder::BACKGROUND) - 3 });

	BGSkyRenderer->SetupAttachment(RootComponent);
	BGMountainRenderer->SetupAttachment(RootComponent);
	BGCloudRenderer->SetupAttachment(RootComponent);

	BGSkyRenderer->SetAutoScaleRatio(2.0f);
	BGMountainRenderer->SetAutoScaleRatio(2.0f);
	BGCloudRenderer->SetAutoScaleRatio(2.0f);
}

ABackGround::~ABackGround()
{
}
