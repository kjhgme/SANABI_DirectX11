#pragma once
#include <EngineCore/Actor.h>
#include <queue>

class AMari : public AActor
{
public:
	AMari();
	~AMari();

	AMari(const AMari& _Other) = delete;
	AMari(AMari&& _Other) noexcept = delete;
	AMari& operator=(const AMari& _Other) = delete;
	AMari& operator=(AMari&& _Other) noexcept = delete;

	void InitMariAnimation();

	void SetAnimation(std::string_view _Anim);
	void ChangeToNextAnim();

	void MufinOn();
	void MufinOff();

	void MakeTextBubble(std::string_view _Text, float _BoxSize = 40.0f, float _TextSize = 24.0f, float _X = -2.0f, float _Y = -2.0f, UColor _Color = UColor::BLACK);
	void ClearTextBubble();

protected:
	void Tick(float _DeltaTime) override;

private:
	std::shared_ptr<class USpriteRenderer> MariRenderer;
	std::shared_ptr<class USpriteRenderer> MufinRenderer;

	std::shared_ptr<class ATextBubble> MariText;

	std::queue<std::string> AnimQueue;
};

