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

	/*Collision->SetCollisionEnter([](UCollision* _This, UCollision* _Other)
		{
			_Other->GetActor()->Destroy();
			UEngineDebug::OutPutString("Enter");
		});*/
}

void APlayer::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	UEngineCore::GetMainWindow().GetMousePos();

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
	PlayerRenderer->CreateAnimation("Jumping", "SNB_FallStart");
	ArmRenderer->CreateAnimation("ArmJumping", "SNB_Arm_FallStart");
	PlayerRenderer->CreateAnimation("Jumping", "SNB_Falling");
	ArmRenderer->CreateAnimation("ArmJumping", "SNB_Arm_Falling");
	PlayerRenderer->CreateAnimation("Jumping", "SNB_Landing");
	ArmRenderer->CreateAnimation("ArmJumping", "SNB_Arm_Landing");

	PlayerRenderer->CreateAnimation("Jumping", "SNB_Land2Run");
	ArmRenderer->CreateAnimation("ArmJumping", "SNB_Arm_Land2Run");

	PlayerRenderer->CreateAnimation("Swing", "SNB_Swing");
	PlayerRenderer->CreateAnimation("SwingJump", "SNB_SwingJump");
	ArmRenderer->CreateAnimation("ArmJSwingJump", "SNB_Arm_SwingJump");
	PlayerRenderer->CreateAnimation("SwingJumpUp", "SNB_SwingJumpUp");
	ArmRenderer->CreateAnimation("ArmSwingJumpUp", "SNB_Arm_SwingJumpUp");
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
			ArmRenderer->SetRelativeLocation({ -8.f, 4.f, static_cast<float>(ERenderOrder::ARM) });
		}
		else if(IsRight == false) {
			ArmRenderer->SetRelativeLocation({ 8.f, 4.f, static_cast<float>(ERenderOrder::ARM) });
		}
	}
	else if (IsWalking == true) {
		if (IsRight == true) {
			ArmRenderer->SetRelativeLocation({ 8.f, 4.f, static_cast<float>(ERenderOrder::ARM) });
		}
		else if (IsRight == false) {
			ArmRenderer->SetRelativeLocation({ -8.f, 4.f, static_cast<float>(ERenderOrder::ARM) });
		}
	}
	else if (IsRunning == true) {
		if (IsRight == true) {
			ArmRenderer->SetRelativeLocation({ -8.f, 8.f, static_cast<float>(ERenderOrder::ARM) });
		}
		else if (IsRight == false) {
			ArmRenderer->SetRelativeLocation({ 8.f, 8.f, static_cast<float>(ERenderOrder::ARM) });
		}
	}
	else if (IsJumping == true) {
		if (IsRight == true) {
			ArmRenderer->SetRelativeLocation({ 8.f, 4.f, static_cast<float>(ERenderOrder::ARM) });
		}
		else if (IsRight == false) {
			ArmRenderer->SetRelativeLocation({ 8.f, 8.f, static_cast<float>(ERenderOrder::ARM) });
		}
	}
}
