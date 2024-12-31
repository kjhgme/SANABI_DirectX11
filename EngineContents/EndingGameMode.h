#pragma once
#include <EngineCore/Actor.h>

class AEndingGameMode : public AActor
{
public:
	AEndingGameMode();
	~AEndingGameMode();

	AEndingGameMode(const AEndingGameMode& _Other) = delete;
	AEndingGameMode(AEndingGameMode&& _Other) noexcept = delete;
	AEndingGameMode& operator=(const AEndingGameMode& _Other) = delete;
	AEndingGameMode& operator=(AEndingGameMode&& _Other) noexcept = delete;

	void Tick(float _DeltaTime) override;

protected:

private:
	std::shared_ptr<class AEndingPlayer> Player;
	std::shared_ptr<class ABackGround> BackGround;
};

