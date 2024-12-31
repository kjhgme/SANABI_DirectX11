#pragma once
#include <EngineCore/Actor.h>

class APlayer : public AActor
{
public:
	APlayer();
	~APlayer();

	APlayer(const APlayer& _Other) = delete;
	APlayer(APlayer&& _Other) noexcept = delete;
	APlayer& operator=(const APlayer& _Other) = delete;
	APlayer& operator=(APlayer&& _Other) noexcept = delete;

	void InitPlayerAnimation();
	void SetAnimation(std::shared_ptr<class USpriteRenderer> Renderer,
		std::string_view AnimationName,
		std::string_view TextureName,
		int StartFrame,
		int EndFrame,
		float FrameRate = 0.1f,
		float AutoScaleRatio = 2.0f);

	void PlayerMove(float _DeltaTime);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	std::shared_ptr<class USpriteRenderer> PlayerRenderer;
	std::shared_ptr<class USpriteRenderer> ArmRenderer;

	bool IsIdle = true;
	bool IsWalking = true;
	bool IsRunning = false;
	bool IsJumping = false;
};

