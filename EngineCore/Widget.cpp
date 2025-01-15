#include "PreCompile.h"
#include "Widget.h"

#include <EnginePlatform/EngineInput.h>
#include "HUD.h"
#include "RenderUnit.h"
#include "CameraActor.h"
#include "EngineCamera.h"
#include "EngineSprite.h"

UWidget::UWidget()
{	
}

UWidget::~UWidget()
{
}

void UWidget::Tick(float _DeltaTime)
{
	std::shared_ptr<class ACameraActor> CameraActor = GetWorld()->GetCamera(EEngineCameraType::UICamera);

	FVector WorldPos = CameraActor->ScreenMousePosToWorldPos();
	FTransform Transform;
	Transform.WorldLocation = WorldPos;

	if (true == FTransform::PointToRect(Transform, GetTransformRef()))
	{
		if (nullptr != Hover)
		{
			Hover();
		}

		if (true == UEngineInput::IsDown(VK_LBUTTON))
		{
			if (nullptr != Down)
			{
				Down();
			}
		}

		if (true == UEngineInput::IsUp(VK_LBUTTON))
		{
			if (nullptr != Up)
			{
				Up();
			}
		}
	};
}

void UWidget::Render(UEngineCamera* Camera, float _DeltaTime)
{	
}

ULevel* UWidget::GetWorld()
{
	return HUD->GetWorld();
}