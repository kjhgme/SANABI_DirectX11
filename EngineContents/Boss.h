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

	std::shared_ptr<class USpriteRenderer> GetBossAimRenderer()
	{
		return BossAimRenderer;
	}
	
	std::shared_ptr<class USpriteRenderer> GetMachineGunRenderer()
	{
		return BossMachineGunRenderer;
	}

	void StareAtPlayer();
	void StartBattle();

	// Attacks
	void ShootMachineGun();
	void ShootMissile();
	void SlapAttack();
	void DropBomb();

	int State = 0;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	std::shared_ptr<class UDefaultSceneComponent> Default;
	std::shared_ptr<class USpriteRenderer> BossRenderer;
	std::shared_ptr<class USpriteRenderer> BossWingRenderer;
	std::shared_ptr<class UCollision> BossCollision;

	// Attacks
	std::shared_ptr<class USpriteRenderer> BossAimRenderer;
	std::shared_ptr<class USpriteRenderer> BossMachineGunRenderer;
	std::shared_ptr<class USpriteRenderer> BossBomberRenderer;

	std::shared_ptr<class UTimeEventComponent> TimeEventComponent;

	void InitBossAnimation();

	bool bIsRight = true;
};

