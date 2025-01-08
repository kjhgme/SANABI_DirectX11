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
	MariRenderer->AddRelativeLocation({ 0.0f, 0.0f, static_cast<float>(ERenderOrder::PLAYER) });

	MariRenderer->SetupAttachment(RootComponent);
}

AMari::~AMari()
{
}

void AMari::InitMariAnimation()
{
	MariRenderer->CreateAnimation("001_TrainOnHarmonicaPlay", "001_TrainOnHarmonicaPlay", false);
	MariRenderer->CreateAnimation("002_TrainOnHarmonicaPlayEndLoop", "002_TrainOnHarmonicaPlayEndLoop");
	MariRenderer->CreateAnimation("003_TrainOnHarmonicaEnd", "003_TrainOnHarmonicaEnd");
	MariRenderer->CreateAnimation("004_TrainOnLoop", "004_TrainOnLoop");
	MariRenderer->CreateAnimation("005_TrainOnMindBreakStart", "005_TrainOnMindBreakStart");
	MariRenderer->CreateAnimation("006_TrainOnMindBreakLoop", "006_TrainOnMindBreakLoop");
	MariRenderer->CreateAnimation("007_TrainOnMindBreakEnd", "007_TrainOnMindBreakEnd");
	MariRenderer->CreateAnimation("009_TrainOn2Idle", "009_TrainOn2Idle");
	MariRenderer->CreateAnimation("010_LookBackgroundStart", "010_LookBackgroundStart");
	MariRenderer->CreateAnimation("011_LookBackgroundLoop", "011_LookBackgroundLoop");
	MariRenderer->CreateAnimation("012_LookBackgroundEnd", "012_LookBackgroundEnd");
	MariRenderer->CreateAnimation("013_Idle", "013_Idle");
	MariRenderer->CreateAnimation("014_AltDroneCloakEnd", "014_AltDroneCloakEnd");
	MariRenderer->CreateAnimation("015_AltDroneRideStart", "015_AltDroneRideStart");
	MariRenderer->CreateAnimation("016_AltDroneRideCloakStart", "016_AltDroneRideCloakStart");
}
