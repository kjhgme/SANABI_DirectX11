#include "PreCompile.h"
#include "BossAttack.h"

#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/Collision.h>
#include "Player.h"
#include "BossPlatform.h"

ABossAttack::ABossAttack()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	BossAttackRenderer = CreateDefaultSubObject<USpriteRenderer>();

	InitBossAttackAnimation();
	BossAttackRenderer->ChangeAnimation("BossAttack_NoImage");
	BossAttackRenderer->SetupAttachment(RootComponent);

	BossAttackCollision = CreateDefaultSubObject<UCollision>();
	BossAttackCollision->SetupAttachment(RootComponent);
	BossAttackCollision->SetCollisionProfileName("BossAttack");
}

ABossAttack::~ABossAttack()
{
}

void ABossAttack::InitBossAttackAnimation()
{
	BossAttackRenderer->CreateAnimation("BossAttack_NoImage", "BossAttack_NoImage");

	BossAttackRenderer->CreateAnimation("BossAttack_Bomb_Appear", "BossAttack_Bomb_Appear", false, 0.15f);
	BossAttackRenderer->CreateAnimation("BossAttack_Bomb_Explode", "BossAttack_Bomb_Explode", false, 0.15f);
	BossAttackRenderer->CreateAnimation("BossAttack_Bomb_Falling", "BossAttack_Bomb_Falling", true, 0.15f);
	BossAttackRenderer->CreateAnimation("BossAttack_ClusterBomb_Appear", "BossAttack_ClusterBomb_Appear", false, 0.15f);
	BossAttackRenderer->CreateAnimation("BossAttack_ClusterBomb_Explode", "BossAttack_ClusterBomb_Explode", false, 0.15f);
	BossAttackRenderer->CreateAnimation("BossAttack_ClusterBomblet_Explode", "BossAttack_ClusterBomblet_Explode", false, 0.15f);
	BossAttackRenderer->CreateAnimation("BossAttack_ClusterBomblet_Idle", "BossAttack_ClusterBomblet_Idle", true, 0.15f);
	BossAttackRenderer->CreateAnimation("BossAttack_ShootExplode", "BossAttack_ShootExplode", false, 0.15f);
}

void ABossAttack::SetAttack(std::string_view _Anim)
{
	BossAttackRenderer->ChangeAnimation(_Anim);

	if ("BossAttack_ShootExplode" == _Anim)
	{
		BossAttackCollision->SetScale3D({ 50.0f, 50.0f });
		BossAttackCollision->SetRelativeLocation({ 0.0f, 110.0f, 0.0f });
	}

	if ("BossAttack_Bomb_Appear" == _Anim)
	{
		BossAttackCollision->SetScale3D({ 20.0f, 20.0f });
		BossAttackCollision->AddWorldLocation({ 0.0f, 120.0f, 0.0f });
	}
}

void ABossAttack::BeginPlay()
{
	AActor::BeginPlay();

	BossAttackCollision->SetCollisionEnter([this](UCollision* _This, UCollision* _Other) {
		if (this->GetBossAttackRenderer()->GetCurSpriteName() == "BOSSATTACK_BOMB_APPEAR" ||
			this->GetBossAttackRenderer()->GetCurSpriteName() == "BOSSATTACK_BOMB_FALLING")
		{
			this->GetBossAttackRenderer()->ChangeAnimation("BossAttack_Bomb_Explode");

			if (_Other->GetCollisionProfileName() == "PLAYER")
			{
				APlayer* Player = static_cast<APlayer*>(GetWorld()->GetMainPawn());
				Player->TakeDamage();
			}
		}

		if (_Other->GetCollisionProfileName() == "PLATFORMWALL")
		{
			ABossPlatform* a = static_cast<ABossPlatform*>(_Other->GetActor());
			a->TakeDamage();
		}
		});
}

void ABossAttack::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	if (BossAttackRenderer->IsCurAnimationEnd())
	{
		if (BossAttackRenderer->GetCurSpriteName() == "BOSSATTACK_SHOOTEXPLODE")
		{
			Destroy();
		}

		if (BossAttackRenderer->GetCurSpriteName() == "BOSSATTACK_BOMB_APPEAR")
		{
			BossAttackRenderer->ChangeAnimation("BossAttack_Bomb_Falling");
		}
		else if (BossAttackRenderer->GetCurSpriteName() == "BOSSATTACK_BOMB_EXPLODE")
		{
			Destroy();
		}
	}

	if (BossAttackRenderer->GetCurSpriteName() == "BOSSATTACK_BOMB_APPEAR" ||
		BossAttackRenderer->GetCurSpriteName() == "BOSSATTACK_BOMB_FALLING")
	{
		AddActorLocation({ 0.0f, -100.0f * _DeltaTime, 0.0f });
	}
	else if (BossAttackRenderer->GetCurSpriteName() == "BOSSATTACK_BOMB_EXPLODE")
	{
		BossAttackCollision->SetRelativeScale3D({ 60.0f, 60.0f });
	}
}