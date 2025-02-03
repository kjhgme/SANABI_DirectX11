#include "PreCompile.h"
#include "Boss.h"
#include "ContentsEnum.h"

#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/TimeEventComponent.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/CameraActor.h>
#include <EngineCore/Collision.h>

#include <EnginePlatform/EngineInput.h>
#include "BossAttack.h"
#include "BodySlap.h"

ABoss::ABoss()
{
	Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	BossWingRenderer = CreateDefaultSubObject<USpriteRenderer>();
	BossRenderer = CreateDefaultSubObject<USpriteRenderer>();

	BossAimRenderer = CreateDefaultSubObject<USpriteRenderer>();
	BossMachineGunRenderer = CreateDefaultSubObject<USpriteRenderer>();
	BossBomberRenderer = CreateDefaultSubObject<USpriteRenderer>();

	InitBossAnimation();

	BossRenderer->ChangeAnimation("Boss_Slap");
	BossWingRenderer->ChangeAnimation("Boss_Wing_NoImage");

	BossAimRenderer->ChangeAnimation("BossAttack_NoImage");
	BossMachineGunRenderer->ChangeAnimation("BossAttack_NoImage");
	BossBomberRenderer->ChangeAnimation("BossAttack_NoImage");

	BossRenderer->AddRelativeLocation({ 1800.0f, 100.0f, static_cast<float>(ERenderOrder::BOSS) });
	BossWingRenderer->AddRelativeLocation({ 1800.0f, 100.0f, static_cast<float>(ERenderOrder::BOSS) + 1 });
	BossAimRenderer->AddRelativeLocation({ 0.0f, 0.0f, -2.0f });

	BossRenderer->SetupAttachment(RootComponent);
	BossWingRenderer->SetupAttachment(RootComponent);
	BossMachineGunRenderer->SetupAttachment(RootComponent);
	BossBomberRenderer->SetupAttachment(RootComponent);
	
	BossRenderer->SetAutoScaleRatio(0.2f);
	BossWingRenderer->SetAutoScaleRatio(0.2f);

	bIsRight = false;
	BossRenderer->SetRotation({ 0.0f, 180.0f, 0.0f });
	BossWingRenderer->SetRotation({ 0.0f, 180.0f, 0.0f });

	BossCollision = CreateDefaultSubObject<UCollision>();
	BossCollision->SetupAttachment(RootComponent);
	BossCollision->SetRelativeLocation({ { 30.0f, 180.0f, static_cast<float>(ERenderOrder::BOSS) } });
	BossCollision->SetScale3D({ 320.0f, 220.0f });

	TimeEventComponent = CreateDefaultSubObject<UTimeEventComponent>();
}

ABoss::~ABoss()
{
}

void ABoss::BeginPlay()
{
	AActor::BeginPlay();
}

void ABoss::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	if (true == bIsRight)
	{
		BossRenderer->SetRotation({ 0.0f, 0.0f, 0.0f });
		BossWingRenderer->SetRotation({ 0.0f, 0.0f, 0.0f });
	}
	else if (false == bIsRight)
	{
		BossRenderer->SetRotation({ 0.0f, 180.0f, 0.0f });
		BossWingRenderer->SetRotation({ 0.0f, 180.0f, 0.0f });
	}

	if (State == 1)
	{
		BossRenderer->AddRelativeLocation({ -1500.0f * _DeltaTime, 0.0f, 0.0f });
		BossWingRenderer->AddRelativeLocation({ -1500.0f * _DeltaTime, 0.0f, 0.0f });
	}

	if (UEngineInput::IsDown('1'))
	{
		ShootMachineGun();
	}
	if (UEngineInput::IsDown('2'))
	{
		ShootMissile();
	}
	if (UEngineInput::IsDown('3'))
	{
		SlapAttack();
	}
	if (UEngineInput::IsDown('4'))
	{
		DropBomb();
	}
}

