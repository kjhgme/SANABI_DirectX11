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
	GrabRenderer = CreateDefaultSubObject<USpriteRenderer>();
	HpRenderer = CreateDefaultSubObject<USpriteRenderer>();

	InitPlayerAnimation(); 
	InitPlayerState();

	PlayerRenderer->ChangeAnimation("Idle");
	ArmRenderer->ChangeAnimation("ArmIdle");
	GrabRenderer->ChangeAnimation("Grab_NoImage");
	HpRenderer->ChangeAnimation("HP4_NoImage");

	PlayerRenderer->SetupAttachment(RootComponent);
	ArmRenderer->SetupAttachment(RootComponent);
	GrabRenderer->SetupAttachment(RootComponent);
	HpRenderer->SetupAttachment(RootComponent);

	PlayerRenderer->AddRelativeLocation({ 0.0f, 0.0f, static_cast<float>(ERenderOrder::PLAYER) });
	ArmRenderer->AddRelativeLocation({ 0.0f, 0.0f, static_cast<float>(ERenderOrder::ARM) });
	GrabRenderer->AddRelativeLocation({ 0.0f, 0.0f, static_cast<float>(ERenderOrder::ARM) - 1 });
	HpRenderer->AddRelativeLocation({ -30.0f, 40.0f, static_cast<float>(ERenderOrder::UI) + 1 });

	PlayerCamera = GetWorld()->GetMainCamera();

	FSM.ChangeState(PlayerState::Idle);

	AimRenderer = CreateDefaultSubObject<USpriteRenderer>();
	AimRenderer->SetSprite("Aim", 0);
	AimRenderer->SetAutoScaleRatio(1.0f);

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
		// UEngineDebug::OutPutString("Enter : " + _Other->GetCollisionProfileName());
	});

	Collision->SetCollisionEnd([this](UCollision* _This, UCollision* _Other)
	{
		// UEngineDebug::OutPutString("End : " + _Other->GetCollisionProfileName());
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

	float ZDis = GetActorLocation().Z - PlayerCamera->GetActorLocation().Z;
	AimPos = PlayerCamera->ScreenMousePosToWorldPosPerspective(ZDis) + GetActorLocation();
	AimPos.Y -= 30.0f;
	AimRenderer->SetRelativeLocation(AimPos);
	// UEngineDebug::OutPutString(AimPos.ToString());

	if (UEngineInput::IsDown(MK_LBUTTON))
	{
		// UEngineDebug::OutPutString(AimPos.ToString());
	}
	if (false == SceneMode)
	{
		FSM.Update(_DeltaTime);
		ApplyGravity(_DeltaTime);
		CheckRightDir();
		CheckHP();
		AimRenderer->SetSprite("Aim", 0);
	}
	else if (true == SceneMode)
	{
		HpRenderer->ChangeAnimation("HP4_NoImage");
		AimRenderer->SetSprite("Aim", 1);
	}
	if (UEngineInput::IsDown('G'))
	{
		FSM.ChangeState(PlayerState::Death);
	}
	if (UEngineInput::IsDown(VK_F1))
	{
		HP -= 1;
		FSM.ChangeState(PlayerState::Damaged);
	}
	if (UEngineInput::IsDown(VK_F2))
	{
		Heal();
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
	GrabRenderer->AddRelativeLocation(_Loc);
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
			HpRenderer->SetRotation({ 0.0f, 0.0f, 0.0f });
		}
		else
		{
			PlayerRenderer->SetRotation({ 0.0f, 180.0f, 0.0f });
			ArmRenderer->SetRotation({ 0.0f, 180.0f, 0.0f });
		}
	}
}

void APlayer::CheckHP()
{
	if (HP == 4)
	{
		HpRenderer->ChangeAnimation("HP4_4_Mini");
	}
	else if (HP == 3)
	{
		HpRenderer->ChangeAnimation("HP4_3_Idle");
	}
	else if (HP == 2)
	{
		HpRenderer->ChangeAnimation("HP4_2_Idle");
	}
	else if (HP == 1)
	{
		HpRenderer->ChangeAnimation("HP4_1_Idle");
	}
	else if (HP <= 0) {
		FSM.ChangeState(PlayerState::Death);
	}
	else if (HP == 5) {
		HpRenderer->ChangeAnimation("HP4_4_Restore");
	}
}

