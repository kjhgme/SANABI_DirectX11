#include "PreCompile.h"
#include "BossGameMode.h"

#include <EngineCore/CameraActor.h>
#include "BossPlatform.h"
#include "Player.h"
#include "Mari.h"
#include "Boss.h"

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
		Player->AddActorLocation({ 3.0f, 15.0f, 0.0f });
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
		MainCamera->MoveCamera({ 0.0f, 60.0f, 0.0f }, 10.0f);
	});
	Scenes.push_back([this]() {
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