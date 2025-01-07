#include "PreCompile.h"
#include "ActorComponent.h"

#include "Actor.h"

UActorComponent::UActorComponent()
{
}

UActorComponent::~UActorComponent()
{
}

AActor* UActorComponent::GetActor()
{
	return Actor;
}

ULevel* UActorComponent::GetWorld()
{
	return Actor->GetWorld();
}

bool UActorComponent::IsActive()
{
	if (nullptr == GetActor())
	{
		MSGASSERT("Actor is nullptr.");
		return false;
	}

	return UObject::IsActive() && GetActor()->IsActive();
}

bool UActorComponent::IsDestroy()
{
	return UObject::IsDestroy() || GetActor()->IsDestroy();
}