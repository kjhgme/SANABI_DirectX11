#include "PreCompile.h"
#include "ContentsCore.h"

#include <windows.h>
#include <iostream>

#include <EngineCore/HUD.h>
#include <EngineCore/Level.h>
#include <EngineCore/EngineGUI.h>
#include <EngineCore/EngineGUIWindow.h>

#include "MapMakerMode.h"
#include "TitleGameMode.h"
#include "InGameMode.h"
#include "BossGameMode.h"
#include "EndingGameMode.h"
#include "ContentsEditorGUI.h"
#include "BossGameHUD.h"
#include "TitlePlayer.h"
#include "Player.h"

CreateContentsCoreDefine(UContentsCore);

UContentsCore::UContentsCore()
{
	// Font ¼³Ä¡
	{
		std::string Font = "PFStardust.ttf";

		InstallFont(Font);
	}
}

UContentsCore::~UContentsCore()
{
	RemoveFont("PFStardust.ttf");
}


void UContentsCore::EngineStart(UEngineInitData& _Data)
{
	_Data.WindowPos = { 100, 100 };
	_Data.WindowSize = { 1280, 720 };

	InitResources();

	UEngineCore::CreateLevel<ATitleGameMode, ATitlePlayer, AHUD>("TitleLevel");
	UEngineCore::CreateLevel<AInGameMode, APawn, AHUD>("InGameLevel");
	UEngineCore::CreateLevel<ABossGameMode, APlayer, ABossGameHUD>("BossGameLevel");
	UEngineCore::CreateLevel<AEndingGameMode, APawn, AHUD>("EndingGameLevel");

	UEngineCore::CreateLevel<AMapMakerMode, APawn, AHUD>("MapMakerEditor");

	UEngineCore::OpenLevel("TitleLevel");

	// UEngineGUI::AllWindowOff();
}

void UContentsCore::EngineTick(float _DeltaTime)
{

}

void UContentsCore::EngineEnd()
{
}
