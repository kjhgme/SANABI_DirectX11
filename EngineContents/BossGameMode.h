#pragma once
#include <EngineCore/GameMode.h>

#include <EnginePlatform/EngineSound.h>

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

	std::shared_ptr<class AMari> GetMari()
	{
		return Mari;
	}

	class APlayer* AGetPlayer()
	{
		return Player;
	}

protected:
	void LevelChangeStart() override;

private:
	class APlayer* Player;
	std::shared_ptr<class AMari> Mari;
	std::shared_ptr<class ABoss> Boss;
	std::vector<std::shared_ptr<class ABossPlatform>> Platforms;
	std::shared_ptr<class ABossBackGround> BackGround;
	std::shared_ptr<class ACameraActor> MainCamera;

	std::vector<std::function<void()>> Scenes;

	std::shared_ptr<class UTimeEventComponent> TimeEventComponent;

	int SceneTakeNum = 0;
	bool bPlayNextAnimation = false;

	USoundPlayer SoundPlayer;
};

