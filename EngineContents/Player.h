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

	std::shared_ptr<class USpriteRenderer> GetPlayerRenderer()
	{
		return PlayerRenderer;
	}

	void SetAnimation(std::string_view _Anim);

	bool GetSceneMode()
	{
		return SceneMode;
	}

	void SetSceneMode(bool _Mode)
	{
		SceneMode = _Mode;
	}

	void AddPlayerRendererLocation(FVector _Loc);
	
	void CheckRightDir();

	// PlayerFunction
	void ApplyGravity(float _DeltaTime);

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

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	std::shared_ptr<class USpriteRenderer> PlayerRenderer;
	std::shared_ptr<class USpriteRenderer> ArmRenderer;
	std::shared_ptr<class USpriteRenderer> AimRenderer;
	std::shared_ptr<class UCollision> Collision;

	std::shared_ptr<class ACameraActor> PlayerCamera;
	std::shared_ptr<class ATextBubble> PlayerText;
	std::shared_ptr<class UFontRenderer> TextTest;

	bool SceneMode = true;
	bool bIsRight = true;
	bool bCanJump = true; 
	bool bHasSpawnedVfx = false;

	float Gravity = -98.0f;
	float GravityVelocity = 0.0f;

	float MoveVelocity = 300.0f;
	float JumpVelocity = 3.0f;
	const float MaxFallSpeed = -5000.0f;

	UFSMStateManager FSM;
};

