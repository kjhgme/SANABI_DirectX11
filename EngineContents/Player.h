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
	Jump,
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

	void PlayerInput(float _DeltaTime);

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
	void Jump(float _DeltaTime);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	std::shared_ptr<class USpriteRenderer> PlayerRenderer;
	std::shared_ptr<class USpriteRenderer> ArmRenderer;
	std::shared_ptr<class UCollision> Collision;

	std::shared_ptr<class ACameraActor> PlayerCamera;
	std::shared_ptr<class ATextBubble> PlayerText;

	bool bIsRight = true;
	bool SceneMode = true;

	float Gravity = -9.8f;
	float GravityVelocity = 0.0f;

	float MoveVelocity = 0.0f;
	const float MaxFallSpeed = -5000.0f;

	UFSMStateManager FSM;

	void SetArmPosition();
};

