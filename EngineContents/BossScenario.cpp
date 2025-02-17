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
			this->AGetPlayer()->MakeTextBubble("그만 해라. 언제까지 불 셈이냐?", 26.0f, 20.0f, 0.0f, -6.2f);
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
			this->AGetPlayer()->MakeTextBubble("금마리.", 25.0f, 20.0f, 0.0f, -7.0f);
			this->bCanSkipScene = true;
			});
		});
	Scenes.push_back([this]() {
		bCanSkipScene = false;
		Player->ClearTextBubble();
		TimeEventComponent->AddEndEvent(0.5f, [this]() {
			Mari->MakeTextBubble("··· ", 25.0f, 20.0f, -2.0f, -7.5f);
			this->bCanSkipScene = true;
			});
		});
	Scenes.push_back([this]() {
		bCanSkipScene = false;
		Mari->ClearTextBubble();
		Player->ClearTextBubble();
		TimeEventComponent->AddEndEvent(0.2f, [this]() {
			Player->MakeTextBubble("돌아갈 거면 지금이 마지막 기회다.", 25.0f, 20.0f, 0.0f, -7.0f);
			this->bCanSkipScene = true;
			});
		});
	Scenes.push_back([this]() {
		Player->MakeTextBubble("지금부터 부지런히 날아가면..", 25.0f, 20.0f, 0.0f, -7.0f);		
		});
	Scenes.push_back([this]() {
		Player->MakeTextBubble("도시 밖까지 갈 수 있을 거야.", 28.0f, 24.0f, 0.0f, -5.5f);		
		});
	Scenes.push_back([this]() {
		bCanSkipScene = false;
		Player->ClearTextBubble();
		Mari->ChangeToNextAnim();
		MainCamera->Zoom(20.0f, 0.2f);
		TimeEventComponent->AddEndEvent(0.2f, [this]() {
			Mari->MakeTextBubble("아저씨.", 28.0f, 20.0f, -2.0f, -6.5f);
			this->bCanSkipScene = true;
			});
		});
	Scenes.push_back([this]() {
		Mari->MakeTextBubble("아저씨도 이제 그만 해요.", 28.0f, 24.0f, -2.0f, -6.0f);
		});
	Scenes.push_back([this]() {
		bCanSkipScene = false;
		Mari->ClearTextBubble();
		Mari->ChangeToNextAnim();
		MainCamera->Zoom(-20.0f, 0.2f);
		TimeEventComponent->AddEndEvent(0.2f, [this]() {
			Mari->MakeTextBubble("전 아저씨 딸이 아니에요.", 25.0f, 20.0f, -2.0f, -6.7f);
			this->bCanSkipScene = true;
			});
		});
	Scenes.push_back([this]() {
		Mari->MakeTextBubble("그러니까..", 25.0f, 20.0f, -2.0f, -6.7f);

		});
	Scenes.push_back([this]() {
		Mari->MakeTextBubble("이제 서로 그만 하기로 해요.", 30.0f, 24.0f, -2.0f, -5.5f);
		});
	Scenes.push_back([this]() {
		Mari->ChangeToNextAnim();
		Mari->MakeTextBubble("..저 뭐 하나만 물어봐도 돼요?", 25.0f, 20.0f, -2.0f, -6.7f);
	});
	Scenes.push_back([this]() {
		bCanSkipScene = false;
		Mari->ClearTextBubble();
		MainCamera->Zoom(30.0f, 2.0f);
		TimeEventComponent->AddEndEvent(2.0f, [this]() {
			Mari->MakeTextBubble("아저씨는..", 24.0f, 20.0f, -3.0f, -7.0f);
			this->bCanSkipScene = true;
			});
	});
	Scenes.push_back([this]() {
		Mari->MakeTextBubble("딸을 사랑했나요?", 30.0f, 24.0f, -2.0f, -5.5f);
		});
	Scenes.push_back([this]() {
		Mari->ClearTextBubble();
		Player->MakeTextBubble("무슨 의미지?", 25.0f, 20.0f, 0.0f, -7.0f);
	});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->MakeTextBubble("그냥, 문자 그대로요.", 23.0f, 20.0f, -3.0f, -7.3f);
	});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Player->MakeTextBubble("...그래.", 25.0f, 20.0f, 0.0f, -7.0f);
	});
	Scenes.push_back([this]() {
		bCanSkipScene = false;
		Player->ClearTextBubble();
		MainCamera->Zoom(20.0f, 2.0f);
		TimeEventComponent->AddEndEvent(2.0f, [this]() {
			Mari->ChangeToNextAnim();
			Mari->MakeTextBubble("그럼 됐어요.", 23.0f, 20.0f, -3.0f, -7.7f);
			this->bCanSkipScene = true;
			});
	});
	Scenes.push_back([this]() {
		bCanSkipScene = false;
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		TimeEventComponent->AddEndEvent(2.0f, [this]() {
			Mari->MakeTextBubble("그럼 산나비가 많이 밉겠네요.", 25.0f, 24.0f, -3.0f, -6.7f, UColor::RED);	
			this->bCanSkipScene = true;
			});		
	});
	Scenes.push_back([this]() {
		bCanSkipScene = false;
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		MainCamera->Zoom(-20.0f, 1.0f);
		TimeEventComponent->AddEndEvent(1.0f, [this]() {
			Player->MakeTextBubble("뭐?", 28.0f, 20.0f, 0.0f, -6.0f);
			this->bCanSkipScene = true;
			});
		});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->MakeTextBubble("산나비에게 복수하는 거..", 27.0f, 24.0f, -3.0f, -6.0f);
		});
	Scenes.push_back([this]() {
		Mari->MakeTextBubble("잘 됐으면 좋겠다구요.", 24.0f, 20.0f, -3.0f, -7.1f);
		});
	Scenes.push_back([this]() {
		bCanSkipScene = false;
		Mari->ClearTextBubble();
		MainCamera->Zoom(30.0f, 2.0f);
		TimeEventComponent->AddEndEvent(2.0f, [this]() {
			Player->MakeTextBubble("금마리...", 24.0f, 20.0f, 0.0f, -7.5f);
			this->bCanSkipScene = true;
			});
		});
	Scenes.push_back([this]() {
		Player->MakeTextBubble("내가 산나비에게 딸이 죽었다고 얘기 했던 적이 있던가?", 22.0f, 24.0f, 0.0f, -7.8f, UColor::RED);
		});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->MakeTextBubble("아저씨는 ■■■ ■■■■에요.", 20.0f, 20.0f, -2.0f, -8.3f);
	});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		MainCamera->Zoom(-20.0f, 1.0f);
		TimeEventComponent->AddEndEvent(1.0f, [this]() {
			Player->MakeTextBubble("뭐라고?", 25.0f, 20.0f, 0.0f, -7.0f);
			this->bCanSkipScene = true;
			});
		});
	Scenes.push_back([this]() {
		Mari->ChangeToNextAnim();
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Mari->MakeTextBubble("■■■■라고요. 아저씨.", 22.0f, 20.0f, -2.0f, -8.0f);
	});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Player->MakeTextBubble("무..", 28.0f, 20.0f, 0.0f, -6.8f);
		});
	Scenes.push_back([this]() {
		Player->MakeTextBubble("무슨?", 32.0f, 24.0f, 0.0f, -5.3f);
		});
	Scenes.push_back([this]() {
		Player->MakeTextBubble("목소리에 노이즈가..", 24.0f, 20.0f, 0.0f, -7.0f);
	});
	Scenes.push_back([this]() {
		bCanSkipScene = false;
		Mari->ChangeToNextAnim();
		Player->ClearTextBubble();
		MainCamera->Zoom(-20.0f, 2.0f);
		TimeEventComponent->AddEndEvent(2.0f, [this]() {
			Mari->MakeTextBubble("하하..", 25.0f, 20.0f, -3.0f, -6.8f);
			this->bCanSkipScene = true;
			});
		});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->MakeTextBubble("이것까지 철저하게 막아놨구나.", 28.0f, 24.0f, -2.0f, -6.0f);
		});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Mari->MakeTextBubble("집요하네 정말..", 25.0f, 20.0f, -2.0f, -6.7f);
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
					Player->MakeTextBubble("그게 무슨 의미지?!", 32.0f, 24.0f, 0.0f, -5.8f);
					this->bCanSkipScene = true;
					});
			}
			});		
		});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Mari->ChangeToNextAnim();
		Mari->MakeTextBubble("음, 아무것도 아니에요. 그냥 잊어 버려요.", 25.0f, 20.0f, -2.0f, -6.7f);
		});
	Scenes.push_back([this]() {
		bCanSkipScene = false;
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		MainCamera->Zoom(20.0f, 1.0f);
		TimeEventComponent->AddEndEvent(1.0f, [this]() {
			Player->MakeTextBubble("잊으라고?", 28.0f, 20.0f, 0.0f, -7.1f);
			this->bCanSkipScene = true;
			});		
		});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Player->MakeTextBubble("지금 나랑 장난하나?!!", 30.0f, 24.0f, -1.0f, -6.5f);
		});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		Player->MakeTextBubble("당장...", 25.0f, 20.0f, -2.0f, -7.3f);
	});
	Scenes.push_back([this]() {
		bCanSkipScene = false;
		Player->ClearTextBubble();
		Mari->ClearTextBubble();
		TimeEventComponent->AddEndEvent(2.0f, [this]() {
			Player->SetAnimation("SNB_Boss_004_LookBackgroundStart");
			Player->MakeTextBubble("잠깐...", 27.0f, 20.0f, -1.0f, -7.4f);
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
		Player->MakeTextBubble("이 소리는...", 25.0f, 16.0f, 0.0f, -5.0f);
	});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->MakeTextBubble("저기 봐요!! 저, 저게 뭐야?!", 28.0f, 18.0f, -2.0f, -3.8f);
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
			Player->MakeTextBubble("젠장..", 32.0f, 16.0f, 0.0f, -3.7f);
			this->bCanSkipScene = true;
			});
		});

	Scenes.push_back([this]() {
		Player->MakeTextBubble("그래.. 묘비 부대가 왔으면", 30.0f, 16.0f, 0.0f, -3.8f);
		});
	Scenes.push_back([this]() {
		Player->MakeTextBubble("저게 안 나타날 리가 없지.", 30.0f, 16.0f, 0.0f, -3.8f);
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
			Player->MakeTextBubble("금마리.", 32.0f, 18.0f, 0.0f, -3.0f);
			this->bCanSkipScene = true;
			});
	});
	Scenes.push_back([this]() {
		Player->MakeTextBubble("열차 차량 전부 분해해서 넓게 퍼트려라.", 30.0f, 18.0f, 0.0f, -3.6f);
	});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->ChangeToNextAnim();
		Mari->MakeTextBubble("넓게 퍼트리라고요?", 30.0f, 18.0f, -2.0f, -3.8f);
	});
	Scenes.push_back([this]() {
		Mari->ClearTextBubble();
		Player->MakeTextBubble("그래.", 34.0f, 18.0f, 0.0f, -2.6f);
	});
	Scenes.push_back([this]() {
		Player->MakeTextBubble("불새가 왔으니, 여긴 곧 불바다가 될 거다.", 36.0f, 22.0f, 0.0f, -1.8f);
		});
	Scenes.push_back([this]() {
		Player->MakeTextBubble("열차가 줄줄이 박살나지 않게 ", 30.0f, 18.0f, 0.0f, -3.6f);
		});
	Scenes.push_back([this]() {
		Player->MakeTextBubble("전부 떨어뜨려.", 30.0f, 18.0f, 0.0f, -3.6f);
		});
	Scenes.push_back([this]() {
		Player->ClearTextBubble();
		Mari->MakeTextBubble("아저씨는 어쩌려구요?", 30.0f, 18.0f, -2.0f, -3.6f);
		});
	Scenes.push_back([this]() {
		Mari->ClearTextBubble();
		Player->MakeTextBubble("당장 은폐하고 열차로부터 멀리 떨어져라.", 30.0f, 18.0f, 0.0f, -3.7f);
		});
	Scenes.push_back([this]() {
		Mari->MufinOn();
		Player->MakeTextBubble("얘기는..", 30.0f, 18.0f, 0.0f, -3.7f);
		});
	Scenes.push_back([this]() {
		Player->MakeTextBubble("살아남은 다음에 하자.", 34.0f, 22.0f, 0.0f, -2.2f);
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