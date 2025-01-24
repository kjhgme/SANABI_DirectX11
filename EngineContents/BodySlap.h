#pragma once
#include "BossAttack.h"

class ABodySlap : public ABossAttack
{
public:
	ABodySlap();
	~ABodySlap();

	ABodySlap(const ABodySlap& _Other) = delete;
	ABodySlap(ABodySlap&& _Other) noexcept = delete;
	ABodySlap& operator=(const ABodySlap& _Other) = delete;
	ABodySlap& operator=(ABodySlap&& _Other) noexcept = delete;

	void SetHeadRight(bool _IsRight)
	{
		bIsRight = _IsRight;
	}

protected:
	void Tick(float _DeltaTime) override;

private:
	std::shared_ptr<class USpriteRenderer> AlertRenderer;

	bool bIsRight;
};

