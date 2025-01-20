#include "PreCompile.h"
#include "Player.h"
#include "ContentsEnum.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/TimeEventComponent.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/CameraActor.h>
#include <EngineCore/Collision.h>
#include <EngineCore/FontRenderer.h>
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

	PlayerCamera = GetWorld()->GetMainCamera();
	PlayerCamera->AttachToActor(this);

	FSM.ChangeState(PlayerState::Idle);

	AimRenderer = CreateDefaultSubObject<USpriteRenderer>();
	AimRenderer->SetSprite("Aim", 0);
	AimRenderer->AddRelativeLocation({ 0.0f, 118.0f * 0.5f, 0.0f });
	//AimRenderer->SetAutoScaleRatio(0.1f);

	TimeEventComponent = CreateDefaultSubObject<UTimeEventComponent>();
}

APlayer::~APlayer()
{
}

void APlayer::BeginPlay()
{
	AActor::BeginPlay();

	// PlayerCollision
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

	// GrabCollision
	GrabCollision = CreateDefaultSubObject<UCollision>();
	GrabCollision->SetupAttachment(ArmRenderer);
	GrabCollision->SetCollisionProfileName("Grab");
	GrabCollision->AddRelativeLocation({ 0.0f, 0.8f, 0.0f});
	GrabCollision->SetScale3D({ 0.8f, 0.3f });
}

void APlayer::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);


	std::shared_ptr<class ACameraActor> Camera = GetWorld()->GetCamera(0);

	UEngineCore::GetMainWindow().GetMousePos();

	float ZDis = GetActorLocation().Z - Camera->GetActorLocation().Z;

	UEngineDebug::OutPutString(Camera->ScreenMousePosToWorldPosWithOutPos(ZDis).ToString());
	AimRenderer->SetRelativeLocation(Camera->ScreenMousePosToWorldPosWithOutPos(ZDis));


	if (false == SceneMode)
	{
		FSM.Update(_DeltaTime);
		ApplyGravity(_DeltaTime);
		CheckRightDir();
	}	
	if (UEngineInput::IsDown('G'))
	{
		FSM.ChangeState(PlayerState::Death);
	}
}

void APlayer::SetAnimation(std::string_view _Anim)
{
	if (false == ArmRenderer->ChangeAnimation("Arm" + std::string(_Anim)))
	{
		ArmRenderer->ChangeAnimation("SNB_Arm_NoImage");

	}
	
	PlayerRenderer->ChangeAnimation(_Anim);
}

void APlayer::AddPlayerRendererLocation(FVector _Loc)
{
	PlayerRenderer->AddRelativeLocation(_Loc);
	ArmRenderer->AddRelativeLocation(_Loc);
	Collision->AddRelativeLocation(_Loc);
}

void APlayer::CheckRightDir()
{
	if (false == bIsGrabbing)
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
}

void APlayer::MakeTextBubble(std::string_view _Text, float _Size)
{
	PlayerText = GetWorld()->SpawnActor<ATextBubble>();
	PlayerText->SetText(_Text, _Size);
	PlayerText->SetActorLocation(GetActorLocation());
}

void APlayer::ClearTextBubble()
{
	if (PlayerText != nullptr)
	{
		PlayerText->Destroy();
	}
}

void APlayer::GrabLaunchToPosition(FVector _Pos)
{
	FVector TargetPosition = _Pos;

	TimeEventComponent->AddUpdateEvent(0.1f, [this, TargetPosition](float DeltaTime, float CurTime)
	{
		auto Lerp = [](FVector A, FVector B, float Alpha)
		{
			return A * (1 - Alpha) + B * Alpha;
		};

		float Alpha = UEngineMath::Clamp(DeltaTime / 0.1f, 0.0f, 1.0f);
		FVector NewPosition = Lerp(FVector::ZERO, TargetPosition, Alpha);

		this->GetArmRenderer()->AddRelativeLocation(NewPosition);
	},
		false
	);
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
		// Base of Base
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
			PlayerRenderer->CreateAnimation("FallStart", "SNB_FallStart", false);
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

			PlayerRenderer->CreateAnimation("Death", "SNB_Death", false);
		}
		// Grab
		{
			ArmRenderer->CreateAnimation("ArmGrab_Flying", "SNB_Grab_Flying", false);
			ArmRenderer->CreateAnimation("ArmGrab_Grabbing", "SNB_Grab_Grabbing", false);
			ArmRenderer->CreateAnimation("ArmGrab_Grabed", "SNB_Grab_Grabed", false);
			ArmRenderer->CreateAnimation("ArmGrab_Lower_Grabbed", "SNB_Grab_Lower_Grabbed", false);
			ArmRenderer->CreateAnimation("ArmGrab_Lower_Grabbing", "SNB_Grab_Lower_Grabbing", false);
			ArmRenderer->CreateAnimation("ArmGrab_Return", "SNB_Grab_Return", false);
			ArmRenderer->CreateAnimation("ArmGrab_ReturnWithGrabbed", "SNB_Grab_ReturnWithGrabbed",false);
			ArmRenderer->CreateAnimation("ArmGrab_ReturnWithoutGrabbed", "SNB_Grab_ReturnWithoutGrabbed", false);
		}
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
	FSM.CreateState(PlayerState::Death, std::bind(&APlayer::Death, this, std::placeholders::_1), [this]() {});
	FSM.CreateState(PlayerState::Grab_Flying, std::bind(&APlayer::Grab_Flying, this, std::placeholders::_1), [this]() {});
	FSM.CreateState(PlayerState::Grab_Grabbing, std::bind(&APlayer::Grab_Grabbing, this, std::placeholders::_1), [this]() {});
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
	else if (UEngineInput::IsPress('D'))
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
	if (false == Collision->IsColliding())
	{
		FSM.ChangeState(PlayerState::FallStart);
		return;
	}
	if (true == UEngineInput::IsPress(VK_LBUTTON))
	{
		FSM.ChangeState(PlayerState::Grab_Flying);
		return;
	}
}

