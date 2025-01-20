#include "PreCompile.h"
#include "CameraActor.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/TimeEventComponent.h>
#include "EngineCamera.h"

ACameraActor::ACameraActor()
{
	CameraComponent = CreateDefaultSubObject<UEngineCamera>();
	TimeEventComponent = CreateDefaultSubObject<UTimeEventComponent>();

	RootComponent = CameraComponent;
}

ACameraActor::~ACameraActor()
{
	CameraComponent = nullptr;
}

void ACameraActor::BeginPlay()
{
	AActor::BeginPlay();
}

void ACameraActor::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	ScreenPos = UEngineCore::GetMainWindow().GetMousePos();
	FVector ScreenDir = PrevScreenPos - ScreenPos;
	ScreenDir.Normalize();
	PrevScreenPos = ScreenPos;

	if (true == IsFreeCameraValue)
	{
		if (UEngineInput::IsDown('O'))
		{
			switch (CameraComponent->ProjectionType)
			{
			case EProjectionType::Perspective:
				CameraComponent->ProjectionType = EProjectionType::Orthographic;
				break;
			case EProjectionType::Orthographic:
				CameraComponent->ProjectionType = EProjectionType::Perspective;
				break;
			default:
				break;
			}
		}

		float Speed = FreeSpeed;

		if (UEngineInput::IsPress(VK_LSHIFT))
		{
			Speed *= 5.0f;
		}

		if (UEngineInput::IsPress('A'))
		{
			AddActorLocation(-GetActorTransform().GetWorldRight() * _DeltaTime * Speed);
		}

		if (UEngineInput::IsPress('D'))
		{
			AddActorLocation(GetActorTransform().GetWorldRight() * _DeltaTime * Speed);
		}

		if (UEngineInput::IsPress('W'))
		{
			AddActorLocation(GetActorTransform().GetWorldFoward() * _DeltaTime * Speed);
		}

		if (UEngineInput::IsPress('S'))
		{
			AddActorLocation(-GetActorTransform().GetWorldFoward() * _DeltaTime * Speed);
		}

		if (UEngineInput::IsPress('Q'))
		{
			AddActorLocation(GetActorTransform().GetWorldUp() * _DeltaTime * Speed);
		}

		if (UEngineInput::IsPress('E'))
		{
			AddActorLocation(-GetActorTransform().GetWorldUp() * _DeltaTime * Speed);
		}

		if (UEngineInput::IsPress(VK_RBUTTON))
		{
			AddActorRotation({ -ScreenDir.Y * RotSpeed * _DeltaTime, -ScreenDir.X * RotSpeed * _DeltaTime });
		}

		
	}

	CameraComponent->CalculateViewAndProjection();
}

FVector ACameraActor::ScreenPosToWorldPosWithOutPos(FVector _Pos, float _PosZ)
{
	FVector Size = UEngineCore::GetMainWindow().GetWindowSize();

	float4x4 ViewPort;
	ViewPort.ViewPort(Size.X, Size.Y, 0.0f, 0.0f, 0.0f, 1.0f);

	FTransform CameraTransform = GetActorTransform();

	float4x4 ViewMat = CameraTransform.View;
	ViewMat.ArrVector[3] = FVector::ZERO;

	_Pos = _Pos * ViewPort.InverseReturn();
	_Pos = _Pos * CameraTransform.Projection.InverseReturn();
	_Pos = _Pos * ViewMat.InverseReturn();

	float Ratio = Size.X / Size.Y;

	_Pos.Y *= Ratio;

	// -668;

	float FOV = GetCameraComponent()->FOV * 0.5f * UEngineMath::D2R;

	// ³ôÀÌ / ¹Øº¯ 
	FVector ZDisScreenScale;
	ZDisScreenScale.X = tanf(FOV * Ratio) * _PosZ * _Pos.X;
	ZDisScreenScale.Y = tanf(FOV) * _PosZ * _Pos.Y;

	return ZDisScreenScale;
}

FVector ACameraActor::ScreenPosToWorldPos(FVector _Pos)
{
	FVector Size = UEngineCore::GetMainWindow().GetWindowSize();

	float4x4 ViewPort;
	ViewPort.ViewPort(Size.X, Size.Y, 0.0f, 0.0f, 0.0f, 1.0f);

	FTransform CameraTransform = GetActorTransform();

	_Pos = _Pos * ViewPort.InverseReturn();
	_Pos = _Pos * CameraTransform.Projection.InverseReturn();
	_Pos = _Pos * CameraTransform.View.InverseReturn();

	return _Pos;
}

