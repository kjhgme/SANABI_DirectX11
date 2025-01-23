#include "PreCompile.h"
#include "Player.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/Collision.h>
#include <EngineCore/CameraActor.h>
#include "PlayerVfx.h"

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
	Gravity = 0.0f;
	GravityVelocity = 0.0f;
	PlayerRenderer->ChangeAnimation("Death");
	ArmRenderer->ChangeAnimation("SNB_Arm_NoImage");
	HpRenderer->ChangeAnimation("HP4_NoImage");
}

void APlayer::Damaged(float _DeltaTime)
{
	PlayerRenderer->ChangeAnimation("Damaged");
	ArmRenderer->ChangeAnimation("SNB_Arm_Damaged");

	if (true == PlayerRenderer->IsCurAnimationEnd())
	{
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

	float ZDis = GetActorLocation().Z - GetWorld()->GetMainCamera()->GetActorLocation().Z;

	if (bIsGrabbing == false)
	{

		FVector CurrentPos = ArmRenderer->GetWorldLocation();
		FVector TargetWorldPos = AimPos;

		FVector CrossResult = FVector::Cross(FVector(0, 1, 0), TargetWorldPos - CurrentPos);
		CrossResult.Normalize();

		AimRotZ = FVector::GetVectorAngleDeg(TargetWorldPos - CurrentPos, FVector(0, 1, 0)) * CrossResult.Z;

		GrabLaunchToPosition(TargetWorldPos);

		bIsGrabbing = true;
	}

	GrabRenderer->SetRotation({ 0.0f, 0.0f, AimRotZ });

	// UEngineDebug::OutPutString(std::to_string(AimRotZ));

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
