#include "PreCompile.h"
#include "Player.h"
#include "ContentsEnum.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/CameraActor.h>
#include <EngineCore/Collision.h>
#include "TextBubble.h"
#include "PlayerVfx.h"

APlayer::APlayer()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	PlayerRenderer = CreateDefaultSubObject<USpriteRenderer>();
	ArmRenderer = CreateDefaultSubObject<USpriteRenderer>();

	InitPlayerAnimation(); 
	InitPlayerState();

	PlayerRenderer->ChangeAnimation("Idle");
	ArmRenderer->ChangeAnimation("ArmIdle");

	PlayerRenderer->SetupAttachment(RootComponent);
	ArmRenderer->SetupAttachment(RootComponent);

	PlayerRenderer->AddRelativeLocation({ 0.0f, 0.0f, static_cast<float>(ERenderOrder::PLAYER) });
	ArmRenderer->AddRelativeLocation({ 0.0f, 0.0f, static_cast<float>(ERenderOrder::ARM) });
	ArmRenderer->AddRelativeLocation({ 100.0f, 100.0f, 0.0f });

	PlayerCamera = GetWorld()->GetMainCamera();
	PlayerCamera->AttachToActor(this);

	FSM.ChangeState(PlayerState::Idle);
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
	Collision->SetScale3D({ 18.0f, 36.0f });

	Collision->SetCollisionEnter([this](UCollision* _This, UCollision* _Other)
	{
		UEngineDebug::OutPutString("Enter : " + _Other->GetCollisionProfileName());
	});

	Collision->SetCollisionEnd([this](UCollision* _This, UCollision* _Other)
	{
		UEngineDebug::OutPutString("End : " + _Other->GetCollisionProfileName());
	});
}

void APlayer::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	UEngineCore::GetMainWindow().GetMousePos();

	if (false == SceneMode)
	{
		FSM.Update(_DeltaTime);
		ApplyGravity(_DeltaTime);
		SetArmPosition();
		CheckRightDir();
	}

	//if (UEngineInput::IsDown('Q'))
	//{
	//	PlayerText = GetWorld()->SpawnActor<ATextBubble>();
	//}
	//if (UEngineInput::IsDown('E'))
	//{
	//	PlayerText->Destroy();
	//	PlayerText = nullptr;
	//}
	//if (PlayerText != nullptr)
	//{
	// 
	//	PlayerText->AttachToActor(this);
	//}
}

void APlayer::PlayerInput(float _DeltaTime)
{	
	/*if (UEngineInput::IsPress('A'))
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
		FSM.ChangeState(PlayerState::Run);
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
		FSM.ChangeState(PlayerState::Run);
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

		FSM.ChangeState(PlayerState::Idle);
	}*/
}

void APlayer::SetAnimation(std::string_view _Anim)
{
	if (false == ArmRenderer->ChangeAnimation("Arm" + std::string(_Anim)))
	{
		ArmRenderer->ChangeAnimation("SNB_Arm_NoImage");
	}
	
	PlayerRenderer->ChangeAnimation(_Anim);
}

void APlayer::SetArmPosition()
{
	FVector PlayerRenPos = PlayerRenderer->GetTransformRef().Location;

	/*if (IsIdle == true) {
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
	}*/
}

void APlayer::AddPlayerRendererLocation(FVector _Loc)
{
	PlayerRenderer->AddRelativeLocation(_Loc);
	ArmRenderer->AddRelativeLocation(_Loc);
	Collision->AddRelativeLocation(_Loc);
}

void APlayer::CheckRightDir()
{
	if (true == bIsRight)
	{
		PlayerRenderer->SetRotation({ 0.0f, 0.0f, 0.0f });
		ArmRenderer->SetRotation({ 0.0f, 0.0f, 0.0f });
	}
	else 
	{
		PlayerRenderer->SetRotation({ 0.0f, 180.0f, 0.0f });
		ArmRenderer->SetRotation({ 0.0f, 180.0f, 0.0f });
	}
}

