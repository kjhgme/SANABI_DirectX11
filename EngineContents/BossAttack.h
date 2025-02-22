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

	void InitBossAttackAnimation();

	void SetAttack(std::string_view _Anim);

	std::shared_ptr<class USpriteRenderer> GetBossAttackRenderer()
	{
		return BossAttackRenderer;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	std::shared_ptr<class USpriteRenderer> BossAttackRenderer;
	std::shared_ptr<class UCollision> BossAttackCollision;
};

