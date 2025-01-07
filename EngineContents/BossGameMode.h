#pragma once
#include <EngineCore/Actor.h>

class ABossGameMode : public AActor
{
public:
	ABossGameMode();
	~ABossGameMode();

	ABossGameMode(const ABossGameMode& _Other) = delete;
	ABossGameMode(ABossGameMode&& _Other) noexcept = delete;
	ABossGameMode& operator=(const ABossGameMode& _Other) = delete;
	ABossGameMode& operator=(ABossGameMode&& _Other) noexcept = delete;

	void BeginPlay() override;

	void Tick(float _DeltaTime) override;

	void Scene();

protected:

private:
	std::shared_ptr<class APlayer> Player;
	std::shared_ptr<class ABossPlatform> Platforms;
	std::shared_ptr<class ABossBackGround> BackGround;
	std::shared_ptr<class ACameraActor> MainCamera;

	float4 LastPlayerPosition;
};

