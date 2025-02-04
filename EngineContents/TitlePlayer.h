#pragma once
#include <EngineCore/Pawn.h>

class ATitlePlayer : public APawn
{
public:
	ATitlePlayer();
	~ATitlePlayer();

	ATitlePlayer(const ATitlePlayer& _Other) = delete;
	ATitlePlayer(ATitlePlayer&& _Other) noexcept = delete;
	ATitlePlayer& operator=(const ATitlePlayer& _Other) = delete;
	ATitlePlayer& operator=(ATitlePlayer&& _Other) noexcept = delete;

protected:

private:

};

