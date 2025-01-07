#pragma once
#include <EngineBase/Object.h>
#include <EngineBase/EngineDebug.h>

class ULevel : public UObject
{
	friend class UCollision;

public:
	ENGINEAPI ULevel();
	ENGINEAPI ~ULevel();

	ULevel(const ULevel& _Other) = delete;
	ULevel(ULevel&& _Other) noexcept = delete;
	ULevel& operator=(const ULevel& _Other) = delete;
	ULevel& operator=(ULevel&& _Other) noexcept = delete;

	void LevelChangeStart();
	void LevelChangeEnd();

	void Tick(float _DeltaTime);
	void Render(float _DeltaTime);
	void Collision(float _DeltaTime);
	void Release(float _DeltaTime);

	// GetFunction
	std::shared_ptr<class ACameraActor> GetMainCamera()
	{
		return GetCamera(0);
	}

	std::shared_ptr<class ACameraActor> GetCamera(int _Order)
	{
		if (false == Cameras.contains(_Order))
		{
			MSGASSERT(_Order + " Camera is not exists.");
		}

		return Cameras[_Order];
	}

	template<typename EnumType>
	std::shared_ptr<class ACameraActor> SpawnCamera(EnumType _Order)
	{
		return SpawnCamera(static_cast<int>(_Order));
	}

	std::shared_ptr<class ACameraActor> SpawnCamera(int _Order);


	template<typename ActorType>
	std::shared_ptr<ActorType> SpawnActor()
	{
		static_assert(std::is_base_of_v<AActor, ActorType>, "Actor is not inherited.");

		if (false == std::is_base_of_v<AActor, ActorType>)
		{
			MSGASSERT("Actor is not inherited.");
			return nullptr;
		}

		char* ActorMemory = new char[sizeof(ActorType)];


		AActor* ActorPtr = reinterpret_cast<ActorType*>(ActorMemory);
		ActorPtr->World = this;

		ActorType* NewPtr = reinterpret_cast<ActorType*>(ActorMemory);

		std::shared_ptr<ActorType> NewActor(NewPtr = new(ActorMemory) ActorType());

		BeginPlayList.push_back(NewActor);

		return NewActor;
	}

	ENGINEAPI void ChangeRenderGroup(int _CameraOrder, int _PrevGroupOrder, std::shared_ptr<class URenderer> _Renderer);
	ENGINEAPI void ChangeCollisionProfileName(std::string_view _ProfileName, std::string_view _PrevProfileName, std::shared_ptr<class UCollision> _Collision);
	ENGINEAPI void CreateCollisionProfile(std::string_view _ProfileName);
	ENGINEAPI void PushCollisionProfileEvent(std::shared_ptr<class URenderer> _Renderer);
	ENGINEAPI void LinkCollisionProfile(std::string_view _LeftProfileName, std::string_view _RightProfileName);

protected:

private:
	std::list<std::shared_ptr<class AActor>> BeginPlayList;
	std::list<std::shared_ptr<class AActor>> AllActorList;
	std::map<int, std::shared_ptr<class ACameraActor>> Cameras;
	std::map<std::string_view, std::list<std::shared_ptr<class UCollision>>> Collisions;
	std::map<std::string, std::list<std::shared_ptr<class UCollision>>> CheckCollisions;
	std::map<std::string, std::list<std::string>> CollisionLinks;
};

