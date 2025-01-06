#pragma once
#include <EngineCore/Actor.h>

class ABossBackGround : public AActor
{
public:
	ABossBackGround();
	~ABossBackGround();

	ABossBackGround(const ABossBackGround& _Other) = delete;
	ABossBackGround(ABossBackGround&& _Other) noexcept = delete;
	ABossBackGround& operator=(const ABossBackGround& _Other) = delete;
	ABossBackGround& operator=(ABossBackGround&& _Other) noexcept = delete;

	std::shared_ptr<class USpriteRenderer> GetBG_Boss_Sky_Renderer()
	{
		return BG_Sky_Renderer;
	}

	std::shared_ptr<class USpriteRenderer> GetBG_Boss_Cloud1_Renderer()
	{
		return BG_Cloud1_Renderer;
	}


	std::shared_ptr<class USpriteRenderer> GetBG_Boss_Cloud2_Renderer()
	{
		return BG_Cloud2_Renderer;
	}


	std::shared_ptr<class USpriteRenderer> GetBG_Boss_Building1_Renderer()
	{
		return BG_Building1_Renderer;
	}

	std::shared_ptr<class USpriteRenderer> GetBG_Boss_Building2_Renderer()
	{
		return BG_Building2_Renderer;
	}

protected:

private:
	std::shared_ptr<class USpriteRenderer> BG_Sky_Renderer;
	std::shared_ptr<class USpriteRenderer> BG_Cloud1_Renderer;
	std::shared_ptr<class USpriteRenderer> BG_Cloud2_Renderer;
	std::shared_ptr<class USpriteRenderer> BG_Building1_Renderer;
	std::shared_ptr<class USpriteRenderer> BG_Building2_Renderer;

	std::shared_ptr<class ACameraActor> Camera;
};

