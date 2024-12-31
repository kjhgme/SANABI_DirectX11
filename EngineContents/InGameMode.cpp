#include "PreCompile.h"
#include "InGameMode.h"

#include <EngineCore/CameraActor.h>
#include "Player.h"
#include "Daughter.h"
#include "BackGround.h"

AInGameMode::AInGameMode()
{
	BackGround = GetWorld()->SpawnActor<ABackGround>();
	Player = GetWorld()->SpawnActor<APlayer>();
	Daughter = GetWorld()->SpawnActor<ADaughter>();

	MainCamera = GetWorld()->GetMainCamera();
	MainCamera->SetActorLocation({ 0.0f, 0.0f, -1000.0f, 1.0f });
}

AInGameMode::~AInGameMode()
{
}

void AInGameMode::BeginPlay()
{
	AActor::BeginPlay();


}

void AInGameMode::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}
