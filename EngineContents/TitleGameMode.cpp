#include "PreCompile.h"
#include "TitleGameMode.h"

#include <EngineCore/CameraActor.h>
#include <EngineCore/SpriteRenderer.h>
#include "TitleBG.h"
#include "TitleLogo.h"

ATitleGameMode::ATitleGameMode()
{
	{
		TitleBG = GetWorld()->SpawnActor<ATitleBG>();
		TitleLogo = GetWorld()->SpawnActor<ATitleLogo>();
	}

	std::shared_ptr<ACameraActor> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation({ 0.0f, 0.0f, -500.0f, 1.0f });
}

ATitleGameMode::~ATitleGameMode()
{
}

void ATitleGameMode::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

}