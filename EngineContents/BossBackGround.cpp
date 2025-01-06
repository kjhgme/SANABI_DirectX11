#include "PreCompile.h"
#include "BossBackGround.h"

#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>

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

	BG_Sky_Renderer->SetRelativeLocation({ 0.0f, -360.0f, 1000.0f });
	BG_Cloud1_Renderer->SetRelativeLocation({ 0.0f, -360.0f, 999.0f });
	BG_Cloud2_Renderer->SetRelativeLocation({ 0.0f, -360.0f, 998.0f });
	BG_Building1_Renderer->SetRelativeLocation({ 0.0f, -360.0f, 997.0f });
	BG_Building2_Renderer->SetRelativeLocation({ 0.0f, -360.0f, 996.0f });

	BG_Sky_Renderer->SetupAttachment(RootComponent);
	BG_Cloud1_Renderer->SetupAttachment(RootComponent);
	BG_Cloud2_Renderer->SetupAttachment(RootComponent);
	BG_Building1_Renderer->SetupAttachment(RootComponent);
	BG_Building2_Renderer->SetupAttachment(RootComponent);

	BG_Sky_Renderer->SetAutoScaleRatio(2.f);
}

ABossBackGround::~ABossBackGround()
{
}

void ABossBackGround::BeginPlay()
{
	AActor::BeginPlay();
	

}

void ABossBackGround::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);


}
