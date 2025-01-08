#pragma once
#include <EngineCore/GameMode.h>

class ATitleGameMode : public AGameMode
{
public:
	ATitleGameMode();
	~ATitleGameMode();

	ATitleGameMode(const ATitleGameMode& _Other) = delete;
	ATitleGameMode(ATitleGameMode&& _Other) noexcept = delete;
	ATitleGameMode& operator=(const ATitleGameMode& _Other) = delete;
	ATitleGameMode& operator=(ATitleGameMode&& _Other) noexcept = delete;

	void Tick(float _DeltaTime) override;

protected:

private:
	std::shared_ptr<class ATitleBG> TitleBG;
	std::shared_ptr<class ATitleLogo> TitleLogo;
};

