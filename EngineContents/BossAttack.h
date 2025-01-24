#pragma once
#include <EngineCore/Actor.h>

class ABossAttack : public AActor
{
public:
	ABossAttack();
	~ABossAttack();

	ABossAttack(const ABossAttack& _Other) = delete;
	ABossAttack(ABossAttack&& _Other) noexcept = delete;
	ABossAttack& operator=(const ABossAttack& _Other) = delete;
	ABossAttack& operator=(ABossAttack&& _Other) noexcept = delete;

protected:

private:

};

