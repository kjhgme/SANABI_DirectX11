#include "PreCompile.h"
#include "TitleLogo.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>

ATitleLogo::ATitleLogo()
{
	//std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	//RootComponent = Default;

	//LogoRenderer = CreateDefaultSubObject<USpriteRenderer>();

	//LogoRenderer->CreateAnimation("Idle", "SNB", 0, 1, 0.1f);
	//{
	//	USpriteRenderer::FrameAnimation* Animation = LogoRenderer->FindAnimation("Idle");
	//	Animation->IsAutoScale = true;
	//	Animation->AutoScaleRatio = 4.0f;
	//}

	//LogoRenderer->CreateAnimation("Move", "SNB", 1, 12, 0.3f);

	////{
	////	USpriteRenderer::FrameAnimation* Animation = LogoRenderer->FindAnimation("Move");
	////	Animation->IsAutoScale = true;
	////	Animation->AutoScaleRatio = 4.0f;
	////}

	//LogoRenderer->ChangeAnimation("Idle");

	//LogoRenderer->SetRelativeScale3D({ 50, 50, 1.0f });
	//LogoRenderer->SetupAttachment(RootComponent);
}

ATitleLogo::~ATitleLogo()
{
}

void ATitleLogo::BeginPlay()
{
	AActor::BeginPlay();
}

void ATitleLogo::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	//if (UEngineInput::IsPress('W'))
	//{
	//	AddRelativeLocation(FVector{ 0.0f, 100.0f * _DeltaTime, 0.0f });
	//}
	//if (UEngineInput::IsPress('A'))
	//{
	//	AddRelativeLocation(FVector{ -100.0f * _DeltaTime, 0.0f, 0.0f });
	//}
	//if (UEngineInput::IsPress('S'))
	//{
	//	AddRelativeLocation(FVector{ 0.0f, -100.0f * _DeltaTime, 0.0f });
	//}
	//if (UEngineInput::IsPress('D'))
	//{
	//	AddRelativeLocation(FVector{ 100.0f * _DeltaTime, 0.0f, 0.0f });
	//}	

	//if (UEngineInput::IsPress('Q'))
	//{
	//	AddActorRotation(FVector{ 0.0f, 0.0f , 360.0f * _DeltaTime });
	//}

	//if (UEngineInput::IsPress('E'))
	//{
	//	LogoRenderer->ChangeAnimation("Move");
	//}
	//if (UEngineInput::IsPress('R'))
	//{
	//}
}