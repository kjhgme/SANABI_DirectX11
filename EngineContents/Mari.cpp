#include "PreCompile.h"
#include "Mari.h"
#include "ContentsEnum.h"

#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>

AMari::AMari()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	MariRenderer = CreateDefaultSubObject<USpriteRenderer>();
	InitPlayerAnimation();

	MariRenderer->ChangeAnimation("Idle");
	MariRenderer->AddRelativeLocation({ 0.0f, 0.0f, static_cast<float>(ERenderOrder::PLAYER) });

	MariRenderer->SetupAttachment(RootComponent);
}

AMari::~AMari()
{
}

void AMari::InitPlayerAnimation()
{

}
