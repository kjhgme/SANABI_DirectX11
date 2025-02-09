#include "PreCompile.h"
#include "BossGameMode.h"

#include <EngineCore/CameraActor.h>
#include <EngineCore/TimeEventComponent.h>
#include "BossPlatform.h"
#include "Player.h"
#include "Mari.h"
#include "Boss.h"

void ABossGameMode::InitScenes()
{
	Scenes.push_back([this]() {
		bCanSkipScene = false;
		MainCamera->Zoom(20.0f, 0.1f);

		TimeEventComponent->AddEndEvent(0.2f, [this]() {
			this->AGetPlayer()->MakeTextBubble("�׸� �ض�. �������� �� ���̳�?", 26.0f, 20.0f, 0.0f, -6.0f);
			bCanSkipScene = true;
			});
		});
	Scenes.push_back([this]() {
		bCanSkipScene = false;
		Player->ClearTextBubble();
		MainCamera->Zoom(20.0f, 2.0f);
		TimeEventComponent->AddEndEvent(0.5f, [this]() {
			Mari->ChangeToNextAnim(); 
			});
		TimeEventComponent->AddEndEvent(2.0f, [this]() {
			this->AGetPlayer()->MakeTextBubble("�ݸ���.", 25.0f, 20.0f, 0.0f, -7.0f);
			bCanSkipScene = true;
			});
		});
	Scenes.push_back([this]() {
		bCanSkipScene = false;
		Player->ClearTextBubble();
		TimeEventComponent->AddEndEvent(0.5f, [this]() {
			Mari->MakeTextBubble("������", 25.0f, 20.0f, -1.0f, -7.0f);
			bCanSkipScene = true; 
			});
		});
	Scenes.push_back([this]() {
		bCanSkipScene = false;
		Mari->ClearTextBubble();
		Player->ClearTextBubble();
		TimeEventComponent->AddEndEvent(0.2f, [this]() {
			Player->MakeTextBubble("���ư� �Ÿ� ������ ������ ��ȸ��.", 25.0f, 20.0f, 0.0f, -7.0f);
			bCanSkipScene = true;
			});
		});
	Scenes.push_back([this]() {
		Player->MakeTextBubble("���ݺ��� �������� ���ư���..", 25.0f, 20.0f, 0.0f, -7.0f);		
		});
	Scenes.push_back([this]() {
		Player->MakeTextBubble("���� �۱��� �� �� ���� �ž�.", 28.0f, 24.0f, 0.0f, -5.5f);		
		});
	Scenes.push_back([this]() {
		bCanSkipScene = false;
		Player->ClearTextBubble();
		Mari->ChangeToNextAnim();
		MainCamera->Zoom(20.0f, 0.2f);
		TimeEventComponent->AddEndEvent(0.2f, [this]() {
			Mari->MakeTextBubble("������.", 25.0f, 20.0f, -2.0f, -6.5f);
			bCanSkipScene = true;
			});
		});
	Scenes.push_back([this]() {
		Mari->MakeTextBubble("�������� ���� �׸� �ؿ�.", 28.0f, 24.0f, -2.0f, -6.0f);
		});
	Scenes.push_back([this]() {
		bCanSkipScene = false;
		Mari->ClearTextBubble();
		Mari->ChangeToNextAnim();
		MainCamera->Zoom(-20.0f, 0.2f);
		TimeEventComponent->AddEndEvent(0.2f, [this]() {
			Mari->MakeTextBubble("�� ������ ���� �ƴϿ���.", 25.0f, 20.0f, -2.0f, -6.5f);
			bCanSkipScene = true;
			});
		});
	Scenes.push_back([this]() {
		Mari->MakeTextBubble("�׷��ϱ�..", 25.0f, 20.0f, -2.0f, -6.5f);

		});
	Scenes.push_back([this]() {
		Mari->MakeTextBubble("���� ���� �׸� �ϱ�� �ؿ�.", 28.0f, 24.0f, -2.0f, -6.0f);
		});
	Scenes.push_back([this]() {
		Mari->ChangeToNextAnim();
		Mari->MakeTextBubble("..�� �� �ϳ��� ������� �ſ�?", 25.0f, 20.0f, -2.0f, -6.5f);
	});
	Scenes.push_back([this]() {
		bCanSkipScene = false;
		Mari->ClearTextBubble();
		MainCamera->Zoom(30.0f, 2.0f);
		TimeEventComponent->AddEndEvent(2.0f, [this]() {
			Mari->MakeTextBubble("��������..", 24.0f, 20.0f, -2.0f, -6.5f);
			bCanSkipScene = true;
			});
	});
	Scenes.push_back([this]() {
		Mari->MakeTextBubble("���� ����߳���?", 27.0f, 24.0f, -2.0f, -6.0f);
		});
	Scenes.push_back([this]() {
		Mari->ClearTextBubble();
		Player->MakeTextBubble("���� �ǹ���?", 25.0f, 20.0f, 0.0f, -7.0f);
	});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->MakeTextBubble("�׳�, ���� �״�ο�.", 25.0f, 20.0f, -2.0f, -6.5f);
	});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Player->MakeTextBubble("...�׷�.", 25.0f, 20.0f, 0.0f, -7.0f);
	});
	Scenes.push_back([this]() {
		bCanSkipScene = false;
		Player->ClearTextBubble();
		MainCamera->Zoom(20.0f, 2.0f);
		TimeEventComponent->AddEndEvent(2.0f, [this]() {
			Mari->ChangeToNextAnim();
			Mari->MakeTextBubble("�׷� �ƾ��.", 25.0f, 20.0f, -2.0f, -6.5f);
			bCanSkipScene = true;
			});
	});
	Scenes.push_back([this]() {
		bCanSkipScene = false;
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		TimeEventComponent->AddEndEvent(2.0f, [this]() {
			Mari->MakeTextBubble("�׷� �곪�� ���� �Ӱڳ׿�.", 27.0f, 24.0f, -2.0f, -6.0f, UColor::RED);	//Red, size BB
			bCanSkipScene = true;
			});		
	});
	Scenes.push_back([this]() {
		bCanSkipScene = false;
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		MainCamera->Zoom(-20.0f, 1.0f);
		TimeEventComponent->AddEndEvent(1.0f, [this]() {
			Player->MakeTextBubble("��?", 25.0f, 20.0f, 0.0f, -7.0f);
			bCanSkipScene = true;
			});
		});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->MakeTextBubble("�곪�񿡰� �����ϴ� ��..", 28.0f, 24.0f, -2.0f, -6.0f);	// sizeUp
		});
	Scenes.push_back([this]() {
		Mari->MakeTextBubble("�� ������ ���ڴٱ���.", 25.0f, 20.0f, -2.0f, -6.5f); // sizeDowm
		});
	Scenes.push_back([this]() {
		Mari->ClearTextBubble();
		Player->MakeTextBubble("�ݸ���...", 25.0f, 20.0f, 0.0f, -7.0f);	// zoomIn
	});
	Scenes.push_back([this]() {
		Player->MakeTextBubble("���� �곪�񿡰� ���� �׾��ٰ� ��� �ߴ� ���� �ִ���?", 28.0f, 24.0f, 0.0f, -6.0f, UColor::RED); // red, BB
		});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->MakeTextBubble("�������� ���� ����ῡ��.", 25.0f, 20.0f, -2.0f, -6.5f);	// blackRect, shack
	});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		MainCamera->Zoom(-20.0f, 1.0f);
		TimeEventComponent->AddEndEvent(1.0f, [this]() {
			Player->MakeTextBubble("�����?", 25.0f, 20.0f, 0.0f, -7.0f);	// zoomOut
			bCanSkipScene = true;
			});
		});
	Scenes.push_back([this]() {
		Mari->ChangeToNextAnim();
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Mari->MakeTextBubble("��������. ������.", 25.0f, 20.0f, -2.0f, -6.5f);	// blackRect, shack
	});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Player->MakeTextBubble("��..", 25.0f, 20.0f, 0.0f, -7.0f);
		});
	Scenes.push_back([this]() {
		Player->MakeTextBubble("����?", 28.0f, 24.0f, 0.0f, -6.0f);	// sizeUp
		});
	Scenes.push_back([this]() {
		Player->MakeTextBubble("��Ҹ��� �����..", 25.0f, 20.0f, 0.0f, -7.0f);
	});
	Scenes.push_back([this]() {
		bCanSkipScene = false;
		Mari->ChangeToNextAnim();
		Player->ClearTextBubble();
		Mari->ChangeToNextAnim(); 
		MainCamera->Zoom(-20.0f, 2.0f);
		TimeEventComponent->AddEndEvent(2.0f, [this]() {
			Mari->MakeTextBubble("����..", 25.0f, 20.0f, -2.0f, -6.5f);
			bCanSkipScene = true;
			});
		});
	Scenes.push_back([this]() {
		Mari->MakeTextBubble("�̰ͱ��� ö���ϰ� ���Ƴ�����.", 28.0f, 24.0f, -2.0f, -6.0f);	// sizeUp
		});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Mari->MakeTextBubble("�����ϳ� ����..", 25.0f, 20.0f, -2.0f, -6.5f);
	});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Player->SetAnimation("SNB_Boss_002_TrainOn2Idle");
	});
	Scenes.push_back([this]() {
		bCanSkipScene = false;
		MainCamera->Zoom(-20.0f, 2.0f);
		TimeEventComponent->AddEndEvent(2.0f, [this]() {
			Player->MakeTextBubble("�װ� ���� �ǹ���?!", 28.0f, 24.0f, 0.0f, -6.0f);
			Player->AddActorLocation({ 3.0f, 15.0f, 0.0f });
			Player->SetAnimation("Idle");
			bCanSkipScene = true;
			});		
	});
	////////////////////////////////////
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
		MainCamera->Zoom(-300.0f, 8.0f);
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