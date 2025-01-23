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
	Scenes.push_back([this]() {
		Mari->ChangeToNextAnim();
	});
	Scenes.push_back([this]() {	Mari->ChangeToNextAnim(); });
	Scenes.push_back([this]() {
		Mari->MakeTextBubble("···");
	});
	Scenes.push_back([this]() {
		Mari->ClearTextBubble();
	}); 
	Scenes.push_back([this]() {
		Player->MakeTextBubble("돌아갈 거면 지금이 마지막 기회다.");
	}); 
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Player->MakeTextBubble("지금부터 부지런히 날아가면..");
		Player->ClearTextBubble();
		Player->MakeTextBubble(" 도시 밖까지 갈 수 있을 거야.");	// sizeUp
	});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->MakeTextBubble("아저씨.");
		Mari->ChangeToNextAnim();
	}); 
	Scenes.push_back([this]() {
		Mari->ClearTextBubble();
		Mari->MakeTextBubble("아저씨도 이제 그만 해요.");
	});
	Scenes.push_back([this]() {
		Mari->ClearTextBubble();
		Mari->MakeTextBubble("전 아저씨 딸이 아니에요."); 
		Mari->ChangeToNextAnim();
	});
	Scenes.push_back([this]() {
		Mari->ClearTextBubble();
		Mari->MakeTextBubble("그러니까..");
		Mari->ClearTextBubble();
		Mari->MakeTextBubble("이제 서로 그만 하기로 해요.");	// sizeUp, shake
	}); 
	Scenes.push_back([this]() {
		Mari->ClearTextBubble();
		Mari->MakeTextBubble("..저 뭐 하나만 물어봐도 돼요?");
		Mari->ChangeToNextAnim();
	});
	Scenes.push_back([this]() {
		Mari->ClearTextBubble();
		Mari->MakeTextBubble("아저씨는..");
		Mari->ClearTextBubble();
		Mari->MakeTextBubble("딸을 사랑했나요?");	//sizeUp, shake
	});
	Scenes.push_back([this]() {
		Mari->ClearTextBubble();
		Player->MakeTextBubble("무슨 의미지?");
	});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->MakeTextBubble("그냥, 문자 그대로요.");
	});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Player->MakeTextBubble("...그래.");
	});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Mari->MakeTextBubble("그럼 됐어요.");
	});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Mari->MakeTextBubble("그럼 산나비가 많이 밉겠네요.");	//Red, sizeUp, zoomIn
	});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Player->MakeTextBubble("뭐?");	// zoomOut
	});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Mari->MakeTextBubble("산나비에게 복수하는 거..");	// sizeUp, shake
		Mari->ClearTextBubble();
		Mari->MakeTextBubble("잘 됐으면 좋겠다구요."); // sizeDowm
	}); 
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Player->MakeTextBubble("금마리...");	// zoomIn
		Player->ClearTextBubble();
		Player->MakeTextBubble("내가 산나비에게 딸이 죽었다고 얘기 했던 적이 있던가?"); // red
	});	
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Mari->MakeTextBubble("아저씨는 ㅁㅁㅁ ㅁㅁㅁㅁ에요.");	// blackRect, shack
	}); 
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Player->MakeTextBubble("뭐라고?");	// zoomOut
	});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Mari->MakeTextBubble("ㅁㅁㅁㅁ라고요. 아저씨.");	// blackRect, shack
	});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Player->MakeTextBubble("무..");
		Player->ClearTextBubble();
		Player->MakeTextBubble("무슨?");	// sizeUp
	});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Player->MakeTextBubble("목소리에 노이즈가..");
	});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Mari->MakeTextBubble("하하..");
		Mari->ClearTextBubble();
		Mari->MakeTextBubble("이것까지 철저하게 막아놨구나.");	// sizeUp
		Mari->ChangeToNextAnim();
	});
	Scenes.push_back([this]() {	Mari->ChangeToNextAnim(); });
	Scenes.push_back([this]() {	Mari->ChangeToNextAnim(); });
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Mari->MakeTextBubble("집요하네 정말..");
	}); 
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Player->SetAnimation("SNB_Boss_002_TrainOn2Idle");
	});
	Scenes.push_back([this]() {
		Player->MakeTextBubble("그게 무슨 의미지?!");	// zoomIn
		Player.get()->AddPlayerRendererLocation({ 3.0f, 15.0f, 0.0f });
		Player->SetAnimation("Idle"); 
	});
	Scenes.push_back([this]() {	Mari->ChangeToNextAnim(); });
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Mari->MakeTextBubble("음, 아무것도 아니에요.");
		Mari->ClearTextBubble();
		Mari->MakeTextBubble("그냥 잊어 버려요.");	// size Up
		Mari->ChangeToNextAnim();
	});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Player->MakeTextBubble("잊으라고?");
		Player->ClearTextBubble();
		Player->MakeTextBubble("지금 나랑 장난하나?!!");	// size Up
	});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Player->MakeTextBubble("당장...");
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
		Player->MakeTextBubble("잠깐... 이 소리는...");
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
		Mari->MakeTextBubble("저기 봐요!! 저, 저게 뭐야?!");
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
		Player->MakeTextBubble("젠장..");
		MainCamera->Zoom(200.0f, 4.0f);
	});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Player->MakeTextBubble("그래.. 묘비 부대가 왔으면 ");	//sizeDown
		Player->ClearTextBubble();
		Player->MakeTextBubble("저게");	//sizeUp
		Player->ClearTextBubble();
		Player->MakeTextBubble(" 안 나타날 리가 없지.");	//sizeDown
		MainCamera->Zoom(200.0f, 4.0f);
	});

	Scenes.push_back([this]() {	
		MainCamera->Zoom(50.0f, 2.0f);
		Player->SetAnimation("SNB_Boss_006_LookBackgroundEnd");
	});
	Scenes.push_back([this]() {	
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Player->MakeTextBubble("금마리.");
		Player->SetAnimation("Idle"); 
	}); 
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Player->MakeTextBubble("열차 차량 전부 분해해서 넓게 퍼트려라.");
	});
	Scenes.push_back([this]() {	Mari->ChangeToNextAnim(); });
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Mari->MakeTextBubble("넓게 퍼트리라고요?");
		Mari->ChangeToNextAnim();
	}); 
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Player->MakeTextBubble("그래.");
	}); 
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Player->MakeTextBubble("불새가 왔으니, ");
		Player->ClearTextBubble();
		Player->MakeTextBubble("여긴 곧 불바다가 될 거다.");	// sizeUp
	});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Player->MakeTextBubble("열차가 줄줄이 박살나지 않게 ");	// sizeUp
		Player->ClearTextBubble();
		Player->MakeTextBubble("전부 떨어뜨려.");
	});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Mari->MakeTextBubble("아저씨는 어쩌려구요?");	// zoomOut
	});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Player->MakeTextBubble("당장 은폐하고 열차로부터 멀리 떨어져라.");
	});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Player->MakeTextBubble("얘기는..");
		Player->ClearTextBubble();
		Player->MakeTextBubble("살아남은 다음에 하자.");	// sizeUp
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
