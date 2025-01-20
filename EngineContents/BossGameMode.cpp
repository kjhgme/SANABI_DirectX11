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

class TestWindow : public UEngineGUIWindow
{
public:
	void OnGUI() override
	{
		if (true == ImGui::Button("FreeCameraOn"))
		{
			GetWorld()->GetMainCamera()->FreeCameraSwitch();
		}

		ImGui::SameLine();
		ImGui::Text("test");
	}
};

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
	Player->AddActorLocation({ 0.0f, -35.0f, 0.0f });

	Mari = GetWorld()->SpawnActor<AMari>();
	Mari->AddActorLocation({ { 30.0f, -28.0f, -2.0f } });

	MainCamera = GetWorld()->GetMainCamera();
	MainCamera->SetActorLocation({ 0.0f, 50.0f, -200.0f, 1.0f });
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

	InitScenes();

	//Player.get()->AddPlayerRendererLocation({ 3.0f, 15.0f, 0.0f });
	//Player->SetSceneMode(false);	
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
		Scenes[SceneTakeNum]();
		SceneTakeNum++;
	}


	//if (true == bPlayNextAnimation && true == Player->GetPlayerRenderer().get()->IsCurAnimationEnd())
	//{
	//	Scenes[SceneTakeNum]();
	//	SceneTakeNum++;
	//	// Scene(_DeltaTime);
	//
	//	bPlayNextAnimation = false;
	//}



	//Player->AddActorLocation({ 300.0f * _DeltaTime, 0.0f, 0.0f });
	//for (int i = 0; i < Platforms.size(); ++i) {
	//	Platforms[i].get()->AddActorLocation({ { 300.0f * _DeltaTime, 0.0f, 0.0f } });
	//}
	//Mari->AddActorLocation({ 300.0f * _DeltaTime, 0.0f, 0.0f });
	//BackGround->AddActorLocation({ 300.0f * _DeltaTime, 0.0f, 0.0f });

	//if(Boss != nullptr && Boss.get()->State >= 1)
	//	Boss->AddActorLocation({ 300.0f * _DeltaTime, 0.0f, 0.0f });
}

void ABossGameMode::InitScenes()
{
	Scenes.push_back([this]() {	
		Player->MakeTextBubble("그만 해라. 언제까지 불 셈이냐?");
		});
	Scenes.push_back([this]() {
		Player->ClearTextBubble(); 
		Mari->ChangeToNextAnim();
	}); 
	Scenes.push_back([this]() {
		Player->MakeTextBubble("금마리.");
	});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
	});
	Scenes.push_back([this]() {	Mari->ChangeToNextAnim(); });
	Scenes.push_back([this]() {	Mari->ChangeToNextAnim(); });
	Scenes.push_back([this]() {	Mari->ChangeToNextAnim(); });
	Scenes.push_back([this]() {	Mari->ChangeToNextAnim(); });
	Scenes.push_back([this]() {	Player->SetAnimation("SNB_Boss_002_TrainOn2Idle"); });
	Scenes.push_back([this]() {	Player.get()->AddPlayerRendererLocation({ 3.0f, 15.0f, 0.0f }); Player->SetAnimation("Idle"); });
	Scenes.push_back([this]() {	Mari->ChangeToNextAnim(); });
	Scenes.push_back([this]() {	Mari->ChangeToNextAnim(); });

	Scenes.push_back([this]() {	
		Player->SetAnimation("SNB_Boss_004_LookBackgroundStart");
		MainCamera->Zoom(-100.0f, 10.0f);
		MainCamera->MoveCamera({0.0f, 60.0f, 0.0f}, 10.0f);
	});
	Scenes.push_back([this]() {	Player->SetAnimation("SNB_Boss_005_LookBackgroundLoop"); });
	Scenes.push_back([this]() {	Mari->ChangeToNextAnim(); });
	Scenes.push_back([this]() {	Mari->AddActorLocation({ -1.0f, 9.0f,0.0f }); Mari->ChangeToNextAnim(); });	
	Scenes.push_back([this]() {	Mari->ChangeToNextAnim(); }); 
	Scenes.push_back([this]() {	MainCamera->Zoom(-50.0f, 2.0f); }); 
	
	// Boss appeared.
	Scenes.push_back([this]() {
		Boss = GetWorld()->SpawnActor<ABoss>();
		Boss->SetActorLocation(Player->GetActorLocation());
	}); 
	Scenes.push_back([this]() {
		MainCamera->Zoom(-200.0f, 6.0f);
		Boss->State++;
		Boss->SetActorLocation(Player->GetActorLocation());
		Boss->StareAtPlayer();
	});
	// Boss disappeared.

	Scenes.push_back([this]() {
		MainCamera->Zoom(200.0f, 4.0f);
	});

	Scenes.push_back([this]() {	
		MainCamera->Zoom(50.0f, 2.0f);
		Player->SetAnimation("SNB_Boss_006_LookBackgroundEnd");
	});
	Scenes.push_back([this]() {	Player->SetAnimation("Idle"); });
	Scenes.push_back([this]() {	Mari->ChangeToNextAnim(); });
	Scenes.push_back([this]() {	Mari->ChangeToNextAnim(); });
	Scenes.push_back([this]() {	Mari->MufinOn(); });
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
		std::shared_ptr<TestWindow> Window = UEngineGUI::FindGUIWindow<TestWindow>("TestWindow");

		if (nullptr == Window)
		{
			Window = UEngineGUI::CreateGUIWindow<TestWindow>("TestWindow");
		}

		Window->SetActive(true);
	}
}