void ABoss::InitBossAnimation()
{
	// Body
	{
		BossRenderer->CreateAnimation("Boss_Slap", "Boss_Slap", false);
		BossRenderer->CreateAnimation("Boss_Body_Idle", "Boss_Body_Idle");
		BossRenderer->CreateAnimation("Boss_Body_Broken_Idle", "Boss_Body_Broken_Idle");
	}
	//Wing
	{
		BossWingRenderer->CreateAnimation("Boss_Wing_NoImage", "Boss_Wing_NoImage", false);
		BossWingRenderer->CreateAnimation("Boss_Wing_Neu_Idle", "Boss_Wing_Neu_Idle");
		BossWingRenderer->CreateAnimation("Boss_Wing_Up1", "Boss_Wing_Up1");
		BossWingRenderer->CreateAnimation("Boss_Wing_Up2", "Boss_Wing_Up2");
		BossWingRenderer->CreateAnimation("Boss_Wing_Up3", "Boss_Wing_Up3");
		BossWingRenderer->CreateAnimation("Boss_Wing_Up4", "Boss_Wing_Up4");
		BossWingRenderer->CreateAnimation("Boss_Wing_Down1", "Boss_Wing_Down1");
		BossWingRenderer->CreateAnimation("Boss_Wing_Down2", "Boss_Wing_Down2");
		BossWingRenderer->CreateAnimation("Boss_Wing_Down3", "Boss_Wing_Down3");
		BossWingRenderer->CreateAnimation("Boss_Wing_Down4", "Boss_Wing_Down4");
		BossWingRenderer->CreateAnimation("Boss_Wing_Broken_Up1", "Boss_Wing_Broken_Up1");
		BossWingRenderer->CreateAnimation("Boss_Wing_Broken_Up2", "Boss_Wing_Broken_Up2");
		BossWingRenderer->CreateAnimation("Boss_Wing_Broken_Up3", "Boss_Wing_Broken_Up3");
		BossWingRenderer->CreateAnimation("Boss_Wing_Broken_Up4", "Boss_Wing_Broken_Up4");
		BossWingRenderer->CreateAnimation("Boss_Wing_Broken_Down1", "Boss_Wing_Broken_Down1");
		BossWingRenderer->CreateAnimation("Boss_Wing_Broken_Down2", "Boss_Wing_Broken_Down2");
		BossWingRenderer->CreateAnimation("Boss_Wing_Broken_Down3", "Boss_Wing_Broken_Down3");
		BossWingRenderer->CreateAnimation("Boss_Wing_Broken_Down4", "Boss_Wing_Broken_Down4");
	}
	// Attack
	{
		BossAimRenderer->CreateAnimation("BossAttack_NoImage", "BossAttack_NoImage", false, 0.15f);
		BossAimRenderer->CreateAnimation("Incendiary_Appear", "Incendiary_Appear", false, 0.15f);
		BossAimRenderer->CreateAnimation("Incendiary_Aim", "Incendiary_Aim", false, 0.15f);
		BossAimRenderer->CreateAnimation("Incendiary_AttackLoop", "Incendiary_AttackLoop", true, 0.15f);
		BossAimRenderer->CreateAnimation("Cluster_Appear", "Cluster_Appear", false, 0.15f);
		BossAimRenderer->CreateAnimation("Cluster_Aim", "Cluster_Aim", false, 0.15f);
		BossAimRenderer->CreateAnimation("Cluster_Shoot", "Cluster_Shoot", false, 0.15f);

		BossMachineGunRenderer->CreateAnimation("BossAttack_NoImage", "BossAttack_NoImage", false);
		BossMachineGunRenderer->CreateAnimation("MachineGun_Appear", "MachineGun_Appear", false, 0.15f);
		BossMachineGunRenderer->CreateAnimation("MachineGun_ShootEnd", "MachineGun_ShootEnd", false, 0.15f);
		BossMachineGunRenderer->CreateAnimation("MachineGun_ShootLoop", "MachineGun_ShootLoop", true, 0.15f);
		BossMachineGunRenderer->CreateAnimation("MachineGun_ShootReadyLoop", "MachineGun_ShootReadyLoop", true, 0.15f);

		BossBomberRenderer->CreateAnimation("BossAttack_NoImage", "BossAttack_NoImage", false);
		BossBomberRenderer->CreateAnimation("Boss_Bomber_Opening", "Boss_Bomber_Opening", false, 0.15f);
		BossBomberRenderer->CreateAnimation("Boss_Bomber_OpenedLoop", "Boss_Bomber_OpenedLoop", true, 0.15f);
		BossBomberRenderer->CreateAnimation("Boss_Bomber_Closing", "Boss_Bomber_Closing", false, 0.15f);
	}
}

