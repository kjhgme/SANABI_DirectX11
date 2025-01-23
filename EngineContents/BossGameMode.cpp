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

	Player->AddActorLocation({ 3.0f, 15.0f, 0.0f });
	Player->SetSceneMode(false);	
}

void ABossGameMode::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	UEngineDebug::OutPutString(Player->GetActorLocation().ToString());

	if (false == Player->GetSceneMode())
	{
		FVector CameraPos = Player->GetActorLocation();

		if (Player->GetActorLocation().X < -400.0f)
		{
			CameraPos.X = -400.0f;
		}
		if (Player->GetActorLocation().X > 400.0f)
		{
			CameraPos.X = 400.0f;
		}
		if (Player->GetActorLocation().Y < -400.0f)
		{
			CameraPos.Y = -400.0f;
		}
		if (Player->GetActorLocation().Y > 400.0f)
		{
			CameraPos.Y = 400.0f;
		}

		CameraPos.Z = MainCamera->GetActorLocation().Z;
		MainCamera->SetActorLocation(CameraPos);
	}

	if (UEngineInput::IsDown('F'))
	{
		GetWorld()->GetCamera(EEngineCameraType::UICamera)->SetActiveSwitch();
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
	if (UEngineInput::IsDown('X'))
	{
		MainCamera->Zoom(-300.0f, 2.0f);
	}
	// test
	if (UEngineInput::IsDown(VK_SHIFT))
	{
		FVector CameraPos = MainCamera->GetActorLocation();
		CameraPos.Z = -500.0f;
		MainCamera->SetActorLocation(CameraPos);
	}
}

