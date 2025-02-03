#include "PreCompile.h"
#include "BossAttack.h"

#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>

ABossAttack::ABossAttack()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	BossAttackRenderer = CreateDefaultSubObject<USpriteRenderer>();

	InitBossAttackAnimation();
	BossAttackRenderer->ChangeAnimation("BossAttack_NoImage");

	BossAttackRenderer->SetupAttachment(RootComponent);
}

ABossAttack::~ABossAttack()
{
}

void ABossAttack::InitBossAttackAnimation()
{
	BossAttackRenderer->CreateAnimation("BossAttack_NoImage", "BossAttack_NoImage");

	BossAttackRenderer->CreateAnimation("BossAttack_Bomb_Appear", "BossAttack_Bomb_Appear", false);
	BossAttackRenderer->CreateAnimation("BossAttack_Bomb_Explode", "BossAttack_Bomb_Explode", false);
	BossAttackRenderer->CreateAnimation("BossAttack_Bomb_Falling", "BossAttack_Bomb_Falling", true);
	BossAttackRenderer->CreateAnimation("BossAttack_ClusterBomb_Appear", "BossAttack_ClusterBomb_Appear", false);
	BossAttackRenderer->CreateAnimation("BossAttack_ClusterBomb_Explode", "BossAttack_ClusterBomb_Explode", false);
	BossAttackRenderer->CreateAnimation("BossAttack_ClusterBomblet_Explode", "BossAttack_ClusterBomblet_Explode", false);
	BossAttackRenderer->CreateAnimation("BossAttack_ClusterBomblet_Idle", "BossAttack_ClusterBomblet_Idle", true);
	BossAttackRenderer->CreateAnimation("BossAttack_ShootExplode", "BossAttack_ShootExplode", false, 0.15f);
}

void ABossAttack::SetAnimation(std::string_view _Anim)
{
	BossAttackRenderer->ChangeAnimation(_Anim);
}

void ABossAttack::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	if (BossAttackRenderer->IsCurAnimationEnd())
	{
		Destroy();
	}
}