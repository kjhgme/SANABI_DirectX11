#pragma once
#include <EngineBase/FSMStateManager.h>
#include <EngineCore/Actor.h>
#include <EngineCore/Pawn.h>

enum class PlayerState
{
	Idle,
	Walking,
	RunStart,
	Running,
	RunStop,
	Jumping,
	FallStart,
	Falling,
	Landing,
	Land2Run,
	Death,
	Damaged,
	Grab_Grabbing,
	Grab_Bomb,
};

class APlayer : public APawn
{
public:
	APlayer();
	~APlayer();

	APlayer(const APlayer& _Other) = delete;
	APlayer(APlayer&& _Other) noexcept = delete;
	APlayer& operator=(const APlayer& _Other) = delete;
	APlayer& operator=(APlayer&& _Other) noexcept = delete;

	// GetFunction
	std::shared_ptr<class USpriteRenderer> GetPlayerRenderer()
	{
		return PlayerRenderer;
	}

	bool GetSceneMode()
	{
		return SceneMode;
	}

	std::shared_ptr<class USpriteRenderer> GetGrabRenderer()
	{
		return GrabRenderer;
	}

	std::shared_ptr<class UCollision> GetGrabCollision()
	{
		return GrabCollision;
	}

	int GetHp() const
	{
		return HP;
	}

	// SetFunction
	void SetSceneMode(bool _Mode);

	void SetAnimation(std::string_view _Anim);
	
	void SetGrabbedPos(const FVector& _Pos);

	// Function
	void CheckRightDir();

	void MakeTextBubble(std::string_view _Text, float _Y = -2.0f, float _Size = 20.0f);
	void ClearTextBubble();

	void GrabLaunchToPosition(const FVector& _TargetPos);

	void FadeIn()
	{
		bIsFadeIn = true;
	}

	void FadeOut()
	{
		bIsFadeIn = false;
	}

	void TakeDamage();

	// PlayerFunction
	void ApplyGravity(float _DeltaTime);
	void Heal();

	// InitFunction
	void InitPlayerAnimation();
	void InitPlayerState();

	// StateFunction
	void Idle(float _DeltaTime);
	void Walking(float _DeltaTime);
	void RunStart(float _DeltaTime);
	void Running(float _DeltaTime);
	void RunStop(float _DeltaTime);
	void Jumping(float _DeltaTime);
	void FallStart(float _DeltaTime);
	void Falling(float _DeltaTime);
	void Landing(float _DeltaTime);
	void Land2Run(float _DeltaTime);
	void Death(float _DeltaTime);
	void Damaged(float _DeltaTime);
	void Grab_Flying(float _DeltaTime);
	void Grab_Grabbing(float _DeltaTime);
	void Grab_Bomb(float _DeltaTime);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	std::shared_ptr<class USpriteRenderer> PlayerRenderer;
	std::shared_ptr<class USpriteRenderer> ArmRenderer;
	std::shared_ptr<class USpriteRenderer> GrabRenderer;
	std::shared_ptr<class USpriteRenderer> AimRenderer;
	std::shared_ptr<class USpriteRenderer> HpRenderer;
	std::shared_ptr<class USpriteRenderer> FadeRenderer;

	std::shared_ptr<class UCollision> Collision;
	std::shared_ptr<class UCollision> GrabCollision;

	std::shared_ptr<class ACameraActor> PlayerCamera;
	std::shared_ptr<class ATextBubble> PlayerText;

	std::shared_ptr<class UTimeEventComponent> TimeEventComponent;

	bool SceneMode = true;
	bool bIsRight = true;
	bool bCanJump = true; 
	bool bHasSpawnedVfx = false;
	bool bIsGrabbing = false;

	float Gravity = -98.0f * 2.0f;
	float GravityVelocity = 0.0f;

	float MoveVelocity = 300.0f;
	float JumpVelocity = 3.0f;
	const float MaxFallSpeed = -1000.0f;

	// FADE
	float FadeValue = 1.0f;
	bool bIsFadeIn = true;

	// HP
	int HP = 4;
	bool bIsInfinity = false;
	float InfinityTime = 3.0f;
	float HealTime = 0.0f;

	// Grab
	FVector GrabbedPos;
	FVector AimPos{};
	float AimRotZ = 0.0f;

	// PendulumMove
	float SwingVelocity = 0.0f;
	float SwingAngle = 0.0f;

	std::shared_ptr<class AChain>Chain;

	UFSMStateManager FSM;
};

