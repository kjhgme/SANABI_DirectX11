#pragma once
#include <EngineCore/Actor.h>

class ABoss : public AActor
{
public:
	ABoss();
	~ABoss();

	ABoss(const ABoss& _Other) = delete;
	ABoss(ABoss&& _Other) noexcept = delete;
	ABoss& operator=(const ABoss& _Other) = delete;
	ABoss& operator=(ABoss&& _Other) noexcept = delete;

	int State = 0;

	void StareAtPlayer();

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	std::shared_ptr<class USpriteRenderer> BossRenderer;
	std::shared_ptr<class USpriteRenderer> BossWingRenderer;
	std::shared_ptr<class UTimeEventComponent> TimeEventComponent;

	void InitBossAnimation();

};

