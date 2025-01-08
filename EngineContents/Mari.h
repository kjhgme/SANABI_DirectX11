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

protected:

private:
	std::shared_ptr<class USpriteRenderer> MariRenderer;
	std::shared_ptr<class USpriteRenderer> MufinRenderer;
	std::queue<std::string> AnimQueue;
};

