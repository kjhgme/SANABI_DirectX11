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
#include "Chain.h"

APlayer::APlayer()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	PlayerRenderer = CreateDefaultSubObject<USpriteRenderer>();
	ArmRenderer = CreateDefaultSubObject<USpriteRenderer>();
	GrabRenderer = CreateDefaultSubObject<USpriteRenderer>();
	HpRenderer = CreateDefaultSubObject<USpriteRenderer>(); 
	FadeRenderer = CreateDefaultSubObject<USpriteRenderer>();

	InitPlayerAnimation(); 
	InitPlayerState();

	PlayerRenderer->ChangeAnimation("Idle");
	ArmRenderer->ChangeAnimation("ArmIdle");
	GrabRenderer->ChangeAnimation("Grab_NoImage");
	HpRenderer->ChangeAnimation("HP4_NoImage");
	FadeRenderer->SetSprite("FADE", 0);

	PlayerRenderer->SetupAttachment(RootComponent);
	ArmRenderer->SetupAttachment(RootComponent);
	GrabRenderer->SetupAttachment(RootComponent);
	HpRenderer->SetupAttachment(RootComponent);
	FadeRenderer->SetupAttachment(RootComponent);

	PlayerRenderer->AddRelativeLocation({ 0.0f, 0.0f, static_cast<float>(ERenderOrder::PLAYER) });
	ArmRenderer->AddRelativeLocation({ 0.0f, 0.0f, static_cast<float>(ERenderOrder::ARM) });
	GrabRenderer->AddRelativeLocation({ 0.0f, 0.0f, static_cast<float>(ERenderOrder::ARM) - 1 });
	HpRenderer->AddRelativeLocation({ -30.0f, 40.0f, static_cast<float>(ERenderOrder::UI) + 1 });
	FadeRenderer->AddRelativeLocation({ 0.0f, -720.0f, static_cast<float>(ERenderOrder::UI) + 2 });

	PlayerCamera = GetWorld()->GetMainCamera();

	FSM.ChangeState(PlayerState::Idle);

	AimRenderer = CreateDefaultSubObject<USpriteRenderer>();
	AimRenderer->SetSprite("Aim", 0);
	AimRenderer->SetAutoScaleRatio(1.0f);

	TimeEventComponent = CreateDefaultSubObject<UTimeEventComponent>();

	FadeValue = 0.0f;
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

		if (_Other->GetCollisionProfileName() == "BOSS")
		{
			// Grabbing ÇØÁ¦
			if (nullptr != Chain)
			{
				Chain->Destroy();
				Chain = nullptr;
			}
			GrabRenderer->ChangeAnimation("Grab_NoImage");

 			this->FSM.ChangeState(PlayerState::Damaged);
			return;
		}

		if (_Other->GetCollisionProfileName() == "BOSSATTACK")
		{
			this->FSM.ChangeState(PlayerState::Damaged);
			return;
		}
	});

	Collision->SetCollisionEnd([this](UCollision* _This, UCollision* _Other)
	{
		// UEngineDebug::OutPutString("End : " + _Other->GetCollisionProfileName());
	});

	// GrabCollision
	GrabCollision = CreateDefaultSubObject<UCollision>();
	GrabCollision->SetupAttachment(GrabRenderer);
	GrabCollision->SetCollisionProfileName("Grab");
	GrabCollision->AddRelativeLocation({ 0.0f, 0.8f, 0.0f});
	GrabCollision->SetScale3D({ 0.3f, 0.3f });

	GrabCollision->SetCollisionEnter([this](UCollision* _This, UCollision* _Other)
	{
		if ("SNB_GRAB_FLYING" == this->GetGrabRenderer().get()->GetCurSpriteName())
		{
			FVector GrabPos = this->GetGrabRenderer()->GetWorldLocation();
			this->SetGrabbedPos(GrabPos);
			this->FSM.ChangeState(PlayerState::Grab_Grabbing);
			return;
		}
	});

	GrabCollision->SetCollisionEnd([this](UCollision* _This, UCollision* _Other)
	{

	});
}

