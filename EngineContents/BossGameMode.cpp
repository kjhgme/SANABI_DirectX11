#include "PreCompile.h"
#include "BossGameMode.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/CameraActor.h>
#include <EngineCore/EngineCamera.h>
#include <EngineCore/SpriteRenderer.h>
#include "Player.h"
#include "Mari.h"
#include "BossBackGround.h"
#include "BossPlatform.h"
#include "TextBubble.h"

ABossGameMode::ABossGameMode()
{
	GetWorld()->CreateCollisionProfile("Player");
	GetWorld()->CreateCollisionProfile("Arm");
	GetWorld()->CreateCollisionProfile("Boss");
	GetWorld()->CreateCollisionProfile("BossPlatform");
	GetWorld()->LinkCollisionProfile("Player", "BossPlatform");

	BackGround = GetWorld()->SpawnActor<ABossBackGround>();
	
	Platforms.resize(7);
	for (int i = 0; i < Platforms.size(); ++i)
	{
		Platforms[i] = GetWorld()->SpawnActor<ABossPlatform>();
		Platforms[i].get()->AddRelativeLocation({ 235.0f * (i - 3), -27.0f, 2.0f * i });
	}

	Player = GetWorld()->SpawnActor<APlayer>();
	Player->AddRelativeLocation({ 0.0f, -35.0f, 0.0f });
	
	Mari = GetWorld()->SpawnActor<AMari>();
	Mari->AddRelativeLocation({ { 30.0f, -28.0f, 0.0f } });

	BackGround->AttachToActor(Player.get());

	MainCamera = GetWorld()->GetMainCamera();
	MainCamera->SetActorLocation({ 0.0f, 0.0f, -200.0f, 1.0f });
	MainCamera->GetCameraComponent()->SetZSort(0, true);
}

ABossGameMode::~ABossGameMode()
{
}

void ABossGameMode::BeginPlay()
{
	AActor::BeginPlay();

	LastPlayerPosition = Player.get()->GetActorTransform().Location;
	Player->SetAnimation("SNB_Boss_001_TrainOnLoop");
	Mari->ChangeToNextAnim();
}

void ABossGameMode::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	float4 CurrentPlayerPosition = Player.get()->GetActorTransform().Location;

	float4 DeltaPosition = CurrentPlayerPosition - LastPlayerPosition;

	BackGround->GetBG_Boss_Cloud1_Renderer().get()->AddUVPlusValue({ DeltaPosition.X * 0.00002f, 0.0f, 0.0f, 1.0f });
	BackGround->GetBG_Boss_Cloud2_Renderer().get()->AddUVPlusValue({ DeltaPosition.X * 0.00008f, 0.0f, 0.0f, 1.0f });
	BackGround->GetBG_Boss_Building1_Renderer().get()->AddUVPlusValue({ DeltaPosition.X * 0.0004f, 0.0f, 0.0f, 1.0f });
	BackGround->GetBG_Boss_Building2_Renderer().get()->AddUVPlusValue({ DeltaPosition.X * 0.0008f, 0.0f, 0.0f, 1.0f });

	LastPlayerPosition = CurrentPlayerPosition;

	if (UEngineInput::IsPress('Q'))
	{
		MainCamera->AddRelativeLocation({ 0.0f, 0.0f, -100.0f * _DeltaTime, 1.0f });
	}
	if (UEngineInput::IsPress('E'))
	{
		MainCamera->AddRelativeLocation({ 0.0f, 0.0f, 100.0f * _DeltaTime, 1.0f });
	}
	if (UEngineInput::IsDown(VK_SPACE) && true == Player->GetSceneMode())
	{
		SceneTakeNum++;
		Scene(_DeltaTime);
	}
	/*if (UEngineInput::IsDown(VK_F1))
	{
		GetWorld()->GetMainCamera()->FreeCameraSwitch();
	}*/

	if (true == bPlayNextAnimation && true == Player->GetPlayerRenderer().get()->IsCurAnimationEnd())
	{
		SceneTakeNum++;
		Scene(_DeltaTime);

		bPlayNextAnimation = false;
	}

	Player->AddActorLocation({ 300.0f * _DeltaTime, 0.0f, 0.0f });
	for (int i = 0; i < Platforms.size(); ++i) {
		Platforms[i].get()->AddActorLocation({ { 300.0f * _DeltaTime, 0.0f, 0.0f } });
	}
	Mari->AddActorLocation({ 300.0f * _DeltaTime, 0.0f, 0.0f });
}

void ABossGameMode::Scene(float _DeltaTime)
{
	switch(SceneTakeNum)
	{
	case 1:
		break;	
	case 2:
	{
		Mari->ChangeToNextAnim();
		//Player->SetAnimation("SNB_Boss_002_TrainOn2Idle");
		//bPlayNextAnimation = true;
		break;
	}
	case 3:
	{
		Mari->ChangeToNextAnim();
		//Player->GetPlayerRenderer().get()->AddRelativeLocation({ 2.0f, 14.0f, 0.0f });
		//Player->SetAnimation("Idle");
		break;
	}
	case 4:
	{
		Mari->ChangeToNextAnim();
		Player->SetAnimation("SNB_Boss_004_LookBackgroundStart");
		//bPlayNextAnimation = true;
		break;
	}
	case 5:
	{
		Mari->ChangeToNextAnim();
		Player->SetAnimation("SNB_Boss_005_LookBackgroundLoop");
		break;
	}
	case 6:
	{
		Mari->ChangeToNextAnim();
		Player->SetAnimation("SNB_Boss_006_LookBackgroundEnd");
		//bPlayNextAnimation = true;
		break;
	}
	case 7:
	{
		Mari->ChangeToNextAnim();
		Player->SetAnimation("Idle");
		break;
	}
	case 8:
	{
		Mari->ChangeToNextAnim();
		// Player->SetSceneMode(false);
		break;
	}
	case 9:
	{
		Mari->ChangeToNextAnim();
		break;
	}
	case 10:
	{
		Mari->AddActorLocation({ -1.0f, 9.0f,0.0f });
		Mari->ChangeToNextAnim();
		break;
	}
	case 11:
	{
		Mari->ChangeToNextAnim();
		break;
	}
	case 12:
	{
		Mari->ChangeToNextAnim();
		break;
	}
	case 13:
	{
		Mari->ChangeToNextAnim();
		break;
	}
	case 14:
	{
		Mari->MufinOn();
		break;
	}
	case 15:
	{
		Mari->MufinOff();
		Mari->ChangeToNextAnim();
		break;
	}
	case 16:
	{
		Mari->AddActorLocation({ -1.0f, 14.0f, 0.0f });
		Mari->ChangeToNextAnim();
		break;
	}
	default:
		break;
	}
}
