#include "PreCompile.h"
#include "Player.h"
#include "ContentsEnum.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>

APlayer::APlayer()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	PlayerRenderer = CreateDefaultSubObject<USpriteRenderer>();
	ArmRenderer = CreateDefaultSubObject< USpriteRenderer>();

	InitPlayerAnimation();

	PlayerRenderer->ChangeAnimation("Idle");
	PlayerRenderer->SetOrder(static_cast<int>(ERenderOrder::PLAYER));

	PlayerRenderer->SetRelativeScale3D({ 1.0f, 1.0f, 1.0f });
	PlayerRenderer->SetupAttachment(RootComponent);

	ArmRenderer->ChangeAnimation("ArmIdle");
	ArmRenderer->SetOrder(static_cast<int>(ERenderOrder::PLAYER));

	ArmRenderer->SetRelativeScale3D({ 1.0f, 1.0f, 1.0f });
	ArmRenderer->SetRelativeLocation({ -16.f, 8.f, 0.f });
	ArmRenderer->SetupAttachment(RootComponent);
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

	if (UEngineInput::IsPress(VK_SHIFT))
	{
		IsWalking = false;
		IsRunning = true;
	}
	if (UEngineInput::IsDown('T'))
	{
		IsIdle = false;
		IsWalking = false;
		IsRunning = false;
		IsJumping = true;

		PlayerRenderer->ChangeAnimation("Jumping");
		ArmRenderer->ChangeAnimation("ArmJumping");
	}
}

void APlayer::InitPlayerAnimation()
{
	PlayerRenderer->CreateAnimation("Idle", "SNB_Idle", 0, 7, 0.12f);
	{
		USpriteRenderer::FrameAnimation* Animation = PlayerRenderer->FindAnimation("Idle");
		Animation->IsAutoScale = true;
		Animation->AutoScaleRatio = 2.0f;
	}
	ArmRenderer->CreateAnimation("ArmIdle", "SNB_Arm_Idle", 0, 7, 0.12f);
	{
		USpriteRenderer::FrameAnimation* Animation = ArmRenderer->FindAnimation("ArmIdle");
		Animation->IsAutoScale = true;
		Animation->AutoScaleRatio = 2.0f;
	}
	PlayerRenderer->CreateAnimation("Walking", "SNB_Walking", 0, 11, 0.12f);
	{
		USpriteRenderer::FrameAnimation* Animation = PlayerRenderer->FindAnimation("Walking");
		Animation->IsAutoScale = true;
		Animation->AutoScaleRatio = 2.0f;
	}
	ArmRenderer->CreateAnimation("ArmWalking", "SNB_Arm_Walking", 0, 11, 0.12f);
	{
		USpriteRenderer::FrameAnimation* Animation = ArmRenderer->FindAnimation("ArmWalking");
		Animation->IsAutoScale = true;
		Animation->AutoScaleRatio = 2.0f;
	}
	PlayerRenderer->CreateAnimation("RunStart", "SNB_RunStart", 0, 11, 0.12f);
	{
		USpriteRenderer::FrameAnimation* Animation = PlayerRenderer->FindAnimation("RunStart");
		Animation->IsAutoScale = true;
		Animation->AutoScaleRatio = 2.0f;
	}
	ArmRenderer->CreateAnimation("ArmRunStart", "SNB_Arm_RunStart", 0, 11, 0.12f);
	{
		USpriteRenderer::FrameAnimation* Animation = ArmRenderer->FindAnimation("ArmRunStart");
		Animation->IsAutoScale = true;
		Animation->AutoScaleRatio = 2.0f;
	}
	PlayerRenderer->CreateAnimation("Running", "SNB_Running", 0, 11, 0.12f);
	{
		USpriteRenderer::FrameAnimation* Animation = PlayerRenderer->FindAnimation("Running");
		Animation->IsAutoScale = true;
		Animation->AutoScaleRatio = 2.0f;
	}
	ArmRenderer->CreateAnimation("ArmRunning", "SNB_Arm_Running", 0, 11, 0.12f);
	{
		USpriteRenderer::FrameAnimation* Animation = ArmRenderer->FindAnimation("ArmRunning");
		Animation->IsAutoScale = true;
		Animation->AutoScaleRatio = 2.0f;
	}	
	PlayerRenderer->CreateAnimation("RunStop", "SNB_RunStop", 0, 11, 0.12f);
	{
		USpriteRenderer::FrameAnimation* Animation = PlayerRenderer->FindAnimation("RunStop");
		Animation->IsAutoScale = true;
		Animation->AutoScaleRatio = 2.0f;
	}
	ArmRenderer->CreateAnimation("ArmRunStop", "SNB_Arm_RunStop", 0, 11, 0.12f);
	{
		USpriteRenderer::FrameAnimation* Animation = ArmRenderer->FindAnimation("ArmRunStop");
		Animation->IsAutoScale = true;
		Animation->AutoScaleRatio = 2.0f;
	}
	PlayerRenderer->CreateAnimation("Jumping", "SNB_Jumping", 0, 5, 0.12f);
	{
		USpriteRenderer::FrameAnimation* Animation = PlayerRenderer->FindAnimation("Jumping");
		Animation->IsAutoScale = true;
		Animation->AutoScaleRatio = 2.0f;
	}
	ArmRenderer->CreateAnimation("ArmJumping", "SNB_Arm_Jumping", 0, 5, 0.12f);
	{
		USpriteRenderer::FrameAnimation* Animation = ArmRenderer->FindAnimation("ArmJumping");
		Animation->IsAutoScale = true;
		Animation->AutoScaleRatio = 2.0f;
	}
}