void ABoss::StareAtPlayer()
{
	BossRenderer->ChangeAnimation("Boss_Body_Idle");
	BossWingRenderer->ChangeAnimation("Boss_Wing_Neu_Idle");

	BossRenderer->SetAutoScaleRatio(1.2f);
	BossWingRenderer->SetAutoScaleRatio(1.2f);

	// BossRenderer->SetRelativeLocation({ 20.0f, -130.0f, 100.0f });
	// BossWingRenderer->SetRelativeLocation({ 20.0f, -130.0f, 101.0f });
	
	BossRenderer->SetRelativeLocation({ 20.0f, -600.0f, static_cast<float>(ERenderOrder::BOSS) });
	BossWingRenderer->SetRelativeLocation({ 20.0f, -600.0f, static_cast<float>(ERenderOrder::BOSS) + 1 });

	FVector TargetPosition1 = { 0.0f, 520.0f, 0.0f };
	FVector TargetPosition2 = { 0.0f, -50.0f, 0.0f };
	FVector TargetPosition3 = { 0.0f, 1500.0f, 0.0f };

	TimeEventComponent->AddUpdateEvent(4.0f, [this, TargetPosition1](float DeltaTime, float CurTime)
	{
		auto Lerp = [](FVector A, FVector B, float Alpha)
		{
			return A * (1 - Alpha) + B * Alpha;
		};

		float Alpha = UEngineMath::Clamp(DeltaTime / 4.0f, 0.0f, 1.0f);
		FVector NewPosition = Lerp(FVector::ZERO, TargetPosition1, Alpha);

		AddActorLocation(NewPosition);
	},
		false
	);

	TimeEventComponent->AddEndEvent(4.0f, [this, TargetPosition2]()
	{
		TimeEventComponent->AddUpdateEvent(1.0f, [this, TargetPosition2](float DeltaTime, float CurTime)
		{
			auto Lerp = [](FVector A, FVector B, float Alpha)
			{
				return A * (1 - Alpha) + B * Alpha;
			};

			float Alpha = UEngineMath::Clamp(DeltaTime / 1.0f, 0.0f, 1.0f);
			FVector NewPosition = Lerp(FVector::ZERO, TargetPosition2, Alpha);

			AddActorLocation(NewPosition);
		},
			false
		);
	},
		false
	);

	TimeEventComponent->AddEndEvent(6.0f, [this, TargetPosition3]()
	{
		TimeEventComponent->AddUpdateEvent(5.0f, [this, TargetPosition3](float DeltaTime, float CurTime)
		{
			auto Lerp = [](FVector A, FVector B, float Alpha)
			{
				return A * (1 - Alpha) + B * Alpha;
			};

			float Alpha = UEngineMath::Clamp(DeltaTime / 5.0f, 0.0f, 1.0f);
			FVector NewPosition = Lerp(FVector::ZERO, TargetPosition3, Alpha);

			AddActorLocation(NewPosition);
		},
			false
		);
	},
		false
	);
}