void APlayer::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	if (bIsFadeIn == true)
	{
		FadeValue -= _DeltaTime * 0.2f;
	}
	else {
		FadeValue += _DeltaTime * 0.2f;
	}
	FadeValue = UEngineMath::Clamp(FadeValue, 0.0f, 1.0f);
	FadeRenderer->SetAlpha(FadeValue);

	float ZDis = GetActorLocation().Z - PlayerCamera->GetActorLocation().Z;
	AimPos = PlayerCamera->ScreenMousePosToWorldPosPerspective(ZDis);
	AimPos += {PlayerCamera->GetActorLocation().X, PlayerCamera->GetActorLocation().Y, 0.0f };
	AimPos.Y -= 30.0f;
	AimRenderer->SetWorldLocation(AimPos);
		
	if (UEngineInput::IsDown('G'))
	{
		FSM.ChangeState(PlayerState::Death);
		return;
	}
	if (UEngineInput::IsDown(VK_F1))
	{
		FSM.ChangeState(PlayerState::Damaged);
		return;
	}
	if (UEngineInput::IsDown(VK_F2))
	{
		Heal();
	}

	if (false == SceneMode)
	{
		if (UEngineInput::IsDown(VK_LBUTTON))
		{
			ArmRenderer->ChangeAnimation("ArmShoot");
			GrabRenderer->ChangeAnimation("Grab_Flying");
			Grab_Flying(_DeltaTime);
		}

		FSM.Update(_DeltaTime);
		ApplyGravity(_DeltaTime);
		CheckRightDir();

		if (HealTime > 0.0f)
		{
			HealTime -= _DeltaTime;
			if (HealTime <= 0.0f)
			{
				Heal();
			}
		}

		AimRenderer->SetSprite("Aim", 0);
	}
	else if (true == SceneMode)
	{
		HpRenderer->ChangeAnimation("HP4_NoImage");
		AimRenderer->SetSprite("Aim", 1);
	}
}

void APlayer::SetSceneMode(bool _Mode)
{
	SceneMode = _Mode;

	if (true == SceneMode)
	{
		AimRenderer->ChangeAnimation("Aim_NoImage");
		GrabRenderer->ChangeAnimation("Grab_NoImage");
		HpRenderer->ChangeAnimation("Hp4_NoImage");
	}
	else
	{
		HpRenderer->ChangeAnimation("Hp4_4_Mini");
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

void APlayer::SetGrabbedPos(const FVector& _Pos)
{
	GrabbedPos = _Pos;
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

void APlayer::MakeTextBubble(std::string_view _Text, float _Y, float _Size)
{
	PlayerText = GetWorld()->SpawnActor<ATextBubble>();
	PlayerText->SetText(_Text, _Y, _Size);
	PlayerText->SetActorLocation(GetActorLocation() + FVector(0.0f, 5.0f, 0.0f));
}

void APlayer::ClearTextBubble()
{
	if (PlayerText != nullptr)
	{
		PlayerText->Destroy();
	}
}

void APlayer::GrabLaunchToPosition(const FVector& _TargetPos)
{
	FVector TargetPos = _TargetPos;
	FVector CurrentPos = PlayerRenderer->GetRelativeLocation();

	TimeEventComponent->AddUpdateEvent(0.1f, [this, TargetPos, CurrentPos](float DeltaTime, float CurTime)
	{
		auto Lerp = [](FVector A, FVector B, float Alpha)
		{
			return A * (1 - Alpha) + B * Alpha;
		};

		float Alpha = UEngineMath::Clamp(CurTime / 0.1f, 0.0f, 1.0f);
		FVector NewPosition = Lerp(CurrentPos, TargetPos, Alpha);

		this->GetGrabRenderer()->SetWorldLocation(NewPosition);
		this->GetGrabRenderer()->AddWorldLocation({ 0.0f, 30.0f, 0.0f });
	},
		false
	);

	TimeEventComponent->AddEndEvent(0.1f, [this]() {
		if (false == this->GetGrabCollision().get()->IsColliding())
		{
			bIsGrabbing = false;

			ArmRenderer->SetRelativeLocation(PlayerRenderer->GetRelativeLocation());
			ArmRenderer->AddRelativeLocation({ 0.0f, 0.0f, -1.0f });

			GrabRenderer->ChangeAnimation("Grab_NoImage");
			GrabRenderer->SetWorldLocation(PlayerRenderer->GetRelativeLocation());
		}
	},
		false
	);
}

void APlayer::TakeDamage()
{
	FSM.ChangeState(PlayerState::Damaged);
	return;
}

void APlayer::ApplyGravity(float _DeltaTime)
{
	if (HP != 0)
	{
		if (Collision->IsColliding())
		{
			GravityVelocity = 0.0f;
			Gravity = 0.0f;
		}
		else {
			Gravity = -98.0f * 2.0f;

			GravityVelocity += Gravity * _DeltaTime;
			GravityVelocity = UEngineMath::Clamp(GravityVelocity, MaxFallSpeed, 0.0f);
		}
	}	
	if (true == bIsGrabbing)
	{
		GravityVelocity -= Gravity * _DeltaTime;
	}

	this->AddActorLocation({ 0.0f, _DeltaTime * GravityVelocity, 0.0f });
}

void APlayer::Heal()
{
	HP = 4;

	HpRenderer->ChangeAnimation("HP4_4_Restore");

	TimeEventComponent->AddUpdateEvent(3.0f, [this](float _DeltaTime, float _CurTime) {
		if(true == HpRenderer->IsCurAnimationEnd())
			HpRenderer->ChangeAnimation("HP4_4_Idle");
	},
		false
	);

	TimeEventComponent->AddEndEvent(5.0f, [this]() {
		if(this->GetHp() == 4)
			HpRenderer->ChangeAnimation("HP4_4_Mini");
	},
		false
	);
}
