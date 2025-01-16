#include "PreCompile.h"
#include "ContentsCore.h"

#include <EngineCore/EngineTexture.h>
#include <EngineCore/EngineSprite.h>

void UContentsCore::InitResources()
{
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
	// UI
	{
		LoadFolder("UI/TextUI");
		LoadFolder("UI/TextUI/BubbleSelectionMarker");
	}
	// Title
	{
		LoadFolder("Title");
	}
	// PRLG
	{
		LoadFolder("PRLG/PRLG_TileSet");
	}
	// BOSS
	{
		// Body
		{
			LoadFolder("BOSS/BossPlatform/BossPlatform_A_Idle");
			LoadFolder("BOSS/BossPlatform/BossPlatform_A_BoosterLoop");
			LoadFolder("BOSS/Boss_Slap");
			LoadFolder("BOSS/Boss_Body_Idle");
		}
		// Wing
		{
			LoadFolder("BOSS/Boss_Wing_NoImage");
			LoadFolder("BOSS/Boss_Wing_Neu_Idle");
		}
	}
	// Ending
	{
		LoadFolder("Ending/BadEnding");
	}
	// BackGround
	{
		LoadFolder("BackGround/PRLG_BG");
		LoadFolder("BackGround/BOSS_BG");
	}
	// SNB
	{
		// Base
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
			LoadFolder("SNB/SNB_Death");
		}
		//SNB Arm
		{
			LoadFolder("SNB/SNB_Arm_NoImage");
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
		// BossAnimation
		{
			LoadFolder("SNB/BossStage/SNB_Boss_001_TrainOnLoop");
			LoadFolder("SNB/BossStage/SNB_Boss_002_TrainOn2Idle");
			LoadFolder("SNB/BossStage/SNB_Boss_004_LookBackgroundStart");
			LoadFolder("SNB/BossStage/SNB_Boss_005_LookBackgroundLoop");
			LoadFolder("SNB/BossStage/SNB_Boss_006_LookBackgroundEnd");
		}
	}
	// Mari
	{
		// BossAnimation
		{
			LoadFolder("Mari/BossStage/Mufin_NoImage");
			LoadFolder("Mari/BossStage/001_TrainOnHarmonicaPlay");
			LoadFolder("Mari/BossStage/002_TrainOnHarmonicaPlayEndLoop");
			LoadFolder("Mari/BossStage/003_TrainOnHarmonicaEnd");
			LoadFolder("Mari/BossStage/004_TrainOnLoop");
			LoadFolder("Mari/BossStage/005_TrainOnMindBreakStart");
			LoadFolder("Mari/BossStage/006_TrainOnMindBreakLoop");
			LoadFolder("Mari/BossStage/007_TrainOnMindBreakEnd");
			LoadFolder("Mari/BossStage/009_TrainOn2Idle");
			LoadFolder("Mari/BossStage/010_LookBackgroundStart");
			LoadFolder("Mari/BossStage/011_LookBackgroundLoop");
			LoadFolder("Mari/BossStage/012_LookBackgroundEnd");
			LoadFolder("Mari/BossStage/013_Idle");
			LoadFolder("Mari/BossStage/014_AltDroneCloakEnd");
			LoadFolder("Mari/BossStage/015_AltDroneRideStart");
			LoadFolder("Mari/BossStage/016_AltDroneRideCloakStart");
		}
	}
	// Vfx
	{
		LoadFolder("Vfx/Vfx_NoImage");
		LoadFolder("Vfx/Vfx_Jump");
		LoadFolder("Vfx/Vfx_Landing");
	}
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

	int result = AddFontResourceA(Dir.GetPathToString().c_str());

	if (result != 0) {
		PostMessage(HWND_BROADCAST, WM_FONTCHANGE, 0, 0);
		return true;
	}
	else {
		std::cerr << "폰트 설치 실패: " << _Font << std::endl;
		return false;
	}
}

bool UContentsCore::RemoveFont(std::string_view _Font)
{
	UEngineDirectory Dir;
	if (false == Dir.MoveParentToDirectory("Resources/Font"))
	{
		MSGASSERT("Wrong Directory.");
		return false;
	}
	Dir.Append(_Font);

	int result = RemoveFontResourceA(Dir.GetPathToString().c_str());
	if (result != 0) {
		PostMessage(HWND_BROADCAST, WM_FONTCHANGE, 0, 0);
		return true;
	}
	else {
		return false;
	}
}