void ABoss::StartBattle()
{
	BossWingRenderer->ChangeAnimation("Boss_Wing_Up1");

	BossRenderer->SetAutoScaleRatio(1.2f);
	BossWingRenderer->SetAutoScaleRatio(1.2f);

	BossRenderer->SetRelativeLocation({ 20.0f, -800.0f, static_cast<float>(ERenderOrder::BOSS) });
	BossWingRenderer->SetRelativeLocation({ 20.0f, -800.0f, static_cast<float>(ERenderOrder::BOSS) + 1 });

	FVector TargetPosition1 = { 0.0f, 720.0f, 0.0f };
	FVector TargetPosition2 = { 0.0f, -1000.0f, 0.0f };

	TimeEventComponent->AddUpdateEvent(2.0f, [this, TargetPosition1](float DeltaTime, float CurTime)
	{
		auto Lerp = [](FVector A, FVector B, float Alpha)
		{
			return A * (1 - Alpha) + B * Alpha;
		};

		float Alpha = UEngineMath::Clamp(DeltaTime / 2.0f, 0.0f, 1.0f);
		FVector NewPosition = Lerp(FVector::ZERO, TargetPosition1, Alpha);

		AddActorLocation(NewPosition);
	},
		false
	);

	TimeEventComponent->AddEndEvent(2.0f, [this, TargetPosition2]()
	{
		TimeEventComponent->AddUpdateEvent(1.0f, [this, TargetPosition2](float DeltaTime, float CurTime)
		{
			auto Lerp = [](FVector A, FVector B, float Alpha)
			{
				return A * (1 - Alpha) + B * Alpha;
			};

			float Alpha = UEngineMath::Clamp(DeltaTime / 1.0f, 0.0f, 1.0f);
			FVector NewPosition = Lerp(FVector::ZERO, TargetPosition2, Alpha);

			AddActorLocation(NewPosition);
		});
	});
	
	BossCollision->SetCollisionProfileName("Boss");
}

void ABoss::ShootMachineGun()
{
	BossRenderer->SetAutoScaleRatio(0.8f);
	BossWingRenderer->SetAutoScaleRatio(0.8f);
	BossMachineGunRenderer->SetAutoScaleRatio(0.8f);

	BossRenderer->ChangeAnimation("Boss_Body_Idle");
	BossWingRenderer->ChangeAnimation("Boss_Wing_Neu_Idle");
	BossAimRenderer->ChangeAnimation("Incendiary_Appear");

	BossMachineGunRenderer->ChangeAnimation("MachineGun_Appear");
	BossBomberRenderer->ChangeAnimation("BossAttack_NoImage");

	BossRenderer->SetRelativeLocation({ 0.0f, 0.0f, static_cast<float>(ERenderOrder::BOSS) });
	BossWingRenderer->SetRelativeLocation({ 0.0f, 0.0f, static_cast<float>(ERenderOrder::BOSS) + 1 });
	BossMachineGunRenderer->SetRelativeLocation({ 0.0f, 0.0f, static_cast<float>(ERenderOrder::BOSS) - 1 });
	BossAimRenderer->SetRelativeLocation({ 0.0f, 0.0f, static_cast<float>(ERenderOrder::BOSS) - 2 });

	TimeEventComponent->AddUpdateEvent(10.0f, [this](float _DeltaTime, float _CurTime) {
		FVector PlayerPos = GetWorld()->GetMainPawn()->GetActorLocation();

		FVector AimTargetPos = PlayerPos;
		FVector AimCurrentPos = BossAimRenderer->GetWorldLocation();
		FVector AimNewPos = FVector::Lerp(AimCurrentPos, AimTargetPos, _DeltaTime);
		BossAimRenderer->SetWorldLocation(AimNewPos); 
		
		FVector BossTargetPos = AimNewPos;
		FVector BossCurrentPos = GetActorLocation();
		FVector BossNewPos = FVector::Lerp(BossCurrentPos, BossTargetPos, 0.5f * _DeltaTime);
		SetActorLocation(BossNewPos);

		BossAimRenderer->AddRelativeLocation({ 0.0f, 0.0f, -5.0f });

		if (this->GetMachineGunRenderer().get()->IsCurAnimationEnd() && "MACHINEGUN_APPEAR" == this->GetMachineGunRenderer().get()->GetCurSpriteName())
		{
			this->GetMachineGunRenderer()->ChangeAnimation("MachineGun_ShootReadyLoop");
		}

		// 애니메이션.
		if (this->GetBossAimRenderer().get()->IsCurAnimationEnd())
		{
			if ("INCENDIARY_APPEAR" == this->GetBossAimRenderer().get()->GetCurSpriteName())
			{
				this->GetBossAimRenderer()->ChangeAnimation("Incendiary_Aim");
			}
			else if ("INCENDIARY_AIM" == this->GetBossAimRenderer().get()->GetCurSpriteName())
			{
				this->GetBossAimRenderer()->ChangeAnimation("Incendiary_AttackLoop");
				this->GetMachineGunRenderer()->ChangeAnimation("MachineGun_ShootLoop");
			}
		}

		// 총쏘기.
		if ("INCENDIARY_ATTACKLOOP" == this->GetBossAimRenderer().get()->GetCurSpriteName())
		{
			static float AttackTimer = 0.0f;
			AttackTimer += _DeltaTime;

			if (AttackTimer >= 0.3f)
			{
				static float Z = 0.0f;

				std::shared_ptr<ABossAttack> GunAttack = GetWorld()->SpawnActor<ABossAttack>();
				GunAttack->SetActorLocation(AimNewPos);
				GunAttack->AddActorLocation({ 0.0f, -90.0f, Z });

				GunAttack->SetAttack("BossAttack_ShootExplode");

				Z += 0.1f;

				AttackTimer -= 0.3f;
			}
		}
	});

	TimeEventComponent->AddEndEvent(10.0f, [this]() {
		this->GetBossAimRenderer()->ChangeAnimation("BossAttack_NoImage");
		this->GetMachineGunRenderer()->ChangeAnimation("MachineGun_ShootReadyLoop");
	});
}

