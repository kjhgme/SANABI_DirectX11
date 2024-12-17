#pragma once
#include <memory>

#include <EngineBase/Object.h>

class UActorComponent : public UObject
{
public:
	UActorComponent();
	~UActorComponent();

	UActorComponent(const UActorComponent& _Other) = delete;
	UActorComponent(UActorComponent&& _Other) noexcept = delete;
	UActorComponent& operator=(const UActorComponent& _Other) = delete;
	UActorComponent& operator=(UActorComponent&& _Other) noexcept = delete;

	std::shared_ptr<class AActor> GetActor();

protected:

private:
	class AActor* Actor;
};

