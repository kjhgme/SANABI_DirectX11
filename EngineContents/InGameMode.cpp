#include "PreCompile.h"
#include "InGameMode.h"

#include <EngineCore/CameraActor.h>
#include "Player.h"

AInGameMode::AInGameMode()
{
	Player = GetWorld()->SpawnActor<APlayer>();

	std::shared_ptr<ACameraActor> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation({ 0.0f, 0.0f, -10000.0f, 1.0f });
}

AInGameMode::~AInGameMode()
{
}

void AInGameMode::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}
