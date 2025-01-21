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
}

FVector ACameraActor::ScreenMousePosToWorldPos()
{
	FVector MousePos = UEngineCore::GetMainWindow().GetMousePos();

	return ScreenPosToWorldPos(MousePos);
}

FVector ACameraActor::ScreenMousePosToWorldPosPerspective(float _ZDis)
{
	FVector MousePos = UEngineCore::GetMainWindow().GetMousePos();

	return ScreenPosToWorldPosPerspective(MousePos, _ZDis);
}

 FVector ACameraActor::ScreenPosToWorldPosPerspective(FVector _Pos, float _ZDis)
{
	 // 화면 크기 가져오기
	 FVector Size = UEngineCore::GetMainWindow().GetWindowSize();

	 // Step 1: 화면 좌표 -> NDC 좌표
	 _Pos.X = (_Pos.X / Size.X) * 2.0f - 1.0f; // X: [0, Size.X] -> [-1, 1]
	 _Pos.Y = 1.0f - (_Pos.Y / Size.Y) * 2.0f; // Y: [0, Size.Y] -> [-1, 1], Y축 반전
	 _Pos.Z = 1.0f; // 클리핑 공간의 Z값은 기본적으로 1.0 (far plane)

	 // 카메라의 Projection 및 View 행렬 가져오기
	 FTransform CameraTransform = GetActorTransform();
	 float4x4 Projection = CameraTransform.Projection;
	 float4x4 View = CameraTransform.View;

	 // Step 2: NDC -> 뷰 공간 (역투영 행렬 사용)
	 float4x4 InvProjection = Projection.InverseReturn();
	 FVector ViewPos = FVector(_Pos.X, _Pos.Y, _Pos.Z, 1.0f) * InvProjection;

	 // Step 3: W 분할 (Perspective 투영)
	 if (ViewPos.W != 0.0f)
	 {
		 ViewPos.X /= ViewPos.W;
		 ViewPos.Y /= ViewPos.W;
		 ViewPos.Z /= ViewPos.W;
	 }

	 // Step 4: 뷰 공간 -> 월드 공간
	 float4x4 InvView = View.InverseReturn();
	 FVector WorldPos = ViewPos * InvView;

	 float ZScale = _ZDis / WorldPos.Z;

	 WorldPos.X *= ZScale;
	 WorldPos.Y *= ZScale;
	 WorldPos.Z = _ZDis;

	 return FVector(WorldPos.X, WorldPos.Y, -2.0f);
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