void APlayer::MakeTextBubble(std::string_view _Text, float _Size)
{
	PlayerText = GetWorld()->SpawnActor<ATextBubble>();
	PlayerText->SetText(_Text, _Size);
	PlayerText->SetActorLocation(GetActorLocation() + FVector(0.0f, 5.0f, 0.0f));
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

		this->GetGrabRenderer()->AddRelativeLocation(NewPosition);
	},
		false
	);
}

void APlayer::ApplyGravity(float _DeltaTime)
{
	if (HP != 0)
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
	}

	this->AddActorLocation({ 0.0f, _DeltaTime * GravityVelocity, 0.0f });
}

void APlayer::Heal()
{
	HP = 4;

	HpRenderer->ChangeAnimation("HP4_Restore");
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

			PlayerRenderer->CreateAnimation("Damaged", "SNB_Damaged", false);
			ArmRenderer->CreateAnimation("ArmDamaged", "SNB_Arm_Damaged", false);

			ArmRenderer->CreateAnimation("ArmShoot", "SNB_Arm_Shoot", false);
			ArmRenderer->CreateAnimation("ArmGrabbed", "SNB_Arm_Grabbed", false);
		}
		// Grab
		{
			GrabRenderer->CreateAnimation("Grab_NoImage", "SNB_Grab_NoImage", false);
			GrabRenderer->CreateAnimation("Grab_Flying", "SNB_Grab_Flying", false);
			GrabRenderer->CreateAnimation("Grab_Grabbing", "SNB_Grab_Grabbing", false);
			GrabRenderer->CreateAnimation("Grab_Grabed", "SNB_Grab_Grabed", false);
			GrabRenderer->CreateAnimation("Grab_Lower_Grabbed", "SNB_Grab_Lower_Grabbed", false);
			GrabRenderer->CreateAnimation("Grab_Lower_Grabbing", "SNB_Grab_Lower_Grabbing", false);
			GrabRenderer->CreateAnimation("Grab_Return", "SNB_Grab_Return", false);
			GrabRenderer->CreateAnimation("Grab_ReturnWithGrabbed", "SNB_Grab_ReturnWithGrabbed",false);
			GrabRenderer->CreateAnimation("Grab_ReturnWithoutGrabbed", "SNB_Grab_ReturnWithoutGrabbed", false);
		}
		// HP
		{
			HpRenderer->CreateAnimation("HP4_1_Damaged", "HP4_1_Damaged", false);
			HpRenderer->CreateAnimation("HP4_1_Idle", "HP4_1_Idle", false);
			HpRenderer->CreateAnimation("HP4_2_Damaged", "HP4_2_Damaged", false);
			HpRenderer->CreateAnimation("HP4_2_Disapear", "HP4_2_Disapear", false);
			HpRenderer->CreateAnimation("HP4_2_Idle", "HP4_2_Idle", false);
			HpRenderer->CreateAnimation("HP4_2_Mini", "HP4_2_Mini", false);
			HpRenderer->CreateAnimation("HP4_2_Restore", "HP4_2_Restore", false);
			HpRenderer->CreateAnimation("HP4_3_Damaged", "HP4_3_Damaged", false);
			HpRenderer->CreateAnimation("HP4_3_Disappear", "HP4_3_Disappear", false);
			HpRenderer->CreateAnimation("HP4_3_Idle", "HP4_3_Idle", false);
			HpRenderer->CreateAnimation("HP4_3_Mini", "HP4_3_Mini", false);
			HpRenderer->CreateAnimation("HP4_3_Restore", "HP4_3_Restore", false);
			HpRenderer->CreateAnimation("HP4_4_Disappear", "HP4_4_Disappear", false);
			HpRenderer->CreateAnimation("HP4_4_Idle", "HP4_4_Idle", false);
			HpRenderer->CreateAnimation("HP4_4_Mini", "HP4_4_Mini", false);
			HpRenderer->CreateAnimation("HP4_4_Restore", "HP4_4_Restore", false);
			HpRenderer->CreateAnimation("HP4_NoImage", "HP4_NoImage", false);
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
	FSM.CreateState(PlayerState::Damaged, std::bind(&APlayer::Damaged, this, std::placeholders::_1), [this]() {});
	FSM.CreateState(PlayerState::Grab_Flying, std::bind(&APlayer::Grab_Flying, this, std::placeholders::_1), [this]() {});
	FSM.CreateState(PlayerState::Grab_Grabbing, std::bind(&APlayer::Grab_Grabbing, this, std::placeholders::_1), [this]() {});
}
