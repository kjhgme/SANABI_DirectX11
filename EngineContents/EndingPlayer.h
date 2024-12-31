#pragma once
#include <EngineCore/Actor.h>

class AEndingPlayer : public AActor
{
public:
	AEndingPlayer();
	~AEndingPlayer();

	AEndingPlayer(const AEndingPlayer& _Other) = delete;
	AEndingPlayer(AEndingPlayer&& _Other) noexcept = delete;
	AEndingPlayer& operator=(const AEndingPlayer& _Other) = delete;
	AEndingPlayer& operator=(AEndingPlayer&& _Other) noexcept = delete;

	void InitPlayerAnimation();
	void SetAnimation(std::shared_ptr<class USpriteRenderer> Renderer,
		std::string_view AnimationName,
		std::string_view TextureName, 
		bool Loop = true,
		float FrameRate = 0.12f,
		float AutoScaleRatio = 2.0f);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	std::shared_ptr<class USpriteRenderer> PlayerRenderer;

};

