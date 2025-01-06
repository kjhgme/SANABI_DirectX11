#include "PreCompile.h"
#include "BossGameMode.h"

#include <EngineCore/CameraActor.h>
#include <EngineCore/EngineCamera.h>
#include "Player.h"
#include "BossBackGround.h"

ABossGameMode::ABossGameMode()
{
	BackGround = GetWorld()->SpawnActor<ABossBackGround>();
	Player = GetWorld()->SpawnActor<APlayer>();

	MainCamera = GetWorld()->GetMainCamera();
	MainCamera->SetActorLocation({ 0.0f, 0.0f, -1000.0f, 1.0f });
	MainCamera->GetCameraComponent()->SetZSort(0, true);
}

ABossGameMode::~ABossGameMode()
{
}

void ABossGameMode::BeginPlay()
{
	AActor::BeginPlay();
}

void ABossGameMode::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}
