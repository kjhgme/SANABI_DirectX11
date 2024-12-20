#pragma once
#include "ActorComponent.h"

class USceneComponent : public UActorComponent
{
public:
	USceneComponent();
	~USceneComponent();

	USceneComponent(const USceneComponent& _Other) = delete;
	USceneComponent(USceneComponent&& _Other) noexcept = delete;
	USceneComponent& operator=(const USceneComponent& _Other) = delete;
	USceneComponent& operator=(USceneComponent&& _Other) noexcept = delete;

	// GetFunction
	FTransform& GetTransformRef()
	{
		return Transform;
	}
	
	// SetFunction
	void SetRelativeScale3D(const FVector& _Scale)
	{
		Transform.Scale = _Scale;
		Transform.TransformUpdate();
	}

	void SetLocation(const FVector& _Value)
	{
		Transform.Location = _Value;
		Transform.TransformUpdate();
	}

	// Function
	void AddLocation(const FVector& _Value)
	{
		Transform.Location += _Value;
		Transform.TransformUpdate();
	}

protected:
	FTransform Transform;

private:

	USceneComponent* Parent;
	std::list<std::shared_ptr<USceneComponent>> Childs;
};

