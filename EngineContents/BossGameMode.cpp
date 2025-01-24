#include "PreCompile.h"
#include "BossGameMode.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/CameraActor.h>
#include <EngineCore/EngineCamera.h>
#include <EngineCore/SpriteRenderer.h>
#include "Player.h"
#include "Mari.h"
#include "Boss.h"
#include "BossBackGround.h"
#include "BossPlatform.h"
#include "TextBubble.h"

#include <EngineCore/EngineGUIWindow.h>
#include <EngineCore/EngineGUI.h>
#include <EngineCore/ImageWidget.h>
#include <EngineCore/FontWidget.h>
#include <EngineCore/HUD.h>
#include "ContentsEditorGUI.h"

class BossGameGUI : public UEngineGUIWindow
{
public:
	void OnGUI() override
	{
		if (true == ImGui::Button("FreeCameraSwitch"))
		{
			GetWorld()->GetMainCamera()->FreeCameraSwitch();
		}
		if (true == ImGui::Button("StartBoss"))
		{
			// Player->AddActorLocation({ 3.0f, 15.0f, 0.0f });
			// Player->SetSceneMode(false);	
		}
	}
};

ABossGameMode::ABossGameMode()
{
	GetWorld()->CreateCollisionProfile("Player");
	GetWorld()->CreateCollisionProfile("Grab");
	GetWorld()->CreateCollisionProfile("Boss");
	GetWorld()->CreateCollisionProfile("BossPlatform");
	GetWorld()->CreateCollisionProfile("BossAttack");
	GetWorld()->CreateCollisionProfile("FloatingBomb");

	GetWorld()->LinkCollisionProfile("Player", "BossPlatform");
	GetWorld()->LinkCollisionProfile("Grab", "BossPlatform");
	GetWorld()->LinkCollisionProfile("Grab", "FloatingBomb");
	GetWorld()->LinkCollisionProfile("BossAttack", "BossPlatform");
	GetWorld()->LinkCollisionProfile("BossAttack", "Player");
	GetWorld()->LinkCollisionProfile("FloatingBomb", "Boss");
	GetWorld()->LinkCollisionProfile("FloatingBomb", "BossPlatform");

	BackGround = GetWorld()->SpawnActor<ABossBackGround>();
	
	Platforms.resize(7);
	for (int i = 0; i < Platforms.size(); ++i)
	{
		Platforms[i] = GetWorld()->SpawnActor<ABossPlatform>();
		Platforms[i].get()->AddRelativeLocation({ 235.0f * (i - 3), -27.0f, 2.0f * i });
	}

	Player = GetWorld()->SpawnActor<APlayer>();
	Player->AddActorLocation({ 0.0f, -35.0f, 0.0f });
	
	Mari = GetWorld()->SpawnActor<AMari>();
	Mari->AddActorLocation({ { 30.0f, -28.0f, -2.0f } });

	MainCamera = GetWorld()->GetMainCamera();
	MainCamera->SetActorLocation({ 0.0f, 20.0f, -300.0f, 1.0f });
	MainCamera->GetCameraComponent()->SetZSort(0, true);

	Boss = GetWorld()->SpawnActor<ABoss>();
	Boss->SetActorLocation(Player->GetActorLocation());
}

ABossGameMode::~ABossGameMode()
{
}

void ABossGameMode::BeginPlay()
{
	AActor::BeginPlay();

	Player->SetAnimation("SNB_Boss_001_TrainOnLoop");
	Mari->ChangeToNextAnim();

	InitScenes();

	//Player->AddActorLocation({ 3.0f, 15.0f, 0.0f });
	//Player->SetSceneMode(false);
}

void ABossGameMode::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	// UEngineDebug::OutPutString(Player->GetActorLocation().ToString());

	if (false == Player->GetSceneMode())
	{
		FVector CameraPos = Player->GetActorLocation();

		if (Player->GetActorLocation().X < -700.0f)
		{
			CameraPos.X = -700.0f;
		}
		if (Player->GetActorLocation().X > 700.0f)
		{
			CameraPos.X = 700.0f;
		}
		if (Player->GetActorLocation().Y < -300.0f)
		{
			CameraPos.Y = -300.0f;
		}
		if (Player->GetActorLocation().Y > 300.0f)
		{
			CameraPos.Y = 300.0f;
		}

		CameraPos.Z = MainCamera->GetActorLocation().Z;
		MainCamera->SetActorLocation(CameraPos);
	}

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
		Scenes[SceneTakeNum]();
		SceneTakeNum++;
	}
	if (UEngineInput::IsDown(VK_F4))
	{
		MainCamera->GetCameraComponent()->SetRelativeLocation({ 0, 0, -500 });
	}
}

void ABossGameMode::LevelChangeStart()
{
	UEngineGUI::AllWindowOff();

	{
		std::shared_ptr<UContentsEditorGUI> Window = UEngineGUI::FindGUIWindow<UContentsEditorGUI>("ContentsEditorGUI");

		if (nullptr == Window)
		{
			Window = UEngineGUI::CreateGUIWindow<UContentsEditorGUI>("ContentsEditorGUI");
		}

		Window->SetActive(true);
	}

	{
		std::shared_ptr<BossGameGUI> Window = UEngineGUI::FindGUIWindow<BossGameGUI>("BossGameGUI");

		if (nullptr == Window)
		{
			Window = UEngineGUI::CreateGUIWindow<BossGameGUI>("BossGameGUI");
		}

		Window->SetActive(true);
	}
}
