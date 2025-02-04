#pragma once
#include <EngineCore/Actor.h>

class ABossFloatingBomb : public AActor
{
public:
	ABossFloatingBomb();
	~ABossFloatingBomb();

	ABossFloatingBomb(const ABossFloatingBomb& _Other) = delete;
	ABossFloatingBomb(ABossFloatingBomb&& _Other) noexcept = delete;
	ABossFloatingBomb& operator=(const ABossFloatingBomb& _Other) = delete;
	ABossFloatingBomb& operator=(ABossFloatingBomb&& _Other) noexcept = delete;

	void InitAnimation();

	FVector GetVelocity() const { return Velocity; }
	void SetVelocity(const FVector& NewVelocity) { Velocity = NewVelocity; }

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	std::shared_ptr<class USpriteRenderer> FloatingBombRenderer;
	std::shared_ptr<class UCollision> FloatingBombCollision;

	FVector Velocity = FVector(0.0f, 0.0f, 0.0f);
};

