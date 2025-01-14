#pragma once
#include <EngineCore/GameMode.h>

class AMapMakerMode : public AGameMode
{
public:
	AMapMakerMode();
	~AMapMakerMode();

	AMapMakerMode(const AMapMakerMode& _Other) = delete;
	AMapMakerMode(AMapMakerMode&& _Other) noexcept = delete;
	AMapMakerMode& operator=(const AMapMakerMode& _Other) = delete;
	AMapMakerMode& operator=(AMapMakerMode&& _Other) noexcept = delete;

	void Tick(float _DeltaTime);

protected:
	// void LevelChangeStart() override;

private:
	std::shared_ptr<class UTileMapWindow> TileMapWindow;
	std::shared_ptr<class USpriteRenderer> PivotSpriteRenderer;
	std::shared_ptr<class UTileMapRenderer> TileMapRenderer;
};
