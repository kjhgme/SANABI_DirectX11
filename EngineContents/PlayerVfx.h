#pragma once
#include <EngineCore/Actor.h>

class APlayerVfx : public AActor
{
public:
	APlayerVfx();

	~APlayerVfx();

	APlayerVfx(const APlayerVfx& _Other) = delete;
	APlayerVfx(APlayerVfx&& _Other) noexcept = delete;
	APlayerVfx& operator=(const APlayerVfx& _Other) = delete;
	APlayerVfx& operator=(APlayerVfx&& _Other) noexcept = delete;

	void Tick(float _DeltaTime) override;

	void InitVfx(std::string_view _AnimName);
	void InitPos(FVector _Pos);

protected:

private:
	std::shared_ptr<class USpriteRenderer> VfxRenderer;
};