void APlayer::ApplyGravity(float _DeltaTime)
{
	if (Collision->IsColliding())
	{
		GravityVelocity = 0;
		Gravity = 0;
	}
	else {
		Gravity = -98.0f * 2.0f;
		GravityVelocity += Gravity * _DeltaTime;
		GravityVelocity = UEngineMath::Clamp(GravityVelocity, MaxFallSpeed, 0.0f);
	}

	this->AddActorLocation({ 0.0f, _DeltaTime * GravityVelocity, 0.0f });
}

void APlayer::InitPlayerAnimation()
{
	// Base
	{
		PlayerRenderer->CreateAnimation("Idle", "SNB_Idle");
		ArmRenderer->CreateAnimation("ArmIdle", "SNB_Arm_Idle");

		PlayerRenderer->CreateAnimation("Walking", "SNB_Walking");
		ArmRenderer->CreateAnimation("ArmWalking", "SNB_Arm_Walking");

		PlayerRenderer->CreateAnimation("RunStart", "SNB_RunStart", false);
		ArmRenderer->CreateAnimation("ArmRunStart", "SNB_Arm_RunStart", false);
		PlayerRenderer->CreateAnimation("Running", "SNB_Running");
		ArmRenderer->CreateAnimation("ArmRunning", "SNB_Arm_Running");
		PlayerRenderer->CreateAnimation("RunStop", "SNB_RunStop", false);
		ArmRenderer->CreateAnimation("ArmRunStop", "SNB_Arm_RunStop", false);

		PlayerRenderer->CreateAnimation("Jumping", "SNB_Jumping", false);
		ArmRenderer->CreateAnimation("ArmJumping", "SNB_Arm_Jumping", false);
		PlayerRenderer->CreateAnimation("FallStart", "SNB_FallStart" , false);
		ArmRenderer->CreateAnimation("ArmFallStart", "SNB_Arm_FallStart", false);
		PlayerRenderer->CreateAnimation("Falling", "SNB_Falling");
		ArmRenderer->CreateAnimation("ArmFalling", "SNB_Arm_Falling");
		PlayerRenderer->CreateAnimation("Landing", "SNB_Landing", false);
		ArmRenderer->CreateAnimation("ArmLanding", "SNB_Arm_Landing", false);
		PlayerRenderer->CreateAnimation("Land2Run", "SNB_Land2Run", false);
		ArmRenderer->CreateAnimation("ArmLand2Run", "SNB_Arm_Land2Run", false);

		PlayerRenderer->CreateAnimation("Swing", "SNB_Swing");
		PlayerRenderer->CreateAnimation("SwingJump", "SNB_SwingJump");
		ArmRenderer->CreateAnimation("ArmJSwingJump", "SNB_Arm_SwingJump");
		PlayerRenderer->CreateAnimation("SwingJumpUp", "SNB_SwingJumpUp");
		ArmRenderer->CreateAnimation("ArmSwingJumpUp", "SNB_Arm_SwingJumpUp");
	}
	// BossAnim
	{
		PlayerRenderer->CreateAnimation("SNB_Boss_001_TrainOnLoop", "SNB_Boss_001_TrainOnLoop", false);
		PlayerRenderer->CreateAnimation("SNB_Boss_002_TrainOn2Idle", "SNB_Boss_002_TrainOn2Idle", false);
		PlayerRenderer->CreateAnimation("SNB_Boss_004_LookBackgroundStart", "SNB_Boss_004_LookBackgroundStart", false);
		PlayerRenderer->CreateAnimation("SNB_Boss_005_LookBackgroundLoop", "SNB_Boss_005_LookBackgroundLoop");
		PlayerRenderer->CreateAnimation("SNB_Boss_006_LookBackgroundEnd", "SNB_Boss_006_LookBackgroundEnd", false);

		ArmRenderer->CreateAnimation("SNB_Arm_NoImage", "SNB_Arm_NoImage", false);
	}	
}

