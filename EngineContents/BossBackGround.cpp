#include "PreCompile.h"
#include "BossBackGround.h"
#include "ContentsEnum.h"

#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/CameraActor.h>
#include <EngineCore/EngineCore.h>
#include <EngineCore/Level.h>

ABossBackGround::ABossBackGround()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	BG_Sky_Renderer = CreateDefaultSubObject<USpriteRenderer>();
	BG_Cloud1_Renderer = CreateDefaultSubObject<USpriteRenderer>();
	BG_Cloud2_Renderer = CreateDefaultSubObject<USpriteRenderer>();
	BG_Building1_Renderer = CreateDefaultSubObject<USpriteRenderer>();
	BG_Building2_Renderer = CreateDefaultSubObject<USpriteRenderer>();
	
	BG_Sky_Renderer->SetSprite("BOSS_BG", 0);
	BG_Cloud1_Renderer->SetSprite("BOSS_BG", 1);
	BG_Cloud2_Renderer->SetSprite("BOSS_BG", 2);
	BG_Building1_Renderer->SetSprite("BOSS_BG", 3);
	BG_Building2_Renderer->SetSprite("BOSS_BG", 4);

	BG_Sky_Renderer->SetRelativeLocation({ 0.0f, -1500.0f, static_cast<float>(ERenderOrder::BACKGROUND)-1 });
	BG_Cloud1_Renderer->SetRelativeLocation({ 0.0f, -1000.0f, static_cast<float>(ERenderOrder::BACKGROUND)-2 });
	BG_Cloud2_Renderer->SetRelativeLocation({ 0.0f, -300.0f, static_cast<float>(ERenderOrder::BACKGROUND)-3 });
	BG_Building1_Renderer->SetRelativeLocation({ 0.0f, -2500.0f, static_cast<float>(ERenderOrder::BACKGROUND)-4 });
	BG_Building2_Renderer->SetRelativeLocation({ 0.0f, -3000.0f, static_cast<float>(ERenderOrder::BACKGROUND)-5 });

	BG_Sky_Renderer->SetupAttachment(RootComponent);
	BG_Cloud1_Renderer->SetupAttachment(RootComponent);
	BG_Cloud2_Renderer->SetupAttachment(RootComponent);
	BG_Building1_Renderer->SetupAttachment(RootComponent);
	BG_Building2_Renderer->SetupAttachment(RootComponent);

	BG_Sky_Renderer->SetAutoScaleRatio(4.0f);
	BG_Cloud1_Renderer->SetAutoScaleRatio(4.0f);
	BG_Cloud2_Renderer->SetAutoScaleRatio(4.0f);
	BG_Building1_Renderer->SetAutoScaleRatio(4.0f);
	BG_Building2_Renderer->SetAutoScaleRatio(4.0f);
}

ABossBackGround::~ABossBackGround()
{
}