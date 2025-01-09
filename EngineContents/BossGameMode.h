#pragma once
#include <EngineCore/GameMode.h>

class ABossGameMode : public AGameMode
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

	void InitScenes();

protected:

private:
	std::shared_ptr<class APlayer> Player;
	std::shared_ptr<class AMari> Mari;
	std::vector<std::shared_ptr<class ABossPlatform>> Platforms;
	std::shared_ptr<class ABossBackGround> BackGround;
	std::shared_ptr<class ACameraActor> MainCamera;

	std::vector<std::function<void()>> Scenes;

	float4 LastPlayerPosition;

	int SceneTakeNum = 0;
	bool bPlayNextAnimation = false;
};

