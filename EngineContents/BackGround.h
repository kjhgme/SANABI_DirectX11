#pragma once
#include <EngineCore/Actor.h>

class ABackGround : public AActor
{
public:
	ABackGround();
	~ABackGround();

	ABackGround(const ABackGround& _Other) = delete;
	ABackGround(ABackGround&& _Other) noexcept = delete;
	ABackGround& operator=(const ABackGround& _Other) = delete;
	ABackGround& operator=(ABackGround&& _Other) noexcept = delete;

protected:

private:
	std::shared_ptr<class USpriteRenderer> BackGroundRenderer;

};

