#include "PreCompile.h"
#include "Level.h"

#include "Actor.h"
#include "Renderer.h"
#include "Collision.h"
#include "EngineCore.h"
#include "CameraActor.h"
#include "EngineCamera.h"

ULevel::ULevel()
{
	SpawnCamera(0);

	//D3D11_VIEWPORT ViewPortInfo;

	//ViewPortInfo.Width = UEngineCore::GetScreenScale().X;
	//ViewPortInfo.Height = UEngineCore::GetScreenScale().Y;
	//ViewPortInfo.TopLeftX = 0.0f;
	//ViewPortInfo.TopLeftY = 0.0f;
	//ViewPortInfo.MinDepth = 0.0f;
	//ViewPortInfo.MaxDepth = 1.0f;

	//UEngineCore::GetDevice().GetContext()->RSSetViewports(1, &ViewPortInfo);
}

ULevel::~ULevel()
{
	BeginPlayList.clear();
	AllActorList.clear();
	Cameras.clear();
}

void ULevel::LevelChangeStart()
{

}

void ULevel::LevelChangeEnd()
{

}

void ULevel::Tick(float _DeltaTime)
{
	std::list<std::shared_ptr<class AActor>>::iterator StartIter = BeginPlayList.begin();
	std::list<std::shared_ptr<class AActor>>::iterator EndIter = BeginPlayList.end();
	
	for ( ; StartIter != EndIter; )
	{
		std::shared_ptr<AActor> CurActor = *StartIter;

		if (false == CurActor->IsActive())
		{
			++StartIter;
			continue;
		}

		StartIter = BeginPlayList.erase(StartIter);

		CurActor->BeginPlay();
		AllActorList.push_back(CurActor);
	}
		
	for (std::shared_ptr<AActor> CurActor : AllActorList)
	{
		if (false == CurActor->IsActive())
		{
			continue;
		}

		CurActor->Tick(_DeltaTime);
	}
}

void ULevel::Render(float _DeltaTime)
{
	UEngineCore::GetDevice().RenderStart();

	for (std::pair<const int, std::shared_ptr<ACameraActor>>& Camera : Cameras)
	{
		Camera.second->Tick(_DeltaTime);
		Camera.second->GetCameraComponent()->Render(_DeltaTime);
	}

	UEngineCore::GetDevice().RenderEnd();
}

std::shared_ptr<class ACameraActor> ULevel::SpawnCamera(int _Order)
{
	std::shared_ptr<ACameraActor> Camera = std::make_shared<ACameraActor>();

	if (true == Cameras.contains(_Order))
	{
		MSGASSERT("Camera is already exists.");
	}

	Camera->BeginPlay();

	Cameras.insert({ _Order , Camera });
	return Camera;
}

void ULevel::ChangeRenderGroup(int _CameraOrder, int _PrevGroupOrder, std::shared_ptr<URenderer> _Renderer)
{
	if (false == Cameras.contains(_CameraOrder))
	{
		MSGASSERT("Camera is not exists.");
		return;
	}
	std::shared_ptr<ACameraActor> Camera = Cameras[_CameraOrder];

	Camera->GetCameraComponent()->ChangeRenderGroup(_PrevGroupOrder, _Renderer);
}

void ULevel::ChangeCollisionProfileName(std::string_view _ProfileName, std::string_view _PrevProfileName, std::shared_ptr<class UCollision> _Collision)
{
	if (false == Collisions.contains(_ProfileName))
	{
		MSGASSERT(std::string(_ProfileName) + " is not Collision Group.");
		return;
	}

	if (_PrevProfileName != "")
	{
		std::list<std::shared_ptr<UCollision>>& PrevCollisionGroup = Collisions[_PrevProfileName];
		PrevCollisionGroup.remove(_Collision);
	}

	std::list<std::shared_ptr<UCollision>>& CollisionGroup = Collisions[_ProfileName];
	CollisionGroup.push_back(_Collision);
}

void ULevel::CreateCollisionProfile(std::string_view _ProfileName)
{
	Collisions[_ProfileName];
}

void ULevel::Release(float _DeltaTime)
{
	for (std::pair<const int, std::shared_ptr<ACameraActor>>& Camera : Cameras)
	{
		Camera.second->GetCameraComponent()->Release(_DeltaTime);
	}

	{
		for (std::pair<const std::string_view, std::list<std::shared_ptr<UCollision>>>& Group : Collisions)
		{
			std::list<std::shared_ptr<UCollision>>& List = Group.second;

			std::list<std::shared_ptr<UCollision>>::iterator StartIter = List.begin();
			std::list<std::shared_ptr<UCollision>>::iterator EndIter = List.end();

			for (; StartIter != EndIter; )
			{
				if (false == (*StartIter)->IsDestroy())
				{
					++StartIter;
					continue;
				}

				StartIter = List.erase(StartIter);
			}
		}
	}

	{
		std::list<std::shared_ptr<AActor>>& List = AllActorList;

		std::list<std::shared_ptr<AActor>>::iterator StartIter = List.begin();
		std::list<std::shared_ptr<AActor>>::iterator EndIter = List.end();

		for (; StartIter != EndIter; )
		{
			if (false == (*StartIter)->IsDestroy())
			{
				++StartIter;
				continue;
			}

			StartIter = List.erase(StartIter);
		}
	}
}