void APlayer::Walking(float _DeltaTime)
{
	PlayerRenderer->ChangeAnimation("Walking");
	ArmRenderer->ChangeAnimation("ArmWalking");

	float WalkVelocity = 100.0f;

	if (UEngineInput::IsPress('A'))
	{
		bIsRight = false;

		AddRelativeLocation(FVector{ -WalkVelocity * _DeltaTime, 0.0f, 0.0f });
	}
	else if (UEngineInput::IsPress('D'))
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
	else if (UEngineInput::IsPress('D'))
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
	if (false == Collision->IsColliding())
	{
		FSM.ChangeState(PlayerState::FallStart);
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
	else if (UEngineInput::IsPress('D'))
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
	if (false == Collision->IsColliding())
	{
		FSM.ChangeState(PlayerState::FallStart);
		return;
	}
}

void APlayer::RunStop(float _DeltaTime)
{
	PlayerRenderer->ChangeAnimation("RunStop");
	ArmRenderer->ChangeAnimation("ArmRunStop");

	if (UEngineInput::IsPress('A'))
	{
		bIsRight = false;
		FSM.ChangeState(PlayerState::RunStart);
		return;
	}
	else if (UEngineInput::IsPress('D'))
	{
		bIsRight = true;
		FSM.ChangeState(PlayerState::RunStart);
		return;
	}
	if (UEngineInput::IsDown(VK_SPACE))
	{
		FSM.ChangeState(PlayerState::Jumping);
		return;
	}
	if (PlayerRenderer->IsCurAnimationEnd())
	{
		FSM.ChangeState(PlayerState::Idle);
		return;
	}
	if (false == Collision->IsColliding())
	{
		FSM.ChangeState(PlayerState::FallStart);
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
	else if (UEngineInput::IsPress('D'))
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
	else if (UEngineInput::IsPress('D'))
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

	if (UEngineInput::IsPress('A') || UEngineInput::IsPress('D'))
	{
		FSM.ChangeState(PlayerState::RunStart);
		return;
	}
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
	if (false == Collision->IsColliding())
	{
		FSM.ChangeState(PlayerState::FallStart);
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
	else if (UEngineInput::IsPress('D'))
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
	if (false == Collision->IsColliding())
	{
		FSM.ChangeState(PlayerState::FallStart);
		return;
	}
}

void APlayer::Death(float _DeltaTime)
{
	PlayerRenderer->ChangeAnimation("Death");
	ArmRenderer->ChangeAnimation("SNB_Arm_NoImage");
}

void APlayer::Grab_Flying(float _DeltaTime)
{
	ArmRenderer->ChangeAnimation("ArmGrab_Flying");

	float ZDis = GetActorLocation().Z - GetWorld()->GetMainCamera()->GetActorLocation().Z;
	
	// 현재 ArmRenderer의 위치
	FVector CurrentPos = ArmRenderer->GetWorldLocation();

	// 타겟 위치 계산 (마우스 화면 좌표 기준으로 월드 좌표를 얻음)
	FVector TargetWorldPos = GetWorld()->GetMainCamera()->ScreenMousePosToWorldPosWithOutPos(ZDis);

	// 방향 벡터 계산
	FVector Direction = (TargetWorldPos - CurrentPos).NormalizeReturn();

	// Z축은 고정(2D 평면에서의 회전 계산)
	FVector Forward = FVector::FORWARD; // 기본적으로 (1, 0, 0)
	FVector Up = FVector::UP;           // Z축 방향 (0, 0, 1)

	// 각도 계산 (내적 사용)
	float CosTheta = FVector::Dot(Forward, Direction);
	float AngleRad = CosTheta * UEngineMath::D2R;

	// 회전 축 계산 (외적 사용)
	FVector RotationAxis = FVector::Cross(Forward, Direction).NormalizeReturn();

	// 로컬 좌표에서 Z축 고정이므로 Z만 처리
	float ZRotation = AngleRad * UEngineMath::R2D;
	if (RotationAxis.Z < 0) // 방향에 따라 각도를 반전
	{
		ZRotation = -ZRotation;
	}

	// ArmRenderer 회전값 설정
	ArmRenderer->SetRotation(FVector(0.0f, 0.0f, ZRotation));

	if(bIsGrabbing == false)
		GrabLaunchToPosition(GetWorld()->GetMainCamera()->ScreenMousePosToWorldPosWithOutPos(ZDis));

	bIsGrabbing = true;

	float WalkVelocity = 100.0f;

	if (UEngineInput::IsPress('A'))
	{
		bIsRight = false;
		PlayerRenderer->ChangeAnimation("Walking");
		AddRelativeLocation(FVector{ -WalkVelocity * _DeltaTime, 0.0f, 0.0f });
	}
	else if (UEngineInput::IsPress('D'))
	{
		bIsRight = true;
		PlayerRenderer->ChangeAnimation("Walking");
		AddRelativeLocation(FVector{ WalkVelocity * _DeltaTime, 0.0f, 0.0f });
	}
	if (UEngineInput::IsFree(VK_LBUTTON))
	{
		ArmRenderer->SetRelativeLocation(PlayerRenderer->GetRelativeLocation());
		ArmRenderer->AddRelativeLocation({ 0.0f, 0.0f, -1.0f });
		bIsGrabbing = false;

		FSM.ChangeState(PlayerState::Idle);
		return;
	}
}

void APlayer::Grab_Grabbing(float _DeltaTime)
{

}