void APlayer::InitPlayerState()
{
	FSM.CreateState(PlayerState::Idle, std::bind(&APlayer::Idle, this, std::placeholders::_1), [this](){});
	FSM.CreateState(PlayerState::Walking, std::bind(&APlayer::Walking, this, std::placeholders::_1), [this]() {});
	FSM.CreateState(PlayerState::RunStart, std::bind(&APlayer::RunStart, this, std::placeholders::_1), [this]() {});
	FSM.CreateState(PlayerState::Running, std::bind(&APlayer::Running, this, std::placeholders::_1), [this]() {});
	FSM.CreateState(PlayerState::RunStop, std::bind(&APlayer::RunStop, this, std::placeholders::_1), [this]() {});
	FSM.CreateState(PlayerState::Jumping, std::bind(&APlayer::Jumping, this, std::placeholders::_1), [this]() {});
	FSM.CreateState(PlayerState::FallStart, std::bind(&APlayer::FallStart, this, std::placeholders::_1), [this]() {});
	FSM.CreateState(PlayerState::Falling, std::bind(&APlayer::Falling, this, std::placeholders::_1), [this]() {});
	FSM.CreateState(PlayerState::Landing, std::bind(&APlayer::Landing, this, std::placeholders::_1), [this]() {});
	FSM.CreateState(PlayerState::Land2Run, std::bind(&APlayer::Land2Run, this, std::placeholders::_1), [this]() {});

}

void APlayer::Idle(float _DeltaTime)
{
	PlayerRenderer->ChangeAnimation("Idle");
	ArmRenderer->ChangeAnimation("ArmIdle");

	if (UEngineInput::IsPress('A'))
	{
		bIsRight = false;
		FSM.ChangeState(PlayerState::RunStart);
		return;
	}
	if (UEngineInput::IsPress('D'))
	{
		bIsRight = true;
		FSM.ChangeState(PlayerState::RunStart);
		return;
	}
	if (UEngineInput::IsPress('R'))
	{
		FSM.ChangeState(PlayerState::Walking);
		return;
	}
	if (UEngineInput::IsDown(VK_SPACE))
	{
		FSM.ChangeState(PlayerState::Jumping);
		return;
	}
}

void APlayer::Walking(float _DeltaTime)
{
	PlayerRenderer->ChangeAnimation("Walking");
	ArmRenderer->ChangeAnimation("Walking");

	float WalkVelocity = 100.0f;

	if (UEngineInput::IsPress('A'))
	{
		bIsRight = false;

		AddRelativeLocation(FVector{ -WalkVelocity * _DeltaTime, 0.0f, 0.0f });
	}	
	if (UEngineInput::IsPress('D'))
	{
		bIsRight = true;

		AddRelativeLocation(FVector{ WalkVelocity * _DeltaTime, 0.0f, 0.0f });
	}
	if (true == UEngineInput::IsFree('A') && true == UEngineInput::IsFree('D') &&
		true == UEngineInput::IsFree('W') && true == UEngineInput::IsFree('S') &&
		true == UEngineInput::IsFree('R'))
	{
		FSM.ChangeState(PlayerState::Idle);
		return;
	}
}

void APlayer::RunStart(float _DeltaTime)
{
	PlayerRenderer->ChangeAnimation("RunStart");
	ArmRenderer->ChangeAnimation("ArmRunStart");

	if (UEngineInput::IsPress('A'))
	{
		bIsRight = false;
		AddRelativeLocation(FVector{ -MoveVelocity * _DeltaTime, 0.0f, 0.0f });
	}
	if (UEngineInput::IsPress('D'))
	{
		bIsRight = true;
		AddRelativeLocation(FVector{ MoveVelocity * _DeltaTime, 0.0f, 0.0f });
	}
	if (UEngineInput::IsDown(VK_SPACE))
	{
		FSM.ChangeState(PlayerState::Jumping);
		return;
	}
	if (true == UEngineInput::IsFree('A') && true == UEngineInput::IsFree('D') &&
		true == UEngineInput::IsFree('W') && true == UEngineInput::IsFree('S'))
	{
		FSM.ChangeState(PlayerState::RunStop);
		return;
	}
	if (PlayerRenderer->IsCurAnimationEnd())
	{
		FSM.ChangeState(PlayerState::Running);
		return;
	}
}

