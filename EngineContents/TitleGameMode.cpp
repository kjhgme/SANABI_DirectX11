#include "PreCompile.h"
#include "TitleGameMode.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/CameraActor.h>
#include <EngineCore/EngineCamera.h>
#include <EngineCore/SpriteRenderer.h>
#include "TitleBG.h"
#include "TitleLogo.h"

ATitleGameMode::ATitleGameMode()
{
	{
		TitleLogo = GetWorld()->SpawnActor<ATitleLogo>();
		TitleBG = GetWorld()->SpawnActor<ATitleBG>();
	}

	std::shared_ptr<ACameraActor> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation({ 0.0f, 0.0f, -500.0f, 1.0f });

	Camera->GetCameraComponent()->SetZSort(0, true);
}

ATitleGameMode::~ATitleGameMode()
{
}

void ATitleGameMode::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	if (UEngineInput::IsDown(VK_SPACE))
	{
		UEngineCore::OpenLevel("BossGameLevel");
	}
}