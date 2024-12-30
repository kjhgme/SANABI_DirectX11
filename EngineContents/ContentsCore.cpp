#include "PreCompile.h"
#include "ContentsCore.h"

#include <EngineCore/Level.h>
#include <EngineCore/EngineSprite.h>
#include <EngineCore/EngineTexture.h>

#include "TitleGameMode.h"
#include "InGameMode.h"

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

	LoadFolder("BackGround/PRLG_BG");
	LoadFolder("SNB/SNB_Idle");
	LoadFolder("SNB/SNB_Walking");


	UEngineCore::CreateLevel<ATitleGameMode, APawn>("TitleLevel");
	UEngineCore::CreateLevel<AInGameMode, APawn>("InGameLevel");
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
