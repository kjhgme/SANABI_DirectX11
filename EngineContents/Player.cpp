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
		Animation->AutoScaleRatio = 2.0f;
	}

	PlayerRenderer->CreateAnimation("Walking", "SNB_Walking", 0, 11, 0.1f);
	{
		USpriteRenderer::FrameAnimation* Animation = PlayerRenderer->FindAnimation("Walking");
		Animation->IsAutoScale = true;
		Animation->AutoScaleRatio = 2.0f;
	}

	PlayerRenderer->ChangeAnimation("Idle");

	PlayerRenderer->SetRelativeScale3D({ 1.0f, 1.0f, 1.0f });
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

	PlayerMove(_DeltaTime);
}

void APlayer::PlayerMove(float _DeltaTime)
{
	if (UEngineInput::IsPress('W'))
	{
		PlayerRenderer->ChangeAnimation("Walking");
		AddRelativeLocation(FVector{ 0.0f, 100.0f * _DeltaTime, 0.0f });
	}
	if (UEngineInput::IsPress('A'))
	{
		PlayerRenderer->ChangeAnimation("Walking");
		PlayerRenderer->SetRotation({ 0.0f, 180.0f, 0.0f });

		AddRelativeLocation(FVector{ -100.0f * _DeltaTime, 0.0f, 0.0f });
	}
	if (UEngineInput::IsPress('S'))
	{
		PlayerRenderer->ChangeAnimation("Walking");
		AddRelativeLocation(FVector{ 0.0f, -100.0f * _DeltaTime, 0.0f });
	}
	if (UEngineInput::IsPress('D'))
	{
		PlayerRenderer->ChangeAnimation("Walking");
		PlayerRenderer->SetRotation({ 0.0f, 0.0f, 0.0f });

		AddRelativeLocation(FVector{ 100.0f * _DeltaTime, 0.0f, 0.0f });
	}
	if (true == UEngineInput::IsFree('A') && true == UEngineInput::IsFree('D') &&
		true == UEngineInput::IsFree('W') && true == UEngineInput::IsFree('S'))
	{
		PlayerRenderer->ChangeAnimation("Idle");
	}

}