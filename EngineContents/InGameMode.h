#pragma once
#include <EngineCore/Actor.h>

class AInGameMode : public AActor
{
public:
	AInGameMode();
	~AInGameMode();

	AInGameMode(const AInGameMode& _Other) = delete;
	AInGameMode(AInGameMode&& _Other) noexcept = delete;
	AInGameMode& operator=(const AInGameMode& _Other) = delete;
	AInGameMode& operator=(AInGameMode&& _Other) noexcept = delete;

	void BeginPlay() override;

	void Tick(float _DeltaTime) override;

protected:

private:
	std::shared_ptr<class APlayer> Player;
	std::shared_ptr<class ADaughter> Daughter;
	std::shared_ptr<class ABackGround> BackGround;
	std::shared_ptr<class ACameraActor> MainCamera;
	std::shared_ptr<class ACameraActor> TestCamera;
};