void APlayer::PlayerMove(float _DeltaTime)
{
	if (IsWalking == true)
	{
		if (UEngineInput::IsPress('W'))
		{
			PlayerRenderer->ChangeAnimation("Walking");
			ArmRenderer->ChangeAnimation("ArmWalking");
			AddRelativeLocation(FVector{ 0.0f, 100.0f * _DeltaTime, 0.0f });
		}
		if (UEngineInput::IsPress('A'))
		{
			PlayerRenderer->ChangeAnimation("Walking");
			ArmRenderer->ChangeAnimation("ArmWalking");
			PlayerRenderer->SetRotation({ 0.0f, 180.0f, 0.0f });
			ArmRenderer->SetRotation({ 0.0f, 180.0f, 0.0f });
			ArmRenderer->SetRelativeLocation({ 16.f, 8.f, 0.f });

			AddRelativeLocation(FVector{ -100.0f * _DeltaTime, 0.0f, 0.0f });
		}
		if (UEngineInput::IsPress('S'))
		{
			PlayerRenderer->ChangeAnimation("Walking");
			ArmRenderer->ChangeAnimation("ArmWalking");
			AddRelativeLocation(FVector{ 0.0f, -100.0f * _DeltaTime, 0.0f });
		}
		if (UEngineInput::IsPress('D'))
		{
			PlayerRenderer->ChangeAnimation("Walking");
			ArmRenderer->ChangeAnimation("ArmWalking");
			PlayerRenderer->SetRotation({ 0.0f, 0.0f, 0.0f });
			ArmRenderer->SetRotation({ 0.0f, 0.0f, 0.0f });
			ArmRenderer->SetRelativeLocation({ -16.f, 8.f, 0.f });

			AddRelativeLocation(FVector{ 100.0f * _DeltaTime, 0.0f, 0.0f });
		}
		if (UEngineInput::IsPress(VK_SPACE))
		{
			PlayerRenderer->ChangeAnimation("Jumping");
			ArmRenderer->ChangeAnimation("ArmJumping");
		}
		if (true == UEngineInput::IsFree('A') && true == UEngineInput::IsFree('D') &&
			true == UEngineInput::IsFree('W') && true == UEngineInput::IsFree('S'))
		{
			PlayerRenderer->ChangeAnimation("Idle");
			ArmRenderer->ChangeAnimation("ArmIdle");
		}
	}
	else if (IsRunning == true)
	{
		if (UEngineInput::IsPress('W'))
		{
			PlayerRenderer->ChangeAnimation("Running");
			ArmRenderer->ChangeAnimation("ArmRunning");
			AddRelativeLocation(FVector{ 0.0f, 300.0f * _DeltaTime, 0.0f });
		}
		if (UEngineInput::IsPress('A'))
		{
			PlayerRenderer->ChangeAnimation("Running");
			ArmRenderer->ChangeAnimation("ArmRunning");
			PlayerRenderer->SetRotation({ 0.0f, 180.0f, 0.0f });
			ArmRenderer->SetRotation({ 0.0f, 180.0f, 0.0f });
			ArmRenderer->SetRelativeLocation({ 16.f, 15.f, 0.f });

			AddRelativeLocation(FVector{ -300.0f * _DeltaTime, 0.0f, 0.0f });
		}
		if (UEngineInput::IsPress('S'))
		{
			PlayerRenderer->ChangeAnimation("Running");
			ArmRenderer->ChangeAnimation("ArmRunning");
			AddRelativeLocation(FVector{ 0.0f, -300.0f * _DeltaTime, 0.0f });
		}
		if (UEngineInput::IsPress('D'))
		{
			PlayerRenderer->ChangeAnimation("Running");
			ArmRenderer->ChangeAnimation("ArmRunning");
			PlayerRenderer->SetRotation({ 0.0f, 0.0f, 0.0f });
			ArmRenderer->SetRotation({ 0.0f, 0.0f, 0.0f });
			ArmRenderer->SetRelativeLocation({ -16.f, 15.f, 0.f });

			AddRelativeLocation(FVector{ 300.0f * _DeltaTime, 0.0f, 0.0f });
		}
		if (true == UEngineInput::IsFree('A') && true == UEngineInput::IsFree('D') &&
			true == UEngineInput::IsFree('W') && true == UEngineInput::IsFree('S'))
		{
			PlayerRenderer->ChangeAnimation("Idle");
			ArmRenderer->ChangeAnimation("ArmIdle");
			IsRunning = false;
			IsWalking = true;
		}
	}
}