void ABossGameMode::InitScenes()
{
	Scenes.push_back([this]() {	
		Player->MakeTextBubble("�׸� �ض�. �������� �� ���̳�?");
		});
	Scenes.push_back([this]() {
		Player->ClearTextBubble(); 
		Mari->ChangeToNextAnim();
	}); 
	Scenes.push_back([this]() {
		Player->MakeTextBubble("�ݸ���.");
	});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
	});
	Scenes.push_back([this]() {
		Mari->ChangeToNextAnim();
	});
	Scenes.push_back([this]() {	Mari->ChangeToNextAnim(); });
	Scenes.push_back([this]() {
		Mari->MakeTextBubble("������");
	});
	Scenes.push_back([this]() {
		Mari->ClearTextBubble();
	}); 
	Scenes.push_back([this]() {
		Player->MakeTextBubble("���ư� �Ÿ� ������ ������ ��ȸ��.");
	}); 
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Player->MakeTextBubble("���ݺ��� �������� ���ư���..");
		Player->ClearTextBubble();
		Player->MakeTextBubble(" ���� �۱��� �� �� ���� �ž�.");	// sizeUp
	});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->MakeTextBubble("������.");
		Mari->ChangeToNextAnim();
	}); 
	Scenes.push_back([this]() {
		Mari->ClearTextBubble();
		Mari->MakeTextBubble("�������� ���� �׸� �ؿ�.");
	});
	Scenes.push_back([this]() {
		Mari->ClearTextBubble();
		Mari->MakeTextBubble("�� ������ ���� �ƴϿ���."); 
		Mari->ChangeToNextAnim();
	});
	Scenes.push_back([this]() {
		Mari->ClearTextBubble();
		Mari->MakeTextBubble("�׷��ϱ�..");
		Mari->ClearTextBubble();
		Mari->MakeTextBubble("���� ���� �׸� �ϱ�� �ؿ�.");	// sizeUp, shake
	}); 
	Scenes.push_back([this]() {
		Mari->ClearTextBubble();
		Mari->MakeTextBubble("..�� �� �ϳ��� ������� �ſ�?");
		Mari->ChangeToNextAnim();
	});
	Scenes.push_back([this]() {
		Mari->ClearTextBubble();
		Mari->MakeTextBubble("��������..");
		Mari->ClearTextBubble();
		Mari->MakeTextBubble("���� ����߳���?");	//sizeUp, shake
	});
	Scenes.push_back([this]() {
		Mari->ClearTextBubble();
		Player->MakeTextBubble("���� �ǹ���?");
	});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->MakeTextBubble("�׳�, ���� �״�ο�.");
	});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Player->MakeTextBubble("...�׷�.");
	});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Mari->MakeTextBubble("�׷� �ƾ��.");
	});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Mari->MakeTextBubble("�׷� �곪�� ���� �Ӱڳ׿�.");	//Red, sizeUp, zoomIn
	});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Player->MakeTextBubble("��?");	// zoomOut
	});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Mari->MakeTextBubble("�곪�񿡰� �����ϴ� ��..");	// sizeUp, shake
		Mari->ClearTextBubble();
		Mari->MakeTextBubble("�� ������ ���ڴٱ���."); // sizeDowm
	}); 
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Player->MakeTextBubble("�ݸ���...");	// zoomIn
		Player->ClearTextBubble();
		Player->MakeTextBubble("���� �곪�񿡰� ���� �׾��ٰ� ��� �ߴ� ���� �ִ���?"); // red
	});	
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Mari->MakeTextBubble("�������� ������ ������������.");	// blackRect, shack
	}); 
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Player->MakeTextBubble("�����?");	// zoomOut
	});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Mari->MakeTextBubble("������������. ������.");	// blackRect, shack
	});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Player->MakeTextBubble("��..");
		Player->ClearTextBubble();
		Player->MakeTextBubble("����?");	// sizeUp
	});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Player->MakeTextBubble("��Ҹ��� �����..");
	});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Mari->MakeTextBubble("����..");
		Mari->ClearTextBubble();
		Mari->MakeTextBubble("�̰ͱ��� ö���ϰ� ���Ƴ�����.");	// sizeUp
		Mari->ChangeToNextAnim();
	});
	Scenes.push_back([this]() {	Mari->ChangeToNextAnim(); });
	Scenes.push_back([this]() {	Mari->ChangeToNextAnim(); });
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Mari->MakeTextBubble("�����ϳ� ����..");
	}); 
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Player->SetAnimation("SNB_Boss_002_TrainOn2Idle");
	});
	Scenes.push_back([this]() {
		Player->MakeTextBubble("�װ� ���� �ǹ���?!");	// zoomIn
		Player.get()->AddPlayerRendererLocation({ 3.0f, 15.0f, 0.0f });
		Player->SetAnimation("Idle"); 
	});
	Scenes.push_back([this]() {	Mari->ChangeToNextAnim(); });
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Mari->MakeTextBubble("��, �ƹ��͵� �ƴϿ���.");
		Mari->ClearTextBubble();
		Mari->MakeTextBubble("�׳� �ؾ� ������.");	// size Up
		Mari->ChangeToNextAnim();
	});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Player->MakeTextBubble("�������?");
		Player->ClearTextBubble();
		Player->MakeTextBubble("���� ���� �峭�ϳ�?!!");	// size Up
	});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Player->MakeTextBubble("����...");
	});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Player->SetAnimation("SNB_Boss_004_LookBackgroundStart");
		MainCamera->Zoom(-100.0f, 10.0f);
		MainCamera->MoveCamera({0.0f, 60.0f, 0.0f}, 10.0f);
	});
	Scenes.push_back([this](){
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Player->MakeTextBubble("���... �� �Ҹ���...");
		Player->SetAnimation("SNB_Boss_005_LookBackgroundLoop");
	});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Mari->AddActorLocation({ -1.0f, 9.0f,0.0f }); Mari->ChangeToNextAnim(); 
	});	
	Scenes.push_back([this]() {	
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Mari->ChangeToNextAnim();
	});
	Scenes.push_back([this]() {
		Mari->MakeTextBubble("���� ����!! ��, ���� ����?!");
		Mari->ChangeToNextAnim(); 
	}); 
	Scenes.push_back([this]() {	MainCamera->Zoom(-50.0f, 2.0f); }); 
	
	// Boss appeared.
	Scenes.push_back([this]() {
		Boss->State++;
	}); 
	Scenes.push_back([this]() {
		MainCamera->Zoom(-200.0f, 6.0f);
		Boss->State++;
		Boss->SetActorLocation(Player->GetActorLocation());
		Boss->StareAtPlayer();
	});
	// Boss disappeared.

	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble(); 
		Player->MakeTextBubble("����..");
		MainCamera->Zoom(200.0f, 4.0f);
	});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Player->MakeTextBubble("�׷�.. ���� �δ밡 ������ ");	//sizeDown
		Player->ClearTextBubble();
		Player->MakeTextBubble("����");	//sizeUp
		Player->ClearTextBubble();
		Player->MakeTextBubble(" �� ��Ÿ�� ���� ����.");	//sizeDown
		MainCamera->Zoom(200.0f, 4.0f);
	});

	Scenes.push_back([this]() {	
		MainCamera->Zoom(50.0f, 2.0f);
		Player->SetAnimation("SNB_Boss_006_LookBackgroundEnd");
	});
	Scenes.push_back([this]() {	
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Player->MakeTextBubble("�ݸ���.");
		Player->SetAnimation("Idle"); 
	}); 
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Player->MakeTextBubble("���� ���� ���� �����ؼ� �а� ��Ʈ����.");
	});
	Scenes.push_back([this]() {	Mari->ChangeToNextAnim(); });
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Mari->MakeTextBubble("�а� ��Ʈ������?");
		Mari->ChangeToNextAnim();
	}); 
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Player->MakeTextBubble("�׷�.");
	}); 
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Player->MakeTextBubble("�һ��� ������, ");
		Player->ClearTextBubble();
		Player->MakeTextBubble("���� �� �ҹٴٰ� �� �Ŵ�.");	// sizeUp
	});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Player->MakeTextBubble("������ ������ �ڻ쳪�� �ʰ� ");	// sizeUp
		Player->ClearTextBubble();
		Player->MakeTextBubble("���� ����߷�.");
	});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Mari->MakeTextBubble("�������� ��¼������?");	// zoomOut
	});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Player->MakeTextBubble("���� �����ϰ� �����κ��� �ָ� ��������.");
	});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Player->MakeTextBubble("����..");
		Player->ClearTextBubble();
		Player->MakeTextBubble("��Ƴ��� ������ ����.");	// sizeUp
	});
	Scenes.push_back([this]() {	
		Player->ClearTextBubble();
		Mari->MufinOn();
	});
	Scenes.push_back([this]() {	Mari->MufinOff(); Mari->ChangeToNextAnim(); });
	Scenes.push_back([this]() {	Mari->AddActorLocation({ -1.0f, 14.0f, 0.0f });	Mari->ChangeToNextAnim(); });
	// Mari disappeared.
		
	// Boss fight start.
	Scenes.push_back([this]() {
		MainCamera->Zoom(-400.0f, 8.0f);
		Platforms[0].get()->GoToPlace({ -300.0f, 0.0f, 0.0f });
		Platforms[1].get()->GoToPlace({ -15.0f, 300.0f, 0.0f });
		Platforms[2].get()->GoToPlace({ -255.0f, -300.0f, 0.0f });
		Platforms[4].get()->GoToPlace({ 255.0f, 300.0f, 0.0f });
		Platforms[5].get()->GoToPlace({ 10.0f, -300.0f, 0.0f });
		Platforms[6].get()->GoToPlace({ 300.0f, 0.0f, 0.0f });
	});

	Scenes.push_back([this]() {	
		Player->SetSceneMode(false);
		Boss->SetActorLocation(Player->GetActorLocation());
		Boss->StartBattle();
	});
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
