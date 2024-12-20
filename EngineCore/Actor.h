#pragma once
#include "SceneComponent.h"

class AActor : public UObject
{
	friend class ULevel;

public:
	ENGINEAPI AActor();
	ENGINEAPI ~AActor();

	AActor(const AActor& _Other) = delete;
	AActor(AActor&& _Other) noexcept = delete;
	AActor& operator=(const AActor& _Other) = delete;
	AActor& operator=(AActor&& _Other) noexcept = delete;

	ENGINEAPI virtual void BeginPlay();
	ENGINEAPI virtual void Tick(float _DeltaTime);

	virtual void LevelChangeStart() {}
	virtual void LevelChangeEnd() {}

	template<typename ComponentType>
	inline std::shared_ptr<ComponentType> CreateDefaultSubObject()
	{
		static_assert(std::is_base_of_v<UActorComponent, ComponentType>, "ActorComponent is not inherited.");

		if (false == std::is_base_of_v<UActorComponent, ComponentType>)
		{
			MSGASSERT("ActorComponent is not inherited.");
			return nullptr;
		}

		char* ComMemory = new char[sizeof(ComponentType)];

		UActorComponent* ComPtr = reinterpret_cast<ComponentType*>(ComMemory);
		ComPtr->Actor = this;

		ComponentType* NewPtr = reinterpret_cast<ComponentType*>(ComMemory);

		std::shared_ptr<ComponentType> NewCom(new(ComMemory) ComponentType());

		if (std::is_base_of_v<USceneComponent, ComponentType>)
		{
			if (nullptr != RootComponent)
			{
				MSGASSERT("RootComponent is not nullptr.");
			}

			RootComponent = NewCom;
		}
		else if (std::is_base_of_v<UActorComponent, ComponentType>)
		{
			ActorComponentList.push_back(NewCom);
		}
		else
		{
			MSGASSERT("Error.");
		}

		return NewCom;
	}

	// GetFunction
	ULevel* GetWorld()
	{
		return World;
	}

	// SetFunction
	void SetActorLocation(const FVector& _Value)
	{
		if (nullptr == RootComponent)
		{
			return;
		}

		RootComponent->SetLocation(_Value);
	}

	void SetActorRelativeScale3D(const FVector& _Scale)
	{
		if (nullptr == RootComponent)
		{
			return;
		}

		RootComponent->SetRelativeScale3D(_Scale);
	}

	// Function
	void AddActorLocation(const FVector& _Value)
	{
		if (nullptr == RootComponent)
		{
			return;
		}

		RootComponent->AddLocation(_Value);
	}

protected:

private:
	ULevel* World;

	std::shared_ptr<class USceneComponent> RootComponent = nullptr;

	std::list<std::shared_ptr<class UActorComponent>> ActorComponentList;
};

