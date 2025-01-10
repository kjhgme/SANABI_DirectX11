#include "PreCompile.h"
#include "PlayerVfx.h"

#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>

APlayerVfx::APlayerVfx()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	VfxRenderer = CreateDefaultSubObject<USpriteRenderer>();
	VfxRenderer->SetupAttachment(RootComponent);

	{
		VfxRenderer->CreateAnimation("Vfx_NoImage", "Vfx_NoImage", false);
		VfxRenderer->CreateAnimation("Vfx_Jump", "Vfx_Jump", false);
		VfxRenderer->CreateAnimation("Vfx_Landing", "Vfx_Landing", false);
	}

	VfxRenderer->ChangeAnimation("Vfx_NoImage");
}

APlayerVfx::~APlayerVfx()
{
}

void APlayerVfx::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	if (VfxRenderer->IsCurAnimationEnd())
	{
		this->Destroy();
	}
}

void APlayerVfx::InitVfx(std::string_view _AnimName)
{
	VfxRenderer->ChangeAnimation(_AnimName);

}

void APlayerVfx::InitPos(FVector _Pos)
{
	this->SetActorLocation(_Pos);
}
