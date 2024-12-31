#include "PreCompile.h"
#include "EndingPlayer.h"
#include "ContentsEnum.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>

AEndingPlayer::AEndingPlayer()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	PlayerRenderer = CreateDefaultSubObject<USpriteRenderer>();

	InitPlayerAnimation();

	PlayerRenderer->ChangeAnimation("Idle");
	PlayerRenderer->SetOrder(static_cast<int>(ERenderOrder::PLAYER));

	PlayerRenderer->SetRelativeScale3D({ 1.0f, 1.0f, 1.0f });
	PlayerRenderer->SetupAttachment(RootComponent);
}

AEndingPlayer::~AEndingPlayer()
{
}

void AEndingPlayer::InitPlayerAnimation()
{
	SetAnimation(PlayerRenderer, "Idle", "SNB_Idle");
	SetAnimation(PlayerRenderer, "BadEnding", "BadEnding", false);
}

void AEndingPlayer::SetAnimation(std::shared_ptr<class USpriteRenderer> Renderer, std::string_view AnimationName, std::string_view TextureName, bool Loop /*= true*/, float FrameRate /*= 0.12f*/, float AutoScaleRatio /*= 2.0f*/)
{
	Renderer->CreateAnimation(AnimationName, TextureName, FrameRate, Loop);
	USpriteRenderer::FrameAnimation* Animation = Renderer->FindAnimation(AnimationName);
	if (Animation)
	{
		Animation->IsAutoScale = true;
		Animation->AutoScaleRatio = AutoScaleRatio;
	}
}

void AEndingPlayer::BeginPlay()
{
	AActor::BeginPlay();
}

void AEndingPlayer::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	if (UEngineInput::IsDown('E'))
	{
		PlayerRenderer->ChangeAnimation("BadEnding");
		PlayerRenderer->AddRelativeLocation({ 0.0f, -360.0f, 1.0f });
	}
}
