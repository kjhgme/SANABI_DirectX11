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

	BG_Cloud1_Renderer2 = CreateDefaultSubObject<USpriteRenderer>();
	BG_Cloud2_Renderer2 = CreateDefaultSubObject<USpriteRenderer>();
	BG_Building1_Renderer2 = CreateDefaultSubObject<USpriteRenderer>();
	BG_Building2_Renderer2 = CreateDefaultSubObject<USpriteRenderer>();

	
	BG_Sky_Renderer->SetSprite("BOSS_BG", 0);
	BG_Cloud1_Renderer->SetSprite("BOSS_BG", 1);
	BG_Cloud2_Renderer->SetSprite("BOSS_BG", 2);
	BG_Building1_Renderer->SetSprite("BOSS_BG", 3);
	BG_Building2_Renderer->SetSprite("BOSS_BG", 4);

	BG_Cloud1_Renderer2->SetSprite("BOSS_BG", 1);
	BG_Cloud2_Renderer2->SetSprite("BOSS_BG", 2);
	BG_Building1_Renderer2->SetSprite("BOSS_BG", 3);
	BG_Building2_Renderer2->SetSprite("BOSS_BG", 4);

	BG_Sky_Renderer->SetRelativeLocation({ 0.0f, -830.0f, static_cast<float>(ERenderOrder::BACKGROUND) - 1 });
	BG_Cloud1_Renderer->SetRelativeLocation({ -830.0f, -100.0f, static_cast<float>(ERenderOrder::BACKGROUND) - 2 });
	BG_Cloud2_Renderer->SetRelativeLocation({ -830.0f, -100.0f, static_cast<float>(ERenderOrder::BACKGROUND) - 3 });
	BG_Building1_Renderer->SetRelativeLocation({ -830.0f, -645.0f, static_cast<float>(ERenderOrder::BACKGROUND) - 4 });
	BG_Building2_Renderer->SetRelativeLocation({ -830.0f, -700.0f, static_cast<float>(ERenderOrder::BACKGROUND) - 5 });

	BG_Cloud1_Renderer2->SetRelativeLocation({ 830.0f, -100.0f, static_cast<float>(ERenderOrder::BACKGROUND) - 2 });
	BG_Cloud2_Renderer2->SetRelativeLocation({ 830.0f, -100.0f, static_cast<float>(ERenderOrder::BACKGROUND) - 3 });
	BG_Building1_Renderer2->SetRelativeLocation({ 830.0f, -645.0f, static_cast<float>(ERenderOrder::BACKGROUND) - 4 });
	BG_Building2_Renderer2->SetRelativeLocation({ 830.0f, -700.0f, static_cast<float>(ERenderOrder::BACKGROUND) - 5 });

	BG_Sky_Renderer->SetupAttachment(RootComponent);
	BG_Cloud1_Renderer->SetupAttachment(RootComponent);
	BG_Cloud2_Renderer->SetupAttachment(RootComponent);
	BG_Building1_Renderer->SetupAttachment(RootComponent);
	BG_Building2_Renderer->SetupAttachment(RootComponent);

	BG_Cloud1_Renderer2->SetupAttachment(RootComponent);
	BG_Cloud2_Renderer2->SetupAttachment(RootComponent);
	BG_Building1_Renderer2->SetupAttachment(RootComponent);
	BG_Building2_Renderer2->SetupAttachment(RootComponent);

	BG_Sky_Renderer->SetAutoScale(false);
	BG_Sky_Renderer->SetScale3D({ 830.0f * 3.2f, 830.0f * 2.0f, 0.0f });
}

ABossBackGround::~ABossBackGround()
{
}
void ABossBackGround::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	BG_Cloud1_Renderer->AddUVPlusValue({ _DeltaTime * 0.008f, 0.0f, 0.0f, 1.0f });
	BG_Cloud2_Renderer->AddUVPlusValue({ _DeltaTime * 0.024f, 0.0f, 0.0f, 1.0f });
	BG_Building1_Renderer->AddUVPlusValue({ _DeltaTime * 0.08f, 0.0f, 0.0f, 1.0f });
	BG_Building2_Renderer->AddUVPlusValue({ _DeltaTime * 0.16f, 0.0f, 0.0f, 1.0f });

	BG_Cloud1_Renderer2->AddUVPlusValue({ _DeltaTime * 0.008f, 0.0f, 0.0f, 1.0f });
	BG_Cloud2_Renderer2->AddUVPlusValue({ _DeltaTime * 0.024f, 0.0f, 0.0f, 1.0f });
	BG_Building1_Renderer2->AddUVPlusValue({ _DeltaTime * 0.08f, 0.0f, 0.0f, 1.0f });
	BG_Building2_Renderer2->AddUVPlusValue({ _DeltaTime * 0.16f, 0.0f, 0.0f, 1.0f });
}