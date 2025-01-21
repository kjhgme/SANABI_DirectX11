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
	GetWorld()->CreateCollisionProfile("Grab");
	GetWorld()->CreateCollisionProfile("Boss");
	GetWorld()->CreateCollisionProfile("BossPlatform");
	GetWorld()->LinkCollisionProfile("Player", "BossPlatform");
	GetWorld()->LinkCollisionProfile("Grab", "BossPlatform");

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

	// Player->AddActorLocation({ 3.0f, 15.0f, 0.0f });
	// Player->SetSceneMode(false);	
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
		Player->MakeTextBubble("益幻 背虞. 情薦猿走 災 疾戚劃?");
		});
	Scenes.push_back([this]() {
		Player->ClearTextBubble(); 
		Mari->ChangeToNextAnim();
	}); 
	Scenes.push_back([this]() {
		Player->MakeTextBubble("榎原軒.");
	});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
	});
	Scenes.push_back([this]() {
		Mari->ChangeToNextAnim();
	});
	Scenes.push_back([this]() {	Mari->ChangeToNextAnim(); });
	Scenes.push_back([this]() {
		Mari->MakeTextBubble("...");
	});
	Scenes.push_back([this]() {
		Mari->ClearTextBubble();
	}); 
	Scenes.push_back([this]() {
		Player->MakeTextBubble("宜焼哀 暗檎 走榎戚 原走厳 奄噺陥.");
	}); 
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Player->MakeTextBubble("走榎採斗 採走訓備 劾焼亜檎..");
		Player->ClearTextBubble();
		Player->MakeTextBubble(" 亀獣 鉱猿走 哀 呪 赤聖 暗醤.");	// sizeUp
	});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->MakeTextBubble("焼煽松.");
		Mari->ChangeToNextAnim();
	}); 
	Scenes.push_back([this]() {
		Mari->ClearTextBubble();
		Mari->MakeTextBubble("焼煽松亀 戚薦 益幻 背推.");
	});
	Scenes.push_back([this]() {
		Mari->ClearTextBubble();
		Mari->MakeTextBubble("穿 焼煽松 京戚 焼艦拭推."); 
		Mari->ChangeToNextAnim();
	});
	Scenes.push_back([this]() {
		Mari->ClearTextBubble();
		Mari->MakeTextBubble("益君艦猿..");
		Mari->ClearTextBubble();
		Mari->MakeTextBubble("戚薦 辞稽 益幻 馬奄稽 背推.");	// sizeUp, shake
	}); 
	Scenes.push_back([this]() {
		Mari->ClearTextBubble();
		Mari->MakeTextBubble("..煽 更 馬蟹幻 弘嬢坐亀 掬推?");
		Mari->ChangeToNextAnim();
	});
	Scenes.push_back([this]() {
		Mari->ClearTextBubble();
		Mari->MakeTextBubble("焼煽松澗..");
		Mari->ClearTextBubble();
		Mari->MakeTextBubble("京聖 紫櫛梅蟹推?");	//sizeUp, shake
	});
	Scenes.push_back([this]() {
		Mari->ClearTextBubble();
		Player->MakeTextBubble("巷充 税耕走?");
	});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->MakeTextBubble("益撹, 庚切 益企稽推.");
	});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Player->MakeTextBubble("...益掘.");
	});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Mari->MakeTextBubble("益軍 菊嬢推.");
	});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Mari->MakeTextBubble("益軍 至蟹搾亜 弦戚 荒畏革推.");	//Red, sizeUp, zoomIn
	});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Player->MakeTextBubble("更?");	// zoomOut
	});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Mari->MakeTextBubble("至蟹搾拭惟 差呪馬澗 暗..");	// sizeUp, shake
		Mari->ClearTextBubble();
		Mari->MakeTextBubble("設 菊生檎 疏畏陥姥推."); // sizeDowm
	}); 
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Player->MakeTextBubble("榎原軒...");	// zoomIn
		Player->ClearTextBubble();
		Player->MakeTextBubble("鎧亜 至蟹搾拭惟 京戚 宋醸陥壱 剰奄 梅揮 旋戚 赤揮亜?"); // red
	});	
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Mari->MakeTextBubble("焼煽松澗 けけけ けけけけ拭推.");	// blackRect, shack
	}); 
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Player->MakeTextBubble("更虞壱?");	// zoomOut
	});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Mari->MakeTextBubble("けけけけ虞壱推. 焼煽松.");	// blackRect, shack
	});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Player->MakeTextBubble("巷..");
		Player->ClearTextBubble();
		Player->MakeTextBubble("巷充?");	// sizeUp
	});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Player->MakeTextBubble("鯉社軒拭 葛戚綜亜..");
	});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Mari->MakeTextBubble("馬馬..");
		Mari->ClearTextBubble();
		Mari->MakeTextBubble("戚依猿走 旦煽馬惟 厳焼鎌姥蟹.");	// sizeUp
		Mari->ChangeToNextAnim();
	});
	Scenes.push_back([this]() {	Mari->ChangeToNextAnim(); });
	Scenes.push_back([this]() {	Mari->ChangeToNextAnim(); });
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Mari->MakeTextBubble("増推馬革 舛源..");
	}); 
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Player->SetAnimation("SNB_Boss_002_TrainOn2Idle");
	});
	Scenes.push_back([this]() {
		Player->MakeTextBubble("益惟 巷充 税耕走?!");	// zoomIn
		Player.get()->AddPlayerRendererLocation({ 3.0f, 15.0f, 0.0f });
		Player->SetAnimation("Idle"); 
	});
	Scenes.push_back([this]() {	Mari->ChangeToNextAnim(); });
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Mari->MakeTextBubble("製, 焼巷依亀 焼艦拭推.");
		Mari->ClearTextBubble();
		Mari->MakeTextBubble("益撹 蹟嬢 獄形推.");	// size Up
		Mari->ChangeToNextAnim();
	});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Player->MakeTextBubble("蹟生虞壱?");
		Player->ClearTextBubble();
		Player->MakeTextBubble("走榎 蟹櫛 舌貝馬蟹?!!");	// size Up
	});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Player->MakeTextBubble("雁舌...");
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
		Player->MakeTextBubble("節苑... 戚 社軒澗...");
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
		Mari->MakeTextBubble("煽奄 坐推!! 煽, 煽惟 更醤?!");
		Mari->ChangeToNextAnim(); 
	}); 
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
		Player->ClearTextBubble();
		Mari->ClearTextBubble(); 
		Player->MakeTextBubble("賎舌..");
		MainCamera->Zoom(200.0f, 4.0f);
	});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Player->MakeTextBubble("益掘.. 孔搾 採企亜 尽生檎 ");	//sizeDown
		Player->ClearTextBubble();
		Player->MakeTextBubble("煽惟");	//sizeUp
		Player->ClearTextBubble();
		Player->MakeTextBubble(" 照 蟹展劾 軒亜 蒸走.");	//sizeDown
		MainCamera->Zoom(200.0f, 4.0f);
	});

	Scenes.push_back([this]() {	
		MainCamera->Zoom(50.0f, 2.0f);
		Player->SetAnimation("SNB_Boss_006_LookBackgroundEnd");
	});
	Scenes.push_back([this]() {	
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Player->MakeTextBubble("榎原軒.");
		Player->SetAnimation("Idle"); 
	}); 
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Player->MakeTextBubble("伸託 託勲 穿採 歳背背辞 覚惟 遁闘形虞.");
	});
	Scenes.push_back([this]() {	Mari->ChangeToNextAnim(); });
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Mari->MakeTextBubble("覚惟 遁闘軒虞壱推?");
		Mari->ChangeToNextAnim();
	}); 
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Player->MakeTextBubble("益掘.");
	}); 
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Player->MakeTextBubble("災歯亜 尽生艦, ");
		Player->ClearTextBubble();
		Player->MakeTextBubble("食延 稲 災郊陥亜 吃 暗陥.");	// sizeUp
	});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Player->MakeTextBubble("伸託亜 匝匝戚 酵詞蟹走 省惟 ");	// sizeUp
		Player->ClearTextBubble();
		Player->MakeTextBubble("穿採 恭嬢襟形.");
	});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Mari->MakeTextBubble("焼煽松澗 嬢村形姥推?");	// zoomOut
	});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Player->MakeTextBubble("雁舌 精二馬壱 伸託稽採斗 菰軒 恭嬢閃虞.");
	});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Player->MakeTextBubble("剰奄澗..");
		Player->ClearTextBubble();
		Player->MakeTextBubble("詞焼害精 陥製拭 馬切.");	// sizeUp
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
		std::shared_ptr<TestWindow> Window = UEngineGUI::FindGUIWindow<TestWindow>("TestWindow");

		if (nullptr == Window)
		{
			Window = UEngineGUI::CreateGUIWindow<TestWindow>("TestWindow");
		}

		Window->SetActive(true);
	}
}
