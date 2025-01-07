#include "PreCompile.h"
#include "Player.h"
#include "ContentsEnum.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/CameraActor.h>
#include <EngineCore/Collision.h>
#include "TextBubble.h"

APlayer::APlayer()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	PlayerRenderer = CreateDefaultSubObject<USpriteRenderer>();
	ArmRenderer = CreateDefaultSubObject< USpriteRenderer>();

	InitPlayerAnimation();

	PlayerRenderer->ChangeAnimation("Idle");
	ArmRenderer->ChangeAnimation("ArmIdle");

	PlayerRenderer->SetupAttachment(RootComponent);
	ArmRenderer->SetupAttachment(RootComponent);

	PlayerRenderer->AddRelativeLocation({ 0.0f, 0.0f, static_cast<float>(ERenderOrder::PLAYER) });
	ArmRenderer->AddRelativeLocation({ 0.0f, 0.0f, static_cast<float>(ERenderOrder::ARM) });

	PlayerCamera = GetWorld()->GetCamera(0);
	PlayerCamera->AttachToActor(this);
}

APlayer::~APlayer()
{
}

void APlayer::BeginPlay()
{
	AActor::BeginPlay();

	Collision = CreateDefaultSubObject<UCollision>();
	Collision->SetupAttachment(RootComponent);
	Collision->SetCollisionProfileName("Player");
	Collision->SetRelativeLocation({ { 0.0f, 20.0f, 0.0f } });
	Collision->SetScale3D({ 18.0f, 38.0f });

	Collision->SetCollisionEnter([this](UCollision* _This, UCollision* _Other)
		{
			Gravity = 0.0f;
			UEngineDebug::OutPutString("Enter");
		});
}

void APlayer::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	UEngineCore::GetMainWindow().GetMousePos();

	if (false == SceneMode)
	{
		PlayerMove(_DeltaTime);
	}

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

	/*if (UEngineInput::IsDown('Q'))
	{
		PlayerText = GetWorld()->SpawnActor<ATextBubble>();
	}*/
	/*if (UEngineInput::IsDown('E'))
	{
		PlayerText->Destroy();
		PlayerText = nullptr;
	}*/

	if (PlayerText != nullptr)
	{
		PlayerText->AttachToActor(this);
	}
}

void APlayer::InitPlayerAnimation()
{
	// Base
	{
		PlayerRenderer->CreateAnimation("Idle", "SNB_Idle");
		ArmRenderer->CreateAnimation("ArmIdle", "SNB_Arm_Idle");

		PlayerRenderer->CreateAnimation("Walking", "SNB_Walking");
		ArmRenderer->CreateAnimation("ArmWalking", "SNB_Arm_Walking");

		PlayerRenderer->CreateAnimation("RunStart", "SNB_RunStart");
		ArmRenderer->CreateAnimation("ArmRunStart", "SNB_Arm_RunStart");
		PlayerRenderer->CreateAnimation("Running", "SNB_Running");
		ArmRenderer->CreateAnimation("ArmRunning", "SNB_Arm_Running");
		PlayerRenderer->CreateAnimation("RunStop", "SNB_RunStop");
		ArmRenderer->CreateAnimation("ArmRunStop", "SNB_Arm_RunStop");

		PlayerRenderer->CreateAnimation("Jumping", "SNB_Jumping");
		ArmRenderer->CreateAnimation("ArmJumping", "SNB_Arm_Jumping");
		PlayerRenderer->CreateAnimation("FallStart", "SNB_FallStart");
		ArmRenderer->CreateAnimation("ArmFallStart", "SNB_Arm_FallStart");
		PlayerRenderer->CreateAnimation("Falling", "SNB_Falling");
		ArmRenderer->CreateAnimation("ArmFalling", "SNB_Arm_Falling");
		PlayerRenderer->CreateAnimation("Landing", "SNB_Landing");
		ArmRenderer->CreateAnimation("ArmLanding", "SNB_Arm_Landing");
		PlayerRenderer->CreateAnimation("Land2Run", "SNB_Land2Run");
		ArmRenderer->CreateAnimation("ArmLand2Run", "SNB_Arm_Land2Run");

		PlayerRenderer->CreateAnimation("Swing", "SNB_Swing");
		PlayerRenderer->CreateAnimation("SwingJump", "SNB_SwingJump");
		ArmRenderer->CreateAnimation("ArmJSwingJump", "SNB_Arm_SwingJump");
		PlayerRenderer->CreateAnimation("SwingJumpUp", "SNB_SwingJumpUp");
		ArmRenderer->CreateAnimation("ArmSwingJumpUp", "SNB_Arm_SwingJumpUp");
	}
	// BossAnim
	{
		PlayerRenderer->CreateAnimation("SNB_Boss_001_TrainOnLoop", "SNB_Boss_001_TrainOnLoop");
		PlayerRenderer->CreateAnimation("SNB_Boss_002_TrainOn2Idle", "SNB_Boss_002_TrainOn2Idle", false);
		PlayerRenderer->CreateAnimation("SNB_Boss_004_LookBackgroundStart", "SNB_Boss_004_LookBackgroundStart", false);
		PlayerRenderer->CreateAnimation("SNB_Boss_005_LookBackgroundLoop", "SNB_Boss_005_LookBackgroundLoop");
		PlayerRenderer->CreateAnimation("SNB_Boss_006_LookBackgroundEnd", "SNB_Boss_006_LookBackgroundEnd", false);

		ArmRenderer->CreateAnimation("SNB_Arm_NoImage", "SNB_Arm_NoImage");
	}
}

