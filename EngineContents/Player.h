#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/Pawn.h>

class APlayer : public APawn
{
public:
	APlayer();
	~APlayer();

	APlayer(const APlayer& _Other) = delete;
	APlayer(APlayer&& _Other) noexcept = delete;
	APlayer& operator=(const APlayer& _Other) = delete;
	APlayer& operator=(APlayer&& _Other) noexcept = delete;

	void InitPlayerAnimation();

	void PlayerMove(float _DeltaTime);

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

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	std::shared_ptr<class USpriteRenderer> PlayerRenderer;
	std::shared_ptr<class USpriteRenderer> ArmRenderer;
	std::shared_ptr<class UCollision> Collision;

	std::shared_ptr<class ACameraActor> PlayerCamera;
	std::shared_ptr<class ATextBubble> PlayerText;

	bool IsRight = true;
	bool IsIdle = true;
	bool IsWalking = true;
	bool IsRunning = false;
	bool IsJumping = false;

	bool SceneMode = true;

	float Gravity = -9.8f;
	float GravityVelocity = 0.0f;
	const float MaxFallSpeed = -5000.0f;

	void SetArmPosition();
};

