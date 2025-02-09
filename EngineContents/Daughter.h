#pragma once
#include <EngineCore/Actor.h>

class ADaughter : public AActor
{
public:
	ADaughter();
	~ADaughter();

	ADaughter(const ADaughter& _Other) = delete;
	ADaughter(ADaughter&& _Other) noexcept = delete;
	ADaughter& operator=(const ADaughter& _Other) = delete;
	ADaughter& operator=(ADaughter&& _Other) noexcept = delete;

	void MakeTextBubble(std::string_view _Text, float _X = 0.0f, float _Y = -2.0f, float _BoxSize = 40.0f, float _TextSize = 24.0f, UColor _Color = UColor::BLACK);
	void ClearTextBubble();

protected:

private:
	std::shared_ptr<class ATextBubble> DaughterText;

};

