#include "PreCompile.h"
#include "BossGameMode.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/CameraActor.h>
#include <EngineCore/EngineCamera.h>
#include <EngineCore/SpriteRenderer.h>
#include "Player.h"
#include "BossBackGround.h"
#include "BossPlatform.h"
#include "TextBubble.h"

ABossGameMode::ABossGameMode()
{
	BackGround = GetWorld()->SpawnActor<ABossBackGround>();
	Platforms = GetWorld()->SpawnActor<ABossPlatform>();
	Player = GetWorld()->SpawnActor<APlayer>();
	
	BackGround->AttachToActor(Player.get());

	MainCamera = GetWorld()->GetMainCamera();
	MainCamera->SetActorLocation({ 0.0f, 0.0f, -200.0f, 1.0f });
	MainCamera->GetCameraComponent()->SetZSort(0, true);
}

ABossGameMode::~ABossGameMode()
{
}

void ABossGameMode::BeginPlay()
{
	AActor::BeginPlay();

	LastPlayerPosition = Player.get()->GetActorTransform().Location;
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

	Scene();
}

void ABossGameMode::Scene()
{
	if (UEngineInput::IsPress(VK_SPACE))
	{

	}
}
