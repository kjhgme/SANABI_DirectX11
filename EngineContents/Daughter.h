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

protected:

private:

};

