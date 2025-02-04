#pragma once
#include <EngineCore/Actor.h>

class ABossPlatform : public AActor
{
public:
	ABossPlatform();
	~ABossPlatform();

	ABossPlatform(const ABossPlatform& _Other) = delete;
	ABossPlatform(ABossPlatform&& _Other) noexcept = delete;
	ABossPlatform& operator=(const ABossPlatform& _Other) = delete;
	ABossPlatform& operator=(ABossPlatform&& _Other) noexcept = delete;

	void GoToPlace(FVector _Pos);

	void TakeDamage();

	void InitAnimation();

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	std::shared_ptr<class USpriteRenderer> PlatformBoxRenderer;
	std::shared_ptr<class USpriteRenderer> PlatformBoosterRenderer;
	std::shared_ptr<class UTimeEventComponent> TimeEventComponent;
	std::shared_ptr<class UCollision> PlatformCollision;
	std::shared_ptr<class UCollision> WallCollision;

	int HP = 4;
	bool bIsInfinity = false;
};

