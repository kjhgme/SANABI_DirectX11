#pragma once
#include "SceneComponent.h"
#include "EngineSprite.h"
#include "RenderUnit.h"

class UCollision : public USceneComponent
{
public:
	ENGINEAPI UCollision();
	ENGINEAPI ~UCollision();

	UCollision(const UCollision& _Other) = delete;
	UCollision(UCollision&& _Other) noexcept = delete;
	UCollision& operator=(const UCollision& _Other) = delete;
	UCollision& operator=(UCollision&& _Other) noexcept = delete;

	ENGINEAPI void SetCollisionProfileName(std::string_view _ProfileName);
	ENGINEAPI void BeginPlay() override;
	
	std::string GetCollisionProfileName()
	{
		return ProfileName;
	}

	void SetRadius(float _Value);

	ENGINEAPI bool CollisionCheck(std::string_view _OtherName, std::vector<UCollision*>& _Vector);

	void SetCollisionType(ECollisionType _Type)
	{
		CollisionType = _Type;
	}


private:

public:
	ECollisionType CollisionType = ECollisionType::OBB2D;

	std::string ProfileName;
};

