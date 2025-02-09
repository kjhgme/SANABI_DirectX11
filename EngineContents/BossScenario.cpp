#include "PreCompile.h"
#include "BossGameMode.h"

#include <EngineCore/CameraActor.h>
#include <EngineCore/TimeEventComponent.h>
#include <EngineCore/SpriteRenderer.h>
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
			this->bCanSkipScene = true;
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
			this->bCanSkipScene = true;
			});
		});
	Scenes.push_back([this]() {
		bCanSkipScene = false;
		Player->ClearTextBubble();
		TimeEventComponent->AddEndEvent(0.5f, [this]() {
			Mari->MakeTextBubble("������", 25.0f, 20.0f, -1.0f, -7.5f);
			this->bCanSkipScene = true;
			});
		});
	Scenes.push_back([this]() {
		bCanSkipScene = false;
		Mari->ClearTextBubble();
		Player->ClearTextBubble();
		TimeEventComponent->AddEndEvent(0.2f, [this]() {
			Player->MakeTextBubble("���ư� �Ÿ� ������ ������ ��ȸ��.", 25.0f, 20.0f, 0.0f, -7.0f);
			this->bCanSkipScene = true;
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
			this->bCanSkipScene = true;
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
			this->bCanSkipScene = true;
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
			Mari->MakeTextBubble("��������..", 24.0f, 20.0f, -2.0f, -7.0f);
			this->bCanSkipScene = true;
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
			Mari->MakeTextBubble("�׷� �ƾ��.", 23.0f, 20.0f, -2.0f, -7.5f);
			this->bCanSkipScene = true;
			});
	});
	Scenes.push_back([this]() {
		bCanSkipScene = false;
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		TimeEventComponent->AddEndEvent(2.0f, [this]() {
			Mari->MakeTextBubble("�׷� �곪�� ���� �Ӱڳ׿�.", 26.0f, 24.0f, -2.0f, -6.5f, UColor::RED);	//Red, size BB
			this->bCanSkipScene = true;
			});		
	});
	Scenes.push_back([this]() {
		bCanSkipScene = false;
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		MainCamera->Zoom(-20.0f, 1.0f);
		TimeEventComponent->AddEndEvent(1.0f, [this]() {
			Player->MakeTextBubble("��?", 25.0f, 20.0f, 0.0f, -7.0f);
			this->bCanSkipScene = true;
			});
		});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->MakeTextBubble("�곪�񿡰� �����ϴ� ��..", 27.0f, 24.0f, -2.0f, -6.0f);	// sizeUp
		});
	Scenes.push_back([this]() {
		Mari->MakeTextBubble("�� ������ ���ڴٱ���.", 24.0f, 20.0f, -2.0f, -7.0f); // sizeDowm
		});
	Scenes.push_back([this]() {
		bCanSkipScene = false;
		Mari->ClearTextBubble();
		MainCamera->Zoom(30.0f, 2.0f);
		TimeEventComponent->AddEndEvent(2.0f, [this]() {
			Player->MakeTextBubble("�ݸ���...", 24.0f, 20.0f, 0.0f, -7.0f);
			this->bCanSkipScene = true;
			});
		});
	Scenes.push_back([this]() {
		Player->MakeTextBubble("���� �곪�񿡰� ���� �׾��ٰ� ��� �ߴ� ���� �ִ���?", 28.0f, 24.0f, 0.0f, -6.0f, UColor::RED); // red, BB
		});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->MakeTextBubble("�������� ���� ����ῡ��.", 23.0f, 20.0f, -2.0f, -7.2f);	// blackRect, shack
	});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		MainCamera->Zoom(-20.0f, 1.0f);
		TimeEventComponent->AddEndEvent(1.0f, [this]() {
			Player->MakeTextBubble("�����?", 25.0f, 20.0f, 0.0f, -7.0f);	// zoomOut
			this->bCanSkipScene = true;
			});
		});
	Scenes.push_back([this]() {
		Mari->ChangeToNextAnim();
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Mari->MakeTextBubble("��������. ������.", 24.0f, 20.0f, -2.0f, -7.0f);	// blackRect, shack
	});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Player->MakeTextBubble("��..", 24.0f, 20.0f, 0.0f, -7.0f);
		});
	Scenes.push_back([this]() {
		Player->MakeTextBubble("����?", 28.0f, 24.0f, 0.0f, -6.0f);	// sizeUp
		});
	Scenes.push_back([this]() {
		Player->MakeTextBubble("��Ҹ��� �����..", 24.0f, 20.0f, 0.0f, -7.0f);
	});
	Scenes.push_back([this]() {
		bCanSkipScene = false;
		Mari->ChangeToNextAnim();
		Player->ClearTextBubble();
		MainCamera->Zoom(-20.0f, 2.0f);
		TimeEventComponent->AddEndEvent(2.0f, [this]() {
			Mari->MakeTextBubble("����..", 25.0f, 20.0f, -2.0f, -6.5f);
			this->bCanSkipScene = true;
			});
		});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->MakeTextBubble("�̰ͱ��� ö���ϰ� ���Ƴ�����.", 28.0f, 24.0f, -2.0f, -6.0f);	// sizeUp
		});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Mari->MakeTextBubble("�����ϳ� ����..", 25.0f, 20.0f, -2.0f, -6.4f);
	});
	Scenes.push_back([this]() {
		bCanSkipScene = false;
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Player->SetAnimation("SNB_Boss_002_TrainOn2Idle");
		TimeEventComponent->AddUpdateEvent(3.0f, [this](float DeltaTime, float CurTime) {
			if (Player->GetPlayerRenderer()->IsCurAnimationEnd())
			{
				MainCamera->Zoom(-20.0f, 1.0f);
				Player->SetAnimation("Idle");
				Player->AddActorLocation({ 3.0f, 15.0f, 0.0f });
				TimeEventComponent->AddEndEvent(1.0f, [this]() {
					Player->MakeTextBubble("�װ� ���� �ǹ���?!", 30.0f, 24.0f, 0.0f, -6.0f);
					this->bCanSkipScene = true;
					});
			}
			});		
		});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Mari->ChangeToNextAnim();
		Mari->MakeTextBubble("��, �ƹ��͵� �ƴϿ���. �׳� �ؾ� ������.", 25.0f, 20.0f, -2.0f, -6.5f);
		});
	Scenes.push_back([this]() {
		bCanSkipScene = false;
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		MainCamera->Zoom(20.0f, 1.0f);
		TimeEventComponent->AddEndEvent(1.0f, [this]() {
			Player->MakeTextBubble("�������?", 25.0f, 20.0f, 0.0f, -7.5f);
			this->bCanSkipScene = true;
			});		
		});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Player->MakeTextBubble("���� ���� �峭�ϳ�?!!", 28.0f, 24.0f, 0.0f, -6.0f);
		});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Player->MakeTextBubble("����...", 25.0f, 20.0f, 0.0f, -7.5f);
	});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Player->SetAnimation("SNB_Boss_004_LookBackgroundStart");
		TimeEventComponent->AddEndEvent(2.0f, [this]() {
			Player->MakeTextBubble("���...", 25.0f, 20.0f, 0.0f, -7.5f);
			});
		TimeEventComponent->AddUpdateEvent(5.0f, [this](float DeltaTime, float CurTime) {
			if (Player->GetPlayerRenderer()->IsCurAnimationEnd())
			{
				Player->SetAnimation("SNB_Boss_005_LookBackgroundLoop");
			}
			});
		});

	//////////////////////////////////////

	Scenes.push_back([this]() {
		bCanSkipScene = false;
		Player->ClearTextBubble();
		Mari->ClearTextBubble();		
		MainCamera->Zoom(-100.0f, 8.0f);
		MainCamera->MoveCamera({ 0.0f, 60.0f, 0.0f }, 8.0f);

		TimeEventComponent->AddEndEvent(2.0f, [this]() {
			Mari->ChangeToNextAnim();			
			});
		TimeEventComponent->AddUpdateEvent(5.0f, [this](float DeltaTime, float CurTime) {
			if ("010_LOOKBACKGROUNDSTART" == Mari->GetMariRenderer()->GetCurSpriteName())
			{
				if (bAnimeOnce == true)
				{
					Mari->AddActorLocation({ -1.0f, 10.0f,0.0f });
					bAnimeOnce = false;
				}
			}
			});
		TimeEventComponent->AddEndEvent(8.0f, [this]() {
			this->bCanSkipScene = true;
			}); 
	});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Player->MakeTextBubble("�� �Ҹ���...", 25.0f, 18.0f, 0.0f, -5.0f);
	});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->MakeTextBubble("���� ����!! ��, ���� ����?!", 28.0f, 18.0f, -2.0f, -3.8f);
	});

	// Boss appeared.
	Scenes.push_back([this]() {
		bCanSkipScene = false;
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		MainCamera->Zoom(-50.0f, 3.0f);
		Boss->State++;
		TimeEventComponent->AddEndEvent(3.0f, [this]() {
			MainCamera->Zoom(-200.0f, 6.0f);
			Boss->State++;
			Boss->SetActorLocation(Player->GetActorLocation());
			Boss->StareAtPlayer();
			TimeEventComponent->AddEndEvent(6.0f, [this]() {
				this->bCanSkipScene = true;
				});
			this->bCanSkipScene = true;
			});
		});

	Scenes.push_back([this]() {
		bCanSkipScene = false;
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		MainCamera->Zoom(200.0f, 4.0f);
		TimeEventComponent->AddEndEvent(4.0f, [this]() {
			Player->MakeTextBubble("����..", 30.0f, 20.0f, 0.0f, -4.5f);
			this->bCanSkipScene = true;
			});
		});

	/////////////////////

	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Player->MakeTextBubble("�׷�.. ���� �δ밡 ������", 30.0f, 18.0f, 0.0f, -5.0f);	//sizeDown
		});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Player->MakeTextBubble("���� �� ��Ÿ�� ���� ����.", 30.0f, 18.0f, 0.0f, -5.0f);	//sizeUp
		});

	//////////////////////////////////

	Scenes.push_back([this]() {
		bCanSkipScene = false;
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Player->SetAnimation("SNB_Boss_006_LookBackgroundEnd");
		MainCamera->Zoom(50.0f, 2.0f);
		TimeEventComponent->AddEndEvent(4.0f, [this]() {
			MainCamera->Zoom(200.0f, 4.0f);
			this->bCanSkipScene = true;
			});
	});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Player->MakeTextBubble("�ݸ���.", 25.0f, 20.0f, 0.0f, -7.0f);
		Player->SetAnimation("Idle"); 
	});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Player->MakeTextBubble("���� ���� ���� �����ؼ� �а� ��Ʈ����.", 25.0f, 20.0f, 0.0f, -7.0f);
	});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Mari->ChangeToNextAnim();
		Mari->MakeTextBubble("�а� ��Ʈ������?", 25.0f, 20.0f, -2.0f, -6.5f);
	});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Player->MakeTextBubble("�׷�.", 25.0f, 20.0f, 0.0f, -7.0f);
	});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Player->MakeTextBubble("�һ��� ������, ", 25.0f, 20.0f, 0.0f, -7.0f);
		});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Player->MakeTextBubble("���� �� �ҹٴٰ� �� �Ŵ�.", 28.0f, 24.0f, 0.0f, -6.0f);	// sizeUp
		});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Player->MakeTextBubble("������ ������ �ڻ쳪�� �ʰ� ", 28.0f, 24.0f, 0.0f, -6.0f);	// sizeUp
		});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Player->MakeTextBubble("���� ����߷�.", 25.0f, 20.0f, 0.0f, -7.0f);
		});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Mari->MakeTextBubble("�������� ��¼������?", 25.0f, 20.0f, -2.0f, -6.5f);	// zoomOut
		});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Player->MakeTextBubble("���� �����ϰ� �����κ��� �ָ� ��������.", 25.0f, 20.0f, 0.0f, -7.0f);
		});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Mari->MufinOn();
		Player->MakeTextBubble("����..", 25.0f, 20.0f, 0.0f, -7.0f);
		});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Player->MakeTextBubble("��Ƴ��� ������ ����.", 28.0f, 24.0f, 0.0f, -6.0f);	// sizeUp
		});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->MufinOff();
		Mari->ChangeToNextAnim();
		Mari->AddActorLocation({ -1.0f, 14.0f, 0.0f });
	});
	// Mari disappeared.

	// Boss fight start.
	Scenes.push_back([this]() {
		bCanSkipScene = false;
		MainCamera->Zoom(-300.0f, 8.0f);
		Platforms[0].get()->GoToPlace({ -300.0f, 0.0f, 0.0f });
		Platforms[1].get()->GoToPlace({ -15.0f, 300.0f, 0.0f });
		Platforms[2].get()->GoToPlace({ -255.0f, -300.0f, 0.0f });
		Platforms[4].get()->GoToPlace({ 255.0f, 300.0f, 0.0f });
		Platforms[5].get()->GoToPlace({ 10.0f, -300.0f, 0.0f });
		Platforms[6].get()->GoToPlace({ 300.0f, 0.0f, 0.0f });
		TimeEventComponent->AddEndEvent(8.0f, [this]() {
			this->bCanSkipScene = true;

			Player->SetSceneMode(false);

			Boss->SetActorLocation(Player->GetActorLocation());
			Boss->StartBattle();
			});
		});
}