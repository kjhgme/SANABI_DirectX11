#include "PreCompile.h"
#include "ContentsCore.h"

#include <windows.h>
#include <iostream>

#include <EngineCore/Level.h>
#include <EngineCore/EngineSprite.h>
#include <EngineCore/EngineTexture.h>

#include "TitleGameMode.h"
#include "InGameMode.h"
#include "EndingGameMode.h"

CreateContentsCoreDefine(UContentsCore);

UContentsCore::UContentsCore()
{
}

UContentsCore::~UContentsCore()
{
}


void UContentsCore::EngineStart(UEngineInitData& _Data)
{
	_Data.WindowPos = { 100, 100 };
	_Data.WindowSize = { 1280, 720 };

	{
		UEngineDirectory Dir;
		if (false == Dir.MoveParentToDirectory("Resources"))
		{
			MSGASSERT("Wrong Directory.");
			return;
		}
		Dir.Append("Image");
	 
		 std::vector<UEngineFile> ImageFiles = Dir.GetAllFile(true, { ".PNG", ".BMP", ".JPG" });
		 for (size_t i = 0; i < ImageFiles.size(); i++)
		 {
		 	std::string FilePath = ImageFiles[i].GetPathToString();
		 	UEngineTexture::Load(FilePath);
		 }
	}
	// Title
	{
		LoadFolder("Title");
	}
	// Ending
	{
		LoadFolder("Ending/BadEnding");
	}
	// BackGround
	{
		LoadFolder("BackGround/PRLG_BG");
	}
	// SNB
	{
		LoadFolder("SNB/SNB_Idle");
		LoadFolder("SNB/SNB_Walking");
		LoadFolder("SNB/SNB_RunStart");
		LoadFolder("SNB/SNB_Running");
		LoadFolder("SNB/SNB_RunStop");
		LoadFolder("SNB/SNB_Jumping");
		LoadFolder("SNB/SNB_FallStart");
		LoadFolder("SNB/SNB_Falling");
		LoadFolder("SNB/SNB_Landing");
		LoadFolder("SNB/SNB_Land2Run");
		LoadFolder("SNB/SNB_Swing");
		LoadFolder("SNB/SNB_SwingJump");
		LoadFolder("SNB/SNB_SwingJumpUp");
	}
	//SNB Arm
	{
		LoadFolder("SNB/SNB_Arm_Idle");
		LoadFolder("SNB/SNB_Arm_Walking");
		LoadFolder("SNB/SNB_Arm_RunStart");
		LoadFolder("SNB/SNB_Arm_Running");
		LoadFolder("SNB/SNB_Arm_RunStop");
		LoadFolder("SNB/SNB_Arm_Jumping");
		LoadFolder("SNB/SNB_Arm_FallStart");
		LoadFolder("SNB/SNB_Arm_Falling");
		LoadFolder("SNB/SNB_Arm_Landing");
		LoadFolder("SNB/SNB_Arm_Land2Run");
		LoadFolder("SNB/SNB_Arm_SwingJump");
		LoadFolder("SNB/SNB_Arm_SwingJumpUp");
	}

	// Font 설치
	{
		std::string Font = "PFStardust.ttf";

		InstallFont(Font);
	}

	UEngineCore::CreateLevel<ATitleGameMode, APawn>("TitleLevel");
	UEngineCore::CreateLevel<AInGameMode, APawn>("InGameLevel");
	UEngineCore::CreateLevel<AEndingGameMode, APawn>("EndingGameLevel");
	UEngineCore::OpenLevel("InGameLevel");
}

void UContentsCore::EngineTick(float _DeltaTime)
{

}

void UContentsCore::EngineEnd()
{

}

void UContentsCore::LoadFolder(std::string_view _Path)
{	
	UEngineDirectory Dir;
	if (false == Dir.MoveParentToDirectory("Resources/Image"))
	{
		MSGASSERT("Wrong Directory.");
		return;
	}
	Dir.Append(_Path);

	UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());	
}

bool UContentsCore::InstallFont(std::string_view _Font)
{
	UEngineDirectory Dir;
	if (false == Dir.MoveParentToDirectory("Resources/Font"))
	{
		MSGASSERT("Wrong Directory.");
		return false;
	}
	Dir.Append(_Font);

	int result = AddFontResourceEx(Dir.GetPathToString().c_str(), FR_PRIVATE, nullptr);

	if (result > 0) {
		SendMessage(HWND_BROADCAST, WM_FONTCHANGE, 0, 0);
		return true;
	}
	else {
		std::cerr << "폰트 설치 실패: " << _Font << std::endl;
		return false;
	}
}