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

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	std::shared_ptr<class USpriteRenderer> PlayerRenderer;

};

