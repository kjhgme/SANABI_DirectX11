#pragma once
#include <EngineCore/Actor.h>

class ATextBubble : public AActor
{
public:
	ENGINEAPI ATextBubble();
	ENGINEAPI ~ATextBubble();

	ATextBubble(const ATextBubble& _Other) = delete;
	ATextBubble(ATextBubble&& _Other) noexcept = delete;
	ATextBubble& operator=(const ATextBubble& _Other) = delete;
	ATextBubble& operator=(ATextBubble&& _Other) noexcept = delete;

	void SetText(std::string_view _Text, float _Size);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	std::shared_ptr<class USpriteRenderer> BubbleRenderer;
	std::shared_ptr<class USpriteRenderer> BubbleTailRenderer;
	std::shared_ptr<class USpriteRenderer> BubbleMarkerRenderer;
	std::shared_ptr<class UFontRenderer> TextRenderer;

};

