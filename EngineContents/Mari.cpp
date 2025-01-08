#include "PreCompile.h"
#include "Mari.h"
#include "ContentsEnum.h"

#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>

AMari::AMari()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	MariRenderer = CreateDefaultSubObject<USpriteRenderer>();
	InitMariAnimation();

	MariRenderer->ChangeAnimation("001_TrainOnHarmonicaPlay");
	MariRenderer->AddRelativeLocation({ 0.0f, 0.0f, static_cast<float>(ERenderOrder::PLAYER) - 1 });

	MariRenderer->SetupAttachment(RootComponent);
}

AMari::~AMari()
{
}

void AMari::InitMariAnimation()
{
	MariRenderer->CreateAnimation("001_TrainOnHarmonicaPlay", "001_TrainOnHarmonicaPlay", false, 2.0f);
	MariRenderer->CreateAnimation("002_TrainOnHarmonicaPlayEndLoop", "002_TrainOnHarmonicaPlayEndLoop");
	MariRenderer->CreateAnimation("003_TrainOnHarmonicaEnd", "003_TrainOnHarmonicaEnd", false, 1.0f);
	MariRenderer->CreateAnimation("004_TrainOnLoop", "004_TrainOnLoop");
	MariRenderer->CreateAnimation("005_TrainOnMindBreakStart", "005_TrainOnMindBreakStart", false);
	MariRenderer->CreateAnimation("006_TrainOnMindBreakLoop", "006_TrainOnMindBreakLoop");
	MariRenderer->CreateAnimation("007_TrainOnMindBreakEnd", "007_TrainOnMindBreakEnd", false);
	MariRenderer->CreateAnimation("008_TrainOnLoop", "004_TrainOnLoop");
	MariRenderer->CreateAnimation("009_TrainOn2Idle", "009_TrainOn2Idle", false);
	MariRenderer->CreateAnimation("010_LookBackgroundStart", "010_LookBackgroundStart", false);
	MariRenderer->CreateAnimation("011_LookBackgroundLoop", "011_LookBackgroundLoop");
	MariRenderer->CreateAnimation("012_LookBackgroundEnd", "012_LookBackgroundEnd", false);
	MariRenderer->CreateAnimation("013_Idle", "013_Idle");
	MariRenderer->CreateAnimation("014_AltDroneCloakEnd", "014_AltDroneCloakEnd", false);
	MariRenderer->CreateAnimation("015_AltDroneRideStart", "015_AltDroneRideStart", false);
	MariRenderer->CreateAnimation("016_AltDroneRideCloakStart", "016_AltDroneRideCloakStart", false);

	AnimQueue.push("001_TrainOnHarmonicaPlay");
	AnimQueue.push("002_TrainOnHarmonicaPlayEndLoop");
	AnimQueue.push("003_TrainOnHarmonicaEnd");
	AnimQueue.push("004_TrainOnLoop");
	AnimQueue.push("005_TrainOnMindBreakStart");
	AnimQueue.push("006_TrainOnMindBreakLoop");
	AnimQueue.push("007_TrainOnMindBreakEnd");
	AnimQueue.push("008_TrainOnLoop");
	AnimQueue.push("009_TrainOn2Idle");
	AnimQueue.push("010_LookBackgroundStart");
	AnimQueue.push("011_LookBackgroundLoop");
	AnimQueue.push("012_LookBackgroundEnd");
	AnimQueue.push("013_Idle");
	AnimQueue.push("014_AltDroneCloakEnd");
	AnimQueue.push("015_AltDroneRideStart");
	AnimQueue.push("016_AltDroneRideCloakStart");
}

void AMari::SetAnimation(std::string_view _Anim)
{	
	MariRenderer->ChangeAnimation(_Anim);
}

void AMari::ChangeToNextAnim()
{
	if (!AnimQueue.empty())
	{
		std::string nextAnim = AnimQueue.front();
		AnimQueue.pop();

		MariRenderer->ChangeAnimation(nextAnim);
	}
}
