#include "PreCompile.h"
#include "ContentsCore.h"

#include <windows.h>
#include <iostream>

#include <EngineCore/Level.h>
#include <EngineCore/EngineGUI.h>
#include <EngineCore/EngineGUIWindow.h>

#include "TitleGameMode.h"
#include "InGameMode.h"
#include "BossGameMode.h"
#include "EndingGameMode.h"
#include "ContentsEditorGUI.h"

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
	
	UEngineCore::CreateLevel<ATitleGameMode, APawn>("TitleLevel");
	UEngineCore::CreateLevel<AInGameMode, APawn>("InGameLevel");
	UEngineCore::CreateLevel<ABossGameMode, APawn>("BossGameLevel");
	UEngineCore::CreateLevel<AEndingGameMode, APawn>("EndingGameLevel");
	UEngineCore::OpenLevel("BossGameLevel");

	//UEngineGUI::AllWindowOff();
	//
	//UEngineGUI::CreateGUIWindow<UContentsEditorGUI>("ContentsEditorGUI");
	//std::shared_ptr<UContentsEditorGUI> Window = UEngineGUI::FindGUIWindow<UContentsEditorGUI>("ContentsEditorGUI");
	//Window->SetActive(true);
}

void UContentsCore::EngineTick(float _DeltaTime)
{

}

void UContentsCore::EngineEnd()
{
}
