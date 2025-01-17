#pragma once
#include <EngineCore/HUD.h>

class ABossGameHUD : public AHUD
{
public:
	ABossGameHUD();
	~ABossGameHUD();

	ABossGameHUD(const ABossGameHUD& _Other) = delete;
	ABossGameHUD(ABossGameHUD&& _Other) noexcept = delete;
	ABossGameHUD& operator=(const ABossGameHUD& _Other) = delete;
	ABossGameHUD& operator=(ABossGameHUD&& _Other) noexcept = delete;

	void BeginPlay();
	void Tick(float _DeltaTime);

protected:

private:
};