void ABoss::ShootMissile()
{

}

void ABoss::SlapAttack()
{
	FVector PlayerPos = GetWorld()->GetMainPawn()->GetActorLocation();

	BossRenderer->ChangeAnimation("Boss_Slap");
	BossWingRenderer->ChangeAnimation("Boss_Wing_NoImage");
	BossMachineGunRenderer->ChangeAnimation("BossAttack_NoImage");
	BossBomberRenderer->ChangeAnimation("BossAttack_NoImage");

	BossRenderer->SetAutoScaleRatio(0.7f);
	BossWingRenderer->SetAutoScaleRatio(0.7f);

	BossCollision->SetActive(true);

	if (true == bIsRight)
	{
		// 경고 Renderer
		for (int i = 0; i < 50; ++i)
		{
			TimeEventComponent->AddEndEvent(0.05f * i, [this, i, PlayerPos]() {
				std::shared_ptr<ABossAttack> BodySlapAlert = GetWorld()->SpawnActor<ABodySlap>();
				BodySlapAlert->SetActorLocation(PlayerPos);
				BodySlapAlert->AddActorLocation({ i * 35.0f - (35.0f * 15), -176.0f, 5.0f });
			});
		}

		// Boss 위치.
		BossRenderer->SetRotation({ 0.0f, 0.0f, 0.0f });
		BossWingRenderer->SetRotation({ 0.0f, 0.0f, 0.0f });

		BossRenderer->SetRelativeLocation({ 0.0f, 0.0f, static_cast<float>(ERenderOrder::BOSS) });
		BossWingRenderer->SetRelativeLocation({ 0.0f, 0.0f, static_cast<float>(ERenderOrder::BOSS) + 1 });

		SetActorLocation(PlayerPos);
		AddActorLocation({ -1000.0f, -220.0f, 0.0f });

		TimeEventComponent->AddEndEvent(0.05 * 25, [this]() {
			TimeEventComponent->AddUpdateEvent(4.0f, [this](float DeltaTime, float CurTime) {
				AddActorLocation({ 1500.0f * DeltaTime, 0.0f, 0.0f });
			});
		});
	}
	else if (false == bIsRight)
	{
		// 경고 Renderer
		for (int i = 0; i < 50; ++i)
		{
			TimeEventComponent->AddEndEvent(0.05f * i, [this, i, PlayerPos]() {
				std::shared_ptr<ABossAttack> BodySlapAlert = GetWorld()->SpawnActor<ABodySlap>();
				BodySlapAlert->SetActorLocation(PlayerPos);
				BodySlapAlert->SetActorRotation({ 0.0f, 180.0f, 0.0f });
				BodySlapAlert->AddActorLocation({ -i * 35.0f + (35.0f * 15), -176.0f, 5.0f });
			});
		}

		// Boss 위치
		BossRenderer->SetRotation({ 0.0f, 180.0f, 0.0f });
		BossWingRenderer->SetRotation({ 0.0f, 180.0f, 0.0f });	

		BossRenderer->SetRelativeLocation({ 0.0f, 0.0f, static_cast<float>(ERenderOrder::BOSS) });
		BossWingRenderer->SetRelativeLocation({ 0.0f, 0.0f, static_cast<float>(ERenderOrder::BOSS) + 1 });
		
		SetActorLocation(PlayerPos);
		AddActorLocation({ 1000.0f, -220.0f, 0.0f });
	
		TimeEventComponent->AddEndEvent(0.05 * 25, [this]() {
			TimeEventComponent->AddUpdateEvent(4.0f, [this](float DeltaTime, float CurTime) {
				AddActorLocation({ -1500.0f * DeltaTime, 0.0f, 0.0f });
			});
		});
	}
}

