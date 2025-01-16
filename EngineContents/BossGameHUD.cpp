#include "PreCompile.h"
#include "BossGameHUD.h"

#include <EngineCore/ImageWidget.h>
#include <EngineCore/FontWidget.h>

ABossGameHUD::ABossGameHUD()
{
}

ABossGameHUD::~ABossGameHUD()
{
}

void ABossGameHUD::BeginPlay()
{
	AHUD::BeginPlay();
	
	//{
	//	std::shared_ptr<UFontWidget> Widget = CreateWidget<UFontWidget>(-1);

	//	Widget->SetWorldLocation({ -10, -10 });
	//	Widget->SetFont("±Ã¼­");
	//	// Widget->SetFont("PFSdust");
	//	Widget->SetFontSize(50.0f);
	//	Widget->SetText("¾È³ç ¾È³ç ¾È³ç");
	//}
}

void ABossGameHUD::Tick(float _DeltaTime)
{
	AHUD::Tick(_DeltaTime);
}

