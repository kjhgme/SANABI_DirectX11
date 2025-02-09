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

	void SetText(std::string_view _Text, float _Y, float _X = 0.0f, float _BoxSize = 30.0f, float _TextSize = 20.0f);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	std::shared_ptr<class USpriteRenderer> BubbleLRenderer;
	std::shared_ptr<class USpriteRenderer> BubbleMRenderer;
	std::shared_ptr<class USpriteRenderer> BubbleRRenderer;
	std::shared_ptr<class USpriteRenderer> BubbleTailRenderer;
	std::shared_ptr<class USpriteRenderer> BubbleMarkerRenderer;
	std::shared_ptr<class UFontRenderer> TextRenderer;

};