void APlayer::Running(float _DeltaTime)
{
	PlayerRenderer->ChangeAnimation("Running");
	ArmRenderer->ChangeAnimation("ArmRunning");

	if (UEngineInput::IsPress('A'))
	{
		bIsRight = false;
		AddRelativeLocation(FVector{ -MoveVelocity * _DeltaTime, 0.0f, 0.0f });
	}
	if (UEngineInput::IsPress('D'))
	{
		bIsRight = true;		
		AddRelativeLocation(FVector{ MoveVelocity * _DeltaTime, 0.0f, 0.0f });
	}
	if (UEngineInput::IsDown(VK_SPACE))
	{
		FSM.ChangeState(PlayerState::Jumping);
		return;
	}
	if (true == UEngineInput::IsFree('A') && true == UEngineInput::IsFree('D') &&
		true == UEngineInput::IsFree('W') && true == UEngineInput::IsFree('S'))
	{
		FSM.ChangeState(PlayerState::RunStop);
		return;
	}
}

void APlayer::RunStop(float _DeltaTime)
{
	PlayerRenderer->ChangeAnimation("RunStop");
	ArmRenderer->ChangeAnimation("ArmRunStop");

	//float StopVelocity = 300.0f - _DeltaTime * 1000.0f;
	//StopVelocity = UEngineMath::Clamp(StopVelocity, 0.0f, 300.0f);

	if (UEngineInput::IsPress('A'))
	{
		bIsRight = false;
		FSM.ChangeState(PlayerState::RunStart);
		return;
	}
	if (UEngineInput::IsPress('D'))
	{
		bIsRight = true;
		FSM.ChangeState(PlayerState::RunStart);
		return;
	}

	/*if (false == bIsRight)
	{
		AddRelativeLocation(FVector{ -StopVelocity * _DeltaTime, 0.0f, 0.0f });
	}
	if (true == bIsRight)
	{
		AddRelativeLocation(FVector{ StopVelocity * _DeltaTime, 0.0f, 0.0f });
	}*/
	if (PlayerRenderer->IsCurAnimationEnd())
	{
		FSM.ChangeState(PlayerState::Idle);
		return;
	}
}

void APlayer::Jumping(float _DeltaTime)
{
	PlayerRenderer->ChangeAnimation("Jumping");
	ArmRenderer->ChangeAnimation("ArmJumping");

	if (!bHasSpawnedVfx)
	{
		std::shared_ptr<APlayerVfx> Vfx = GetWorld()->SpawnActor<APlayerVfx>();
		Vfx->InitVfx("Vfx_Jump");
		Vfx->InitPos(this->GetActorLocation());
		bHasSpawnedVfx = true;
	}

	if (true == bCanJump)
	{
		bCanJump = false;
	}

	this->AddActorLocation({ 0.0f, JumpVelocity, 0.0f });
		
	if (UEngineInput::IsPress('A'))
	{
		bIsRight = false;
		AddRelativeLocation(FVector{ -MoveVelocity * _DeltaTime, 0.0f, 0.0f });
	}
	if (UEngineInput::IsPress('D'))
	{
		bIsRight = true;
		AddRelativeLocation(FVector{ MoveVelocity * _DeltaTime, 0.0f, 0.0f });
	}
	if (PlayerRenderer->IsCurAnimationEnd())
	{
		bHasSpawnedVfx = false;
		FSM.ChangeState(PlayerState::FallStart);
		return;
	}
}

