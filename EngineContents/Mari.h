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

	void MakeTextBubble(std::string_view _Text, float _X = -2.0f, float _Y = -2.0f, float _Size = 24.0f);
	void ClearTextBubble();

protected:
	void Tick(float _DeltaTime) override;

private:
	std::shared_ptr<class USpriteRenderer> MariRenderer;
	std::shared_ptr<class USpriteRenderer> MufinRenderer;

	std::shared_ptr<class ATextBubble> MariText;

	std::queue<std::string> AnimQueue;
};