void APlayer::PlayerMove(float _DeltaTime)
{
	PlayerRenderer->AddRelativeLocation({ 0.0f, _DeltaTime * -Gravity, 0.0f });
	ArmRenderer->AddRelativeLocation({ 0.0f, _DeltaTime * -Gravity, 0.0f });
	Collision->AddRelativeLocation({ 0.0f, _DeltaTime * -Gravity, 0.0f });

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

void APlayer::SetAnimation(std::string_view _Anim)
{
	PlayerRenderer->ChangeAnimation(_Anim);

	if (false == ArmRenderer->ChangeAnimation("Arm" + std::string(_Anim)))
	{
		ArmRenderer->ChangeAnimation("SNB_Arm_NoImage");
	}
}

void APlayer::SetArmPosition()
{
	FVector PlayerRenPos = PlayerRenderer->GetTransformRef().Location;

	if (IsIdle == true) {
		if (IsRight == true) {
			ArmRenderer->SetRelativeLocation(PlayerRenPos + FVector(-8.f, 4.f, static_cast<float>(ERenderOrder::ARM)));
		}
		else if(IsRight == false) {
			ArmRenderer->SetRelativeLocation(PlayerRenPos + FVector(8.f, 4.f, static_cast<float>(ERenderOrder::ARM)));
		}
	}
	else if (IsWalking == true) {
		if (IsRight == true) {
			ArmRenderer->SetRelativeLocation(PlayerRenPos + FVector(8.f, 4.f, static_cast<float>(ERenderOrder::ARM)));
		}
		else if (IsRight == false) {
			ArmRenderer->SetRelativeLocation(PlayerRenPos + FVector(-8.f, 4.f, static_cast<float>(ERenderOrder::ARM)));
		}
	}
	else if (IsRunning == true) {
		if (IsRight == true) {
			ArmRenderer->SetRelativeLocation(PlayerRenPos + FVector(-8.f, 8.f, static_cast<float>(ERenderOrder::ARM)));
		}
		else if (IsRight == false) {
			ArmRenderer->SetRelativeLocation(PlayerRenPos + FVector(8.f, 8.f, static_cast<float>(ERenderOrder::ARM)));
		}
	}
	else if (IsJumping == true) {
		if (IsRight == true) {
			ArmRenderer->SetRelativeLocation(PlayerRenPos + FVector(8.f, 4.f, static_cast<float>(ERenderOrder::ARM)));
		}
		else if (IsRight == false) {
			ArmRenderer->SetRelativeLocation(PlayerRenPos + FVector(8.f, 8.f, static_cast<float>(ERenderOrder::ARM)));
		}
	}
}