void ABoss::DropBomb()
{
	BossRenderer->SetAutoScaleRatio(0.8f);
	BossWingRenderer->SetAutoScaleRatio(0.8f);
	BossBomberRenderer->SetAutoScaleRatio(0.8f);

	BossRenderer->ChangeAnimation("Boss_Body_Idle");
	BossWingRenderer->ChangeAnimation("Boss_Wing_Neu_Idle");
	BossMachineGunRenderer->ChangeAnimation("BossAttack_NoImage");
	BossBomberRenderer->ChangeAnimation("Boss_Bomber_Opening");
	BossAimRenderer->ChangeAnimation("BossAttack_NoImage");

	BossRenderer->SetRelativeLocation({ 0.0f, 0.0f, static_cast<float>(ERenderOrder::BOSS) });
	BossWingRenderer->SetRelativeLocation({ 0.0f, 0.0f, static_cast<float>(ERenderOrder::BOSS) + 1 });
	BossBomberRenderer->SetRelativeLocation({ 0.0f, 0.0f, static_cast<float>(ERenderOrder::BOSS) + 2 });

	FVector InitialPos = GetActorLocation();
	float TargetY = 400.0f;

	TimeEventComponent->AddUpdateEvent(10.0f, [this, InitialPos, TargetY](float _DeltaTime, float _CurTime) {
		FVector CurrentPos = GetActorLocation();
		FVector NewPos = CurrentPos;

		float LerpAlpha = UEngineMath::Clamp(_CurTime / 2.0f, 0.0f, 1.0f);
		NewPos.Y = UEngineMath::Lerp(InitialPos.Y, TargetY, LerpAlpha);

		FVector PlayerPos = GetWorld()->GetMainPawn()->GetActorLocation();
		NewPos.X = UEngineMath::Lerp(CurrentPos.X, PlayerPos.X, _DeltaTime);

		SetActorLocation(NewPos);

		if (this->GetBossBomberRenderer().get()->IsCurAnimationEnd() && "BOSS_BOMBER_OPENING" == this->GetBossBomberRenderer().get()->GetCurSpriteName())
		{
			this->GetBossBomberRenderer()->ChangeAnimation("Boss_Bomber_OpenedLoop");
		}

		if (NewPos.Y >= TargetY) 
		{
			static float BombTimer = 0.0f;
			BombTimer += _DeltaTime;

			if (BombTimer >= 1.0f) // 1초마다 폭탄 투하
			{
				std::shared_ptr<ABossAttack> BossBomb = GetWorld()->SpawnActor<ABossAttack>();
				BossBomb->SetActorLocation(GetActorLocation());

				static float Z = 0.0f;
				BossBomb->AddActorLocation({ 0.0f, -116.0f, Z });
				Z += 0.1f;

				BossBomb->SetAttack("BossAttack_Bomb_Appear");

				BombTimer -= 1.0f;
			}
		}
	});
}