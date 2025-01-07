#include "PreCompile.h"
#include "Collision.h"
#include <EngineBase/EngineString.h>
#include <EngineCore/EngineCamera.h>

UCollision::UCollision()
{
}

UCollision::~UCollision()
{

}

void UCollision::SetCollisionProfileName(std::string_view _ProfileName)
{
	if (_ProfileName == GetCollisionProfileName())
	{
		return;
	}

	std::string PrevProfileName = GetCollisionProfileName();
	ProfileName = _ProfileName;
	ULevel* Level = GetActor()->GetWorld();

	std::shared_ptr<UCollision> ThisPtr = GetThis<UCollision>();
	Level->ChangeCollisionProfileName(ProfileName, PrevProfileName, ThisPtr);
}

bool UCollision::CollisionCheck(std::string_view _OtherName, std::vector<UCollision*>& _Vector)
{
	std::map<std::string_view, std::list<std::shared_ptr<class UCollision>>>& Collision = GetWorld()->Collisions;

	if (false == Collision.contains(_OtherName))
	{
		MSGASSERT(std::string(_OtherName) + " is not collision group's noame");
		return false;
	}

	std::list<std::shared_ptr<class UCollision>>& Group = Collision[_OtherName];

	for (std::shared_ptr<class UCollision>& OtherCol : Group)
	{
		if (false == OtherCol->IsActive())
		{
			continue;
		}

		if (true == FTransform::Collision(CollisionType, Transform, OtherCol->CollisionType, OtherCol->Transform))
		{
			_Vector.push_back(OtherCol.get());
		}
	}

	return 0 != _Vector.size();
}


void UCollision::BeginPlay()
{
	USceneComponent::BeginPlay();
}

void UCollision::SetRadius(float _Value)
{
	FVector Scale = GetWorldScale3D();
	Scale.X = _Value * 2.0f;
	SetScale3D(Scale);
}