#include "PreCompile.h"
#include "BodySlap.h"

#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>

ABodySlap::ABodySlap()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	AlertRenderer = CreateDefaultSubObject<USpriteRenderer>();

	AlertRenderer->CreateAnimation("BossAttack_BodySlap", "BossAttack_BodySlap", false, 0.1f);
	AlertRenderer->CreateAnimation("BossAttack_NoImage", "BossAttack_NoImage", false);
	AlertRenderer->ChangeAnimation("BossAttack_BodySlap");
	AlertRenderer->SetAutoScaleRatio(0.8f);

	AlertRenderer->SetupAttachment(RootComponent);	
}

ABodySlap::~ABodySlap()
{
}

void ABodySlap::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	if (true == bIsRight)
	{
		AlertRenderer->SetRotation({ 0.0f, 0.0f, 0.0f });
	}
	else if (false == bIsRight)
	{
		AlertRenderer->SetRotation({ 0.0f, 180.0f, 0.0f });
	}

	if (AlertRenderer->IsCurAnimationEnd())
	{
		Destroy();
	}
}

