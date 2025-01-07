#include "PreCompile.h"
#include "Actor.h"

#include "SceneComponent.h"

AActor::AActor()
{
}

AActor::~AActor()
{
}

void AActor::BeginPlay()
{
	if (nullptr != RootComponent)
	{
		RootComponent->BeginPlay();
	}

	for (std::shared_ptr<class UActorComponent>& ActorComponent : ActorComponentList)
	{
		ActorComponent->BeginPlay();
	}
}

void AActor::Tick(float _DeltaTime)
{
	if (nullptr != RootComponent)
	{
		RootComponent->ComponentTick(_DeltaTime);
	}

	for (std::shared_ptr<class UActorComponent> ActorComponent : ActorComponentList)
	{
		if (false == ActorComponent->IsActive())
		{
			continue;
		}

		ActorComponent->ComponentTick(_DeltaTime);
	}
}

FVector AActor::GetActorUpVector()
{
	if (nullptr == RootComponent)
	{
		return FVector(0.0f, 0.0f, 0.0f, 1.0f);
	}

	return RootComponent->GetTransformRef().World.GetUp();
}

FVector AActor::GetActorRightVector()
{
	if (nullptr == RootComponent)
	{
		return FVector(0.0f, 0.0f, 0.0f, 1.0f);
	}
	return RootComponent->GetTransformRef().World.GetRight();
}

FVector AActor::GetActorForwardVector()
{
	if (nullptr == RootComponent)
	{
		return FVector(0.0f, 0.0f, 0.0f, 1.0f);
	}
	return RootComponent->GetTransformRef().World.GetForward();
}


void AActor::AttachToActor(AActor* _Parent)
{
	if (nullptr == RootComponent)
	{
		MSGASSERT("RootComponent is nullptr.");
		return;
	}

	if (nullptr == _Parent->RootComponent)
	{
		MSGASSERT("_Parent->RootComponent is nullptr.");
		return;
	}

	RootComponent->SetupAttachment(_Parent->RootComponent);
}
