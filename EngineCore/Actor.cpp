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
		ActorComponent->ComponentTick(_DeltaTime);
	}
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
