#include "PreCompile.h"
#include "BossGameHUD.h"

#include <EngineCore/ImageWidget.h>
#include <EngineCore/FontWidget.h>
#include <EngineCore/CameraActor.h>


ABossGameHUD::ABossGameHUD()
{
}

ABossGameHUD::~ABossGameHUD()
{
}

void ABossGameHUD::BeginPlay()
{
	AHUD::BeginPlay();
	/*
	{
		std::shared_ptr<UFontWidget> Widget = CreateWidget<UFontWidget>(-1);

		Widget->SetWorldLocation({ -10, -10 });
		Widget->SetFont("PFStardust");
		Widget->SetFontSize(24.0f);
		Widget->SetText("�ȳ� �ȳ� �ȳ�");
	}*/
}

void ABossGameHUD::Tick(float _DeltaTime)
{
	AHUD::Tick(_DeltaTime);

	UEngineCore::GetMainWindow().GetMousePos(); 
}

