#include "PreCompile.h"
#include "EndingGameMode.h"

#include <EngineCore/CameraActor.h>
#include "EndingPlayer.h"

AEndingGameMode::AEndingGameMode()
{
	Player = GetWorld()->SpawnActor<AEndingPlayer>();

	std::shared_ptr<ACameraActor> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation({ 0.0f, 0.0f, -10000.0f, 1.0f });
}

AEndingGameMode::~AEndingGameMode()
{
}

void AEndingGameMode::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}
