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

	void MakeTextBubble(std::string_view _Text, float _Size = 40.0f);
	void ClearTextBubble();

protected:

private:
	std::shared_ptr<class ATextBubble> DaughterText;

};

