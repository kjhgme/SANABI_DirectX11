#pragma once
#include "Actor.h"
#include "EngineEnums.h"

class ACameraActor : public AActor
{
public:
	ACameraActor();
	~ACameraActor();

	ACameraActor(const ACameraActor& _Other) = delete;
	ACameraActor(ACameraActor&& _Other) noexcept = delete;
	ACameraActor& operator=(const ACameraActor& _Other) = delete;
	ACameraActor& operator=(ACameraActor&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	ENGINEAPI std::shared_ptr<class UEngineCamera> GetCameraComponent()
	{
		return CameraComponent;
	}

	ENGINEAPI FVector ScreenMousePosToWorldPos();
	ENGINEAPI FVector ScreenMousePosToWorldPosWithOutPos();
	
	ENGINEAPI inline bool IsFreeCamera()
	{
		return IsFreeCameraValue;
	}

	ENGINEAPI void FreeCameraOn();

	ENGINEAPI void FreeCameraOff();

	ENGINEAPI void FreeCameraSwitch();
	
	void SetFreeCameraSpeed(float _Speed)
	{
		FreeSpeed = _Speed;
	}

	ENGINEAPI void Zoom(float _Value, float _Duration);
	
protected:

private:
	std::shared_ptr<class UEngineCamera> CameraComponent = nullptr;
	std::shared_ptr<class UTimeEventComponent> TimeEventComponent;

	bool IsFreeCameraValue = false;
	ENGINEAPI void FreeCameraCheck();

	FTransform PrevTrans;
	EProjectionType PrevProjectionType = EProjectionType::Orthographic;
	float FreeSpeed = 500.0f;

	FVector ScreenPos;
	FVector PrevScreenPos;
	float RotSpeed = 360.0f;
};

