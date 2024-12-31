#pragma once
#include <EngineCore/Actor.h>

class ATextBubble : public AActor
{
public:
	ATextBubble();
	~ATextBubble();

	ATextBubble(const ATextBubble& _Other) = delete;
	ATextBubble(ATextBubble&& _Other) noexcept = delete;
	ATextBubble& operator=(const ATextBubble& _Other) = delete;
	ATextBubble& operator=(ATextBubble&& _Other) noexcept = delete;

protected:

private:

};

