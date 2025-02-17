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
			this->AGetPlayer()->MakeTextBubble("�׸� �ض�. �������� �� ���̳�?", 26.0f, 20.0f, 0.0f, -6.2f);
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
			Mari->MakeTextBubble("������ ", 25.0f, 20.0f, -2.0f, -7.5f);
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
			Mari->MakeTextBubble("������.", 28.0f, 20.0f, -2.0f, -6.5f);
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
			Mari->MakeTextBubble("�� ������ ���� �ƴϿ���.", 25.0f, 20.0f, -2.0f, -6.7f);
			this->bCanSkipScene = true;
			});
		});
	Scenes.push_back([this]() {
		Mari->MakeTextBubble("�׷��ϱ�..", 25.0f, 20.0f, -2.0f, -6.7f);

		});
	Scenes.push_back([this]() {
		Mari->MakeTextBubble("���� ���� �׸� �ϱ�� �ؿ�.", 30.0f, 24.0f, -2.0f, -5.5f);
		});
	Scenes.push_back([this]() {
		Mari->ChangeToNextAnim();
		Mari->MakeTextBubble("..�� �� �ϳ��� ������� �ſ�?", 25.0f, 20.0f, -2.0f, -6.7f);
	});
	Scenes.push_back([this]() {
		bCanSkipScene = false;
		Mari->ClearTextBubble();
		MainCamera->Zoom(30.0f, 2.0f);
		TimeEventComponent->AddEndEvent(2.0f, [this]() {
			Mari->MakeTextBubble("��������..", 24.0f, 20.0f, -3.0f, -7.0f);
			this->bCanSkipScene = true;
			});
	});
	Scenes.push_back([this]() {
		Mari->MakeTextBubble("���� ����߳���?", 30.0f, 24.0f, -2.0f, -5.5f);
		});
	Scenes.push_back([this]() {
		Mari->ClearTextBubble();
		Player->MakeTextBubble("���� �ǹ���?", 25.0f, 20.0f, 0.0f, -7.0f);
	});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->MakeTextBubble("�׳�, ���� �״�ο�.", 23.0f, 20.0f, -3.0f, -7.3f);
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
			Mari->MakeTextBubble("�׷� �ƾ��.", 23.0f, 20.0f, -3.0f, -7.7f);
			this->bCanSkipScene = true;
			});
	});
	Scenes.push_back([this]() {
		bCanSkipScene = false;
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		TimeEventComponent->AddEndEvent(2.0f, [this]() {
			Mari->MakeTextBubble("�׷� �곪�� ���� �Ӱڳ׿�.", 25.0f, 24.0f, -3.0f, -6.7f, UColor::RED);	
			this->bCanSkipScene = true;
			});		
	});
	Scenes.push_back([this]() {
		bCanSkipScene = false;
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		MainCamera->Zoom(-20.0f, 1.0f);
		TimeEventComponent->AddEndEvent(1.0f, [this]() {
			Player->MakeTextBubble("��?", 28.0f, 20.0f, 0.0f, -6.0f);
			this->bCanSkipScene = true;
			});
		});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->MakeTextBubble("�곪�񿡰� �����ϴ� ��..", 27.0f, 24.0f, -3.0f, -6.0f);
		});
	Scenes.push_back([this]() {
		Mari->MakeTextBubble("�� ������ ���ڴٱ���.", 24.0f, 20.0f, -3.0f, -7.1f);
		});
	Scenes.push_back([this]() {
		bCanSkipScene = false;
		Mari->ClearTextBubble();
		MainCamera->Zoom(30.0f, 2.0f);
		TimeEventComponent->AddEndEvent(2.0f, [this]() {
			Player->MakeTextBubble("�ݸ���...", 24.0f, 20.0f, 0.0f, -7.5f);
			this->bCanSkipScene = true;
			});
		});
	Scenes.push_back([this]() {
		Player->MakeTextBubble("���� �곪�񿡰� ���� �׾��ٰ� ��� �ߴ� ���� �ִ���?", 22.0f, 24.0f, 0.0f, -7.8f, UColor::RED);
		});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->MakeTextBubble("�������� ���� ����ῡ��.", 20.0f, 20.0f, -2.0f, -8.3f);
	});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		MainCamera->Zoom(-20.0f, 1.0f);
		TimeEventComponent->AddEndEvent(1.0f, [this]() {
			Player->MakeTextBubble("�����?", 25.0f, 20.0f, 0.0f, -7.0f);
			this->bCanSkipScene = true;
			});
		});
	Scenes.push_back([this]() {
		Mari->ChangeToNextAnim();
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Mari->MakeTextBubble("��������. ������.", 22.0f, 20.0f, -2.0f, -8.0f);
	});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Player->MakeTextBubble("��..", 28.0f, 20.0f, 0.0f, -6.8f);
		});
	Scenes.push_back([this]() {
		Player->MakeTextBubble("����?", 32.0f, 24.0f, 0.0f, -5.3f);
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
			Mari->MakeTextBubble("����..", 25.0f, 20.0f, -3.0f, -6.8f);
			this->bCanSkipScene = true;
			});
		});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->MakeTextBubble("�̰ͱ��� ö���ϰ� ���Ƴ�����.", 28.0f, 24.0f, -2.0f, -6.0f);
		});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Mari->MakeTextBubble("�����ϳ� ����..", 25.0f, 20.0f, -2.0f, -6.7f);
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
					Player->MakeTextBubble("�װ� ���� �ǹ���?!", 32.0f, 24.0f, 0.0f, -5.8f);
					this->bCanSkipScene = true;
					});
			}
			});		
		});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Mari->ChangeToNextAnim();
		Mari->MakeTextBubble("��, �ƹ��͵� �ƴϿ���. �׳� �ؾ� ������.", 25.0f, 20.0f, -2.0f, -6.7f);
		});
	Scenes.push_back([this]() {
		bCanSkipScene = false;
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		MainCamera->Zoom(20.0f, 1.0f);
		TimeEventComponent->AddEndEvent(1.0f, [this]() {
			Player->MakeTextBubble("�������?", 28.0f, 20.0f, 0.0f, -7.1f);
			this->bCanSkipScene = true;
			});		
		});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Player->MakeTextBubble("���� ���� �峭�ϳ�?!!", 30.0f, 24.0f, -1.0f, -6.5f);
		});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Player->MakeTextBubble("����...", 25.0f, 20.0f, -2.0f, -7.3f);
	});
	Scenes.push_back([this]() {
		bCanSkipScene = false;
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		TimeEventComponent->AddEndEvent(2.0f, [this]() {
			Player->SetAnimation("SNB_Boss_004_LookBackgroundStart");
			Player->MakeTextBubble("���...", 27.0f, 20.0f, -1.0f, -7.4f);
			this->bCanSkipScene = true;
			});
		TimeEventComponent->AddUpdateEvent(5.0f, [this](float DeltaTime, float CurTime) {
			if (Player->GetPlayerRenderer()->IsCurAnimationEnd())
			{
				Player->SetAnimation("SNB_Boss_005_LookBackgroundLoop");
			}
			});
		});
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
					Mari->AddActorRotation({ 0.0f, 180.0f, 0.0f });
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
		Player->MakeTextBubble("�� �Ҹ���...", 25.0f, 16.0f, 0.0f, -5.0f);
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
		MainCamera->Zoom(-200.0f, 6.0f);
		Boss->State++;
		TimeEventComponent->AddEndEvent(3.0f, [this]() {
			Boss->State++;
			Boss->SetActorLocation(Player->GetActorLocation());
			Boss->StareAtPlayer();
			TimeEventComponent->AddEndEvent(6.0f, [this]() {
				this->bCanSkipScene = true;
				});
			});
		});

	////////////////////////////////////////

	Scenes.push_back([this]() {
		bCanSkipScene = false;
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		MainCamera->Zoom(150.0f, 3.0f);
		MainCamera->MoveCamera({ 0.0f, -60.0f, 0.0f }, 3.0f);
		TimeEventComponent->AddEndEvent(3.0f, [this]() {
			Player->MakeTextBubble("����..", 32.0f, 16.0f, 0.0f, -3.7f);
			this->bCanSkipScene = true;
			});
		});

	Scenes.push_back([this]() {
		Player->MakeTextBubble("�׷�.. ���� �δ밡 ������", 30.0f, 16.0f, 0.0f, -3.8f);
		});
	Scenes.push_back([this]() {
		Player->MakeTextBubble("���� �� ��Ÿ�� ���� ����.", 30.0f, 16.0f, 0.0f, -3.8f);
		});

	Scenes.push_back([this]() {
		bCanSkipScene = false;
		Player->ClearTextBubble();
		Player->SetAnimation("SNB_Boss_006_LookBackgroundEnd");
		TimeEventComponent->AddUpdateEvent(2.0f, [this](float DeltaTime, float CurTime) {
			if(true == Player->GetPlayerRenderer()->IsCurAnimationEnd())
				Player->SetAnimation("Idle");
			});
			MainCamera->Zoom(50.0f, 2.0f);
		TimeEventComponent->AddEndEvent(2.0f, [this]() {
			Player->MakeTextBubble("�ݸ���.", 32.0f, 18.0f, 0.0f, -3.0f);
			this->bCanSkipScene = true;
			});
	});
	Scenes.push_back([this]() {
		Player->MakeTextBubble("���� ���� ���� �����ؼ� �а� ��Ʈ����.", 30.0f, 18.0f, 0.0f, -3.6f);
	});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ChangeToNextAnim();
		Mari->MakeTextBubble("�а� ��Ʈ������?", 30.0f, 18.0f, -2.0f, -3.8f);
	});
	Scenes.push_back([this]() {
		Mari->ClearTextBubble();
		Player->MakeTextBubble("�׷�.", 34.0f, 18.0f, 0.0f, -2.6f);
	});
	Scenes.push_back([this]() {
		Player->MakeTextBubble("�һ��� ������, ���� �� �ҹٴٰ� �� �Ŵ�.", 36.0f, 22.0f, 0.0f, -1.8f);
		});
	Scenes.push_back([this]() {
		Player->MakeTextBubble("������ ������ �ڻ쳪�� �ʰ� ", 30.0f, 18.0f, 0.0f, -3.6f);
		});
	Scenes.push_back([this]() {
		Player->MakeTextBubble("���� ����߷�.", 30.0f, 18.0f, 0.0f, -3.6f);
		});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->MakeTextBubble("�������� ��¼������?", 30.0f, 18.0f, -2.0f, -3.6f);
		});
	Scenes.push_back([this]() {
		Mari->ClearTextBubble();
		Player->MakeTextBubble("���� �����ϰ� �����κ��� �ָ� ��������.", 30.0f, 18.0f, 0.0f, -3.7f);
		});
	Scenes.push_back([this]() {
		Mari->MufinOn();
		Player->MakeTextBubble("����..", 30.0f, 18.0f, 0.0f, -3.7f);
		});
	Scenes.push_back([this]() {
		Player->MakeTextBubble("��Ƴ��� ������ ����.", 34.0f, 22.0f, 0.0f, -2.2f);
		});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->MufinOff();
		Mari->ChangeToNextAnim();

		TimeEventComponent->AddUpdateEvent(3.0f, [this](float DeltaTime, float CurTime) {
			if ("016_ALTDRONERIDECLOAKSTART" == Mari->GetMariRenderer()->GetCurSpriteName())
			{
				if (bAnimeOnce == false)
				{
					Mari->AddActorLocation({ -1.0f, 14.0f, 0.0f });
					bAnimeOnce = true;
				}
			}
			});

		// Boss fight start.
		TimeEventComponent->AddEndEvent(3.0f, [this]() {
			bCanSkipScene = false;
			MainCamera->Zoom(-160.0f, 6.0f);
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
	});
}