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
		Player->AddActorLocation({ 3.0f, 15.0f, 0.0f });
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
		MainCamera->MoveCamera({ 0.0f, 60.0f, 0.0f }, 10.0f);
	});
	Scenes.push_back([this]() {
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