#include "PreCompile.h"
#include "Player.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>

APlayer::APlayer()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	PlayerRenderer = CreateDefaultSubObject<USpriteRenderer>();

	PlayerRenderer->CreateAnimation("Idle", "SNB_Idle", 0, 7, 0.1f);
	{
		USpriteRenderer::FrameAnimation* Animation = PlayerRenderer->FindAnimation("Idle");
		Animation->IsAutoScale = true;
		Animation->AutoScaleRatio = 1.0f;
	}

	PlayerRenderer->CreateAnimation("Walking", "SNB_Walking", 0, 11, 0.1f);
	{
		USpriteRenderer::FrameAnimation* Animation = PlayerRenderer->FindAnimation("Walking");
		Animation->IsAutoScale = true;
		Animation->AutoScaleRatio = 1.0f;
	}

	PlayerRenderer->ChangeAnimation("Idle");

	PlayerRenderer->SetRelativeScale3D({ 50, 50, 1.0f });
	PlayerRenderer->SetupAttachment(RootComponent);
}

APlayer::~APlayer()
{
}

void APlayer::BeginPlay()
{
	AActor::BeginPlay();
}

void APlayer::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	if (UEngineInput::IsPress('A'))
	{
		PlayerRenderer->ChangeAnimation("Walking");
		AddRelativeLocation(FVector{ -100.0f * _DeltaTime, 0.0f, 0.0f });
	}
	if (UEngineInput::IsPress('D'))
	{
		PlayerRenderer->ChangeAnimation("Walking");
		AddRelativeLocation(FVector{ 100.0f * _DeltaTime, 0.0f, 0.0f });
	}
	if (UEngineInput::IsPress('W'))
	{
		PlayerRenderer->ChangeAnimation("Walking");
		AddRelativeLocation(FVector{ 0.0f, 100.0f * _DeltaTime, 0.0f });
	}
	if (UEngineInput::IsPress('S'))
	{
		PlayerRenderer->ChangeAnimation("Walking");
		AddRelativeLocation(FVector{ 0.0f, -100.0f * _DeltaTime, 0.0f });
	}
}