void APlayer::FallStart(float _DeltaTime)
{
	PlayerRenderer->ChangeAnimation("FallStart");
	ArmRenderer->ChangeAnimation("ArmFallStart");

	if (UEngineInput::IsPress('A'))
	{
		bIsRight = false;
		AddRelativeLocation(FVector{ -MoveVelocity * _DeltaTime, 0.0f, 0.0f });
	}
	if (UEngineInput::IsPress('D'))
	{
		bIsRight = true;
		AddRelativeLocation(FVector{ MoveVelocity * _DeltaTime, 0.0f, 0.0f });
	}
	if (PlayerRenderer->IsCurAnimationEnd())
	{
		FSM.ChangeState(PlayerState::Falling);
		return;
	}
}

void APlayer::Falling(float _DeltaTime)
{
	PlayerRenderer->ChangeAnimation("Falling");
	ArmRenderer->ChangeAnimation("ArmFalling");

	if (UEngineInput::IsPress('A'))
	{
		bIsRight = false;
		AddRelativeLocation(FVector{ -MoveVelocity * _DeltaTime, 0.0f, 0.0f });
	}
	if (UEngineInput::IsPress('D'))
	{
		bIsRight = true;
		AddRelativeLocation(FVector{ MoveVelocity * _DeltaTime, 0.0f, 0.0f });
	}

	if (Collision->IsColliding())
	{
		if (UEngineInput::IsPress('A') || UEngineInput::IsPress('D'))
		{
			FSM.ChangeState(PlayerState::Land2Run);
			return;
		}
		else
		{
			FSM.ChangeState(PlayerState::Landing);
			return;
		}
	}

}

void APlayer::Landing(float _DeltaTime)
{
	PlayerRenderer->ChangeAnimation("Landing");
	ArmRenderer->ChangeAnimation("ArmLanding");

	if (!bHasSpawnedVfx)
	{
		std::shared_ptr<APlayerVfx> Vfx = GetWorld()->SpawnActor<APlayerVfx>();
		Vfx->InitVfx("Vfx_Landing");
		Vfx->InitPos(this->GetActorLocation());
		bHasSpawnedVfx = true;
	}

	bCanJump = true;

	if (UEngineInput::IsDown(VK_SPACE))
	{
		FSM.ChangeState(PlayerState::Jumping);
		return;
	}
	if (PlayerRenderer->IsCurAnimationEnd())
	{  
		bHasSpawnedVfx = false; 
		FSM.ChangeState(PlayerState::Idle);
		return;
	}
}

void APlayer::Land2Run(float _DeltaTime)
{
	PlayerRenderer->ChangeAnimation("Land2Run");
	ArmRenderer->ChangeAnimation("ArmLand2Run");
	
	if (!bHasSpawnedVfx)
	{
		std::shared_ptr<APlayerVfx> Vfx = GetWorld()->SpawnActor<APlayerVfx>();
		Vfx->InitVfx("Vfx_Landing");
		Vfx->InitPos(this->GetActorLocation());
		bHasSpawnedVfx = true;
	}

	bCanJump = true;

	if (UEngineInput::IsPress('A'))
	{
		bIsRight = false;
		AddRelativeLocation(FVector{ -MoveVelocity * _DeltaTime, 0.0f, 0.0f });
	}
	if (UEngineInput::IsPress('D'))
	{
		bIsRight = true;
		AddRelativeLocation(FVector{ MoveVelocity * _DeltaTime, 0.0f, 0.0f });
	}
	if (UEngineInput::IsDown(VK_SPACE))
	{
		bHasSpawnedVfx = false;
		FSM.ChangeState(PlayerState::Jumping);
		return;
	}
	if (true == UEngineInput::IsFree('A') && true == UEngineInput::IsFree('D'))
	{
		bHasSpawnedVfx = false;
		FSM.ChangeState(PlayerState::RunStop);
		return;
	}

	if (PlayerRenderer->IsCurAnimationEnd())
	{
		bHasSpawnedVfx = false;
		FSM.ChangeState(PlayerState::Running);
		return;
	}
}