FVector ACameraActor::ScreenMousePosToWorldPosWithOutPos(float _PosZ)
{
	FVector MousePos = UEngineCore::GetMainWindow().GetMousePos();

	return ScreenPosToWorldPosWithOutPos(MousePos, _PosZ);
}

FVector ACameraActor::WorldPosToScreenPos(FVector _Pos)
{
	FVector Size = UEngineCore::GetMainWindow().GetWindowSize();

	float4x4 ViewPort;
	ViewPort.ViewPort(Size.X, Size.Y, 0.0f, 0.0f, 0.0f, 1.0f);

	FTransform CameraTransform = GetActorTransform();

	_Pos = _Pos * CameraTransform.View;
	_Pos = _Pos * CameraTransform.Projection;
	_Pos = _Pos * ViewPort;
	return _Pos;
	//FVector Size = UEngineCore::GetMainWindow().GetWindowSize();

	//float4x4 ViewPort;
	//ViewPort.ViewPort(Size.X, Size.Y, 0.0f, 0.0f, 0.0f, 1.0f);

	//FTransform CameraTransform = GetActorTransform();

	//_Pos = _Pos * CameraTransform.View;

	// // Get projection type and apply appropriate transformations
	//EProjectionType ProjectionType = GetCameraComponent()->GetProjectionType();
	//if (ProjectionType == EProjectionType::Orthographic)
	//{
	//	_Pos = _Pos * CameraTransform.Projection; // Orthographic handling remains the same
	//}
	//else if (ProjectionType == EProjectionType::Perspective)
	//{
	//	// Perspective projection calculations
	//	float Near = GetCameraComponent()->GetNear();
	//	float Far = GetCameraComponent()->GetFar();
	//	float FOV = GetCameraComponent()->GetFOV();

	//	// Perspective projection matrix calculation
	//	float4x4 PerspectiveMatrix;
	//	PerspectiveMatrix.PerspectiveFovDeg(FOV, Size.X, Size.Y, Near, Far);

	//	_Pos = _Pos * PerspectiveMatrix;
	//}

	//_Pos = _Pos * ViewPort;

	//// Perform perspective divide for perspective projection
	//if (ProjectionType == EProjectionType::Perspective)
	//{
	//	_Pos.X /= _Pos.W;
	//	_Pos.Y /= _Pos.W;
	//	_Pos.Z /= _Pos.W;
	//}

	//return _Pos;
}

FVector ACameraActor::ScreenMousePosToWorldPos()
{
	FVector MousePos = UEngineCore::GetMainWindow().GetMousePos();

	return ScreenPosToWorldPos(MousePos);
}

void ACameraActor::FreeCameraOn()
{
	IsFreeCameraValue = true;
	FreeCameraCheck();
}

void ACameraActor::FreeCameraOff()
{
	IsFreeCameraValue = false;
}

void ACameraActor::FreeCameraSwitch()
{
	IsFreeCameraValue = !IsFreeCameraValue;
	FreeCameraCheck();
}

void ACameraActor::Zoom(float _Value, float _Duration)
{
	const FVector TotalOffset = FVector(0.0f, 0.0f, _Value);
	const FVector DeltaOffsetPerSecond = TotalOffset / _Duration;

	TimeEventComponent->AddUpdateEvent(_Duration, [this, DeltaOffsetPerSecond](float DeltaTime, float CurTime)
	{
		FVector DeltaMove = DeltaOffsetPerSecond * DeltaTime;

		this->AddRelativeLocation(DeltaMove);
	},

		false
	);
}

void ACameraActor::MoveCamera(FVector _Pos, float _Duration)
{
	FVector TargetPosition = _Pos;
	float Duration = _Duration;

	TimeEventComponent->AddUpdateEvent(_Duration, [this, TargetPosition, Duration](float DeltaTime, float CurTime)
	{
		auto Lerp = [](FVector A, FVector B, float Alpha)
		{
			return A * (1 - Alpha) + B * Alpha;
		};

		float Alpha = UEngineMath::Clamp(DeltaTime / Duration, 0.0f, 1.0f);
		FVector NewPosition = Lerp(FVector::ZERO, TargetPosition, Alpha);

		AddRelativeLocation(NewPosition);
	},
		false
	);

}

void ACameraActor::FreeCameraCheck()
{
	if (true == IsFreeCameraValue)
	{
		PrevTrans = GetActorTransform();
		PrevProjectionType = GetCameraComponent()->ProjectionType;
		GetCameraComponent()->ProjectionType = EProjectionType::Perspective;
	}
	else
	{
		SetActorTransform(PrevTrans);
		GetCameraComponent()->ProjectionType = PrevProjectionType;
	}
}