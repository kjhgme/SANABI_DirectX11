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

protected:
	void Tick(float _DeltaTime) override;

private:
	std::shared_ptr<class USpriteRenderer> BG_Sky_Renderer;
	std::shared_ptr<class USpriteRenderer> BG_Cloud1_Renderer;
	std::shared_ptr<class USpriteRenderer> BG_Cloud2_Renderer;
	std::shared_ptr<class USpriteRenderer> BG_Building1_Renderer;
	std::shared_ptr<class USpriteRenderer> BG_Building2_Renderer;

	std::shared_ptr<class USpriteRenderer> BG_Cloud1_Renderer2;
	std::shared_ptr<class USpriteRenderer> BG_Cloud2_Renderer2;
	std::shared_ptr<class USpriteRenderer> BG_Building1_Renderer2;
	std::shared_ptr<class USpriteRenderer> BG_Building2_Renderer2;
};

