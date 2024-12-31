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
	SetArmPosition();

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
	SetAnimation(PlayerRenderer, "Idle", "SNB_Idle", 0, 7);
	SetAnimation(ArmRenderer, "ArmIdle", "SNB_Arm_Idle", 0, 7);
	SetAnimation(PlayerRenderer, "Walking", "SNB_Walking", 0, 11);
	SetAnimation(ArmRenderer, "ArmWalking", "SNB_Arm_Walking", 0, 11);
	SetAnimation(PlayerRenderer, "RunStart", "SNB_RunStart", 0, 1);
	SetAnimation(ArmRenderer, "ArmRunStart", "SNB_Arm_RunStart", 0, 1);
	SetAnimation(PlayerRenderer, "Running", "SNB_Running", 0, 19);
	SetAnimation(ArmRenderer, "ArmRunning", "SNB_Arm_Running", 0, 19);
	SetAnimation(PlayerRenderer, "RunStop", "SNB_RunStop", 0, 5);
	SetAnimation(ArmRenderer, "ArmRunStop", "SNB_Arm_RunStop", 0, 5);
	SetAnimation(PlayerRenderer, "Jumping", "SNB_Jumping", 0, 5);
	SetAnimation(ArmRenderer, "ArmJumping", "SNB_Arm_Jumping", 0, 5);
	SetAnimation(PlayerRenderer, "Jumping", "SNB_FallStart", 0, 2);
	SetAnimation(ArmRenderer, "ArmJumping", "SNB_Arm_FallStart", 0, 2);
	SetAnimation(PlayerRenderer, "Jumping", "SNB_Falling", 0, 2);
	SetAnimation(ArmRenderer, "ArmJumping", "SNB_Arm_Falling", 0, 2);
	SetAnimation(PlayerRenderer, "Jumping", "SNB_Landing", 0, 2);
	SetAnimation(ArmRenderer, "ArmJumping", "SNB_Arm_Landing", 0, 2);
	SetAnimation(PlayerRenderer, "Jumping", "SNB_Land2Run", 0, 11);
	SetAnimation(ArmRenderer, "ArmJumping", "SNB_Arm_Land2Run", 0, 11);
	SetAnimation(PlayerRenderer, "Swing", "SNB_Swing", 0, 14);
	SetAnimation(PlayerRenderer, "SwingJump", "SNB_SwingJump", 0, 8);
	SetAnimation(ArmRenderer, "ArmJSwingJump", "SNB_Arm_SwingJump", 0, 8);
	SetAnimation(PlayerRenderer, "SwingJumpUp", "SNB_SwingJumpUp", 0, 4);
	SetAnimation(ArmRenderer, "ArmSwingJumpUp", "SNB_Arm_SwingJumpUp", 0, 4);
}

void APlayer::SetAnimation(std::shared_ptr<class USpriteRenderer> Renderer, std::string_view AnimationName, std::string_view TextureName, int StartFrame, int EndFrame, float FrameRate, float AutoScaleRatio)
{
	Renderer->CreateAnimation(AnimationName, TextureName, StartFrame, EndFrame, FrameRate);
	USpriteRenderer::FrameAnimation* Animation = Renderer->FindAnimation(AnimationName);
	if (Animation)
	{
		Animation->IsAutoScale = true;
		Animation->AutoScaleRatio = AutoScaleRatio;
	}
}

void APlayer::PlayerMove(float _DeltaTime)
{
		if (UEngineInput::IsPress('A'))
		{
			IsRight = false;
			if (IsWalking == true) {
				PlayerRenderer->ChangeAnimation("Walking");
				ArmRenderer->ChangeAnimation("ArmWalking");
				PlayerRenderer->SetRotation({ 0.0f, 180.0f, 0.0f });
				ArmRenderer->SetRotation({ 0.0f, 180.0f, 0.0f });

				AddRelativeLocation(FVector{ -100.0f * _DeltaTime, 0.0f, 0.0f });
			}
			else if (IsRunning == true) {
				PlayerRenderer->ChangeAnimation("Running");
				ArmRenderer->ChangeAnimation("ArmRunning");
				PlayerRenderer->SetRotation({ 0.0f, 180.0f, 0.0f });
				ArmRenderer->SetRotation({ 0.0f, 180.0f, 0.0f });

				AddRelativeLocation(FVector{ -300.0f * _DeltaTime, 0.0f, 0.0f });
			}
		}
		if (UEngineInput::IsPress('D'))
		{
			IsRight = true;
			if (IsWalking == true) {
				PlayerRenderer->ChangeAnimation("Walking");
				ArmRenderer->ChangeAnimation("ArmWalking");
				PlayerRenderer->SetRotation({ 0.0f, 0.0f, 0.0f });
				ArmRenderer->SetRotation({ 0.0f, 0.0f, 0.0f });

				AddRelativeLocation(FVector{ 100.0f * _DeltaTime, 0.0f, 0.0f });
			}
			else if (IsRunning == true) {
				PlayerRenderer->ChangeAnimation("Running");
				ArmRenderer->ChangeAnimation("ArmRunning");
				PlayerRenderer->SetRotation({ 0.0f, 0.0f, 0.0f });
				ArmRenderer->SetRotation({ 0.0f, 0.0f, 0.0f });

				AddRelativeLocation(FVector{ 300.0f * _DeltaTime, 0.0f, 0.0f });
			}
		}
		if (UEngineInput::IsPress(VK_SPACE))
		{
			PlayerRenderer->ChangeAnimation("Jumping");
			ArmRenderer->ChangeAnimation("ArmJumping");
		}
		if (true == UEngineInput::IsFree('A') && true == UEngineInput::IsFree('D') &&
			true == UEngineInput::IsFree('W') && true == UEngineInput::IsFree('S') &&
			true == UEngineInput::IsFree('T'))
		{
			IsIdle = true;
			PlayerRenderer->ChangeAnimation("Idle");
			ArmRenderer->ChangeAnimation("ArmIdle");
		}	
}

void APlayer::SetArmPosition()
{
	if (IsIdle == true) {
		if (IsRight == true) {
			ArmRenderer->SetRelativeLocation({ -16.f, 8.f, 0.f });
		}
		else if(IsRight == false) {
			ArmRenderer->SetRelativeLocation({ 16.f, 8.f, 0.f });
		}
	}
	else if (IsWalking == true) {
		if (IsRight == true) {
			ArmRenderer->SetRelativeLocation({ 16.f, 8.f, 0.f });
		}
		else if (IsRight == false) {
			ArmRenderer->SetRelativeLocation({ -16.f, 8.f, 0.f });
		}
	}
	else if (IsRunning == true) {
		if (IsRight == true) {
			ArmRenderer->SetRelativeLocation({ -16.f, 15.f, 0.f });
		}
		else if (IsRight == false) {
			ArmRenderer->SetRelativeLocation({ 16.f, 15.f, 0.f });
		}
	}
	else if (IsJumping == true) {
		if (IsRight == true) {
			ArmRenderer->SetRelativeLocation({ 16.f, 8.f, 0.f });
		}
		else if (IsRight == false) {
			ArmRenderer->SetRelativeLocation({ 16.f, 15.f, 0.f });
		}
	}
}
