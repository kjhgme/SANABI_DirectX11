#include "PreCompile.h"
#include "Player.h"

#include <EngineCore/TimeEventComponent.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/CameraActor.h>
#include <EngineCore/Collision.h>
#include "PlayerVfx.h"

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
			GrabRenderer->CreateAnimation("Grab_ReturnWithGrabbed", "SNB_Grab_ReturnWithGrabbed", false);
			GrabRenderer->CreateAnimation("Grab_ReturnWithoutGrabbed", "SNB_Grab_ReturnWithoutGrabbed", false);
		}
		// HP
		{
			HpRenderer->CreateAnimation("HP4_1_Damaged", "HP4_1_Damaged", false);
			HpRenderer->CreateAnimation("HP4_1_Idle", "HP4_1_Idle");
			HpRenderer->CreateAnimation("HP4_2_Damaged", "HP4_2_Damaged", false);
			HpRenderer->CreateAnimation("HP4_2_Disapear", "HP4_2_Disapear", false);
			HpRenderer->CreateAnimation("HP4_2_Idle", "HP4_2_Idle");
			HpRenderer->CreateAnimation("HP4_2_Mini", "HP4_2_Mini", false);
			HpRenderer->CreateAnimation("HP4_2_Restore", "HP4_2_Restore", false);
			HpRenderer->CreateAnimation("HP4_3_Damaged", "HP4_3_Damaged", false);
			HpRenderer->CreateAnimation("HP4_3_Disappear", "HP4_3_Disappear", false);
			HpRenderer->CreateAnimation("HP4_3_Idle", "HP4_3_Idle");
			HpRenderer->CreateAnimation("HP4_3_Mini", "HP4_3_Mini", false);
			HpRenderer->CreateAnimation("HP4_3_Restore", "HP4_3_Restore", false);
			HpRenderer->CreateAnimation("HP4_4_Disappear", "HP4_4_Disappear", false);
			HpRenderer->CreateAnimation("HP4_4_Idle", "HP4_4_Idle");
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
	FSM.CreateState(PlayerState::Idle, std::bind(&APlayer::Idle, this, std::placeholders::_1), [this]() {});
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
	if (true == UEngineInput::IsDown(VK_LBUTTON))
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
	if (true == UEngineInput::IsDown(VK_LBUTTON))
	{
		FSM.ChangeState(PlayerState::Grab_Flying);
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
	if (true == UEngineInput::IsDown(VK_LBUTTON))
	{
		FSM.ChangeState(PlayerState::Grab_Flying);
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
	if (true == UEngineInput::IsDown(VK_LBUTTON))
	{
		FSM.ChangeState(PlayerState::Grab_Flying);
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
	if (true == UEngineInput::IsDown(VK_LBUTTON))
	{
		FSM.ChangeState(PlayerState::Grab_Flying);
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
	if (true == UEngineInput::IsDown(VK_LBUTTON))
	{
		FSM.ChangeState(PlayerState::Grab_Flying);
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
	if (true == UEngineInput::IsDown(VK_LBUTTON))
	{
		FSM.ChangeState(PlayerState::Grab_Flying);
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
	if (true == UEngineInput::IsDown(VK_LBUTTON))
	{
		FSM.ChangeState(PlayerState::Grab_Flying);
		return;
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
	if (true == UEngineInput::IsDown(VK_LBUTTON))
	{
		FSM.ChangeState(PlayerState::Grab_Flying);
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
	if (true == UEngineInput::IsDown(VK_LBUTTON))
	{
		FSM.ChangeState(PlayerState::Grab_Flying);
		return;
	}
}

void APlayer::Death(float _DeltaTime)
{
	Gravity = 0.0f;
	GravityVelocity = 0.0f;
	PlayerRenderer->ChangeAnimation("Death");
	ArmRenderer->ChangeAnimation("SNB_Arm_NoImage");
	HpRenderer->ChangeAnimation("HP4_NoImage");
}

void APlayer::Damaged(float _DeltaTime)
{
	PlayerRenderer->ChangeAnimation("Damaged");
	ArmRenderer->ChangeAnimation("ArmDamaged");

	if (false == bIsInfinity)
	{
		if (HP == 3)
		{
			HpRenderer->ChangeAnimation("HP4_3_Damaged");
		}
		else if (HP == 2)
		{
			HpRenderer->ChangeAnimation("HP4_2_Damaged");
		}
		else if (HP == 1)
		{
			HpRenderer->ChangeAnimation("HP4_1_Damaged");
		}
		else if (HP <= 0) {
			FSM.ChangeState(PlayerState::Death);
		}

		HealTime = 10.0f;
		bIsInfinity = true;		
	}

	if (true == PlayerRenderer->IsCurAnimationEnd())
	{
		HpRenderer->ChangeAnimation("HP4_" + std::to_string(HP) + "_Idle");

		TimeEventComponent->AddEndEvent(2.0f, [this]()
		{
			bIsInfinity = false;
		},
			false
		);

		if (false == Collision->IsColliding())
		{
			FSM.ChangeState(PlayerState::FallStart);
			return;
		}
		else if (true == UEngineInput::IsPress('A') || true == UEngineInput::IsPress('D'))
		{
			FSM.ChangeState(PlayerState::RunStart);
			return;
		}
		else {
			FSM.ChangeState(PlayerState::Idle);
			return;
		}
	}
}

void APlayer::Grab_Flying(float _DeltaTime)
{	
	ArmRenderer->ChangeAnimation("ArmShoot");
	GrabRenderer->ChangeAnimation("Grab_Flying");

	if (bIsGrabbing == false)
	{
		float ZDis = GetActorLocation().Z - GetWorld()->GetMainCamera()->GetActorLocation().Z;

		FVector CurrentPos = PlayerRenderer->GetWorldLocation();
		FVector TargetWorldPos = AimRenderer->GetWorldLocation();
		CurrentPos.Z = TargetWorldPos.Z;

		FVector CrossResult = FVector::Cross(FVector(0, 1, 0), TargetWorldPos - CurrentPos);
		CrossResult.Normalize();

		AimRotZ = FVector::GetVectorAngleDeg(TargetWorldPos - CurrentPos, FVector(0, 1, 0)) * CrossResult.Z;

		GrabLaunchToPosition(TargetWorldPos - CurrentPos);

		bIsGrabbing = true;
	}

	GrabRenderer->SetRotation({ 0.0f, 0.0f, AimRotZ });
	
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

		GrabRenderer->SetWorldLocation(PlayerRenderer->GetWorldLocation());
		GrabRenderer->ChangeAnimation("Grab_NoImage");
		bIsGrabbing = false;

		FSM.ChangeState(PlayerState::Idle);
		return;
	}
}

void APlayer::Grab_Grabbing(float _DeltaTime)
{

}
