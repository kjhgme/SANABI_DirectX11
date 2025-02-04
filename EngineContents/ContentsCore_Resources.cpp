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
		LoadFolder("UI/Aim_Idle");
		LoadFolder("UI/Aimming");
		LoadFolder("UI/AimStart");
		LoadFolder("UI/GrabIcon_AttackGrab");
		LoadFolder("UI/Grablcon_Grab");

		// HP
		LoadFolder("UI/HP/HP4_1_Damaged");
		LoadFolder("UI/HP/HP4_1_Idle");
		LoadFolder("UI/HP/HP4_2_Damaged");
		LoadFolder("UI/HP/HP4_2_Disapear");
		LoadFolder("UI/HP/HP4_2_Idle");
		LoadFolder("UI/HP/HP4_2_Mini");
		LoadFolder("UI/HP/HP4_2_Restore");
		LoadFolder("UI/HP/HP4_3_Damaged");
		LoadFolder("UI/HP/HP4_3_Disappear");
		LoadFolder("UI/HP/HP4_3_Idle");
		LoadFolder("UI/HP/HP4_3_Mini");
		LoadFolder("UI/HP/HP4_3_Restore");
		LoadFolder("UI/HP/HP4_4_Disappear");
		LoadFolder("UI/HP/HP4_4_Idle");
		LoadFolder("UI/HP/HP4_4_Mini");
		LoadFolder("UI/HP/HP4_4_Restore");
		LoadFolder("UI/HP/HP4_NoImage");
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
			LoadFolder("BOSS/Boss_Slap");
			LoadFolder("BOSS/Boss_Body_Idle");
			LoadFolder("BOSS/Boss_Body_Broken_Idle");
		}
		// Wing
		{
			LoadFolder("BOSS/Boss_Wing_NoImage");
			LoadFolder("BOSS/Boss_Wing_Neu_Idle");
			LoadFolder("BOSS/Boss_Wing_Up1");
			LoadFolder("BOSS/Boss_Wing_Up2");
			LoadFolder("BOSS/Boss_Wing_Up3");
			LoadFolder("BOSS/Boss_Wing_Up4");
			LoadFolder("BOSS/Boss_Wing_Down1");
			LoadFolder("BOSS/Boss_Wing_Down2");
			LoadFolder("BOSS/Boss_Wing_Down3");
			LoadFolder("BOSS/Boss_Wing_Down4");
			LoadFolder("BOSS/Boss_Wing_Broken_Up1");
			LoadFolder("BOSS/Boss_Wing_Broken_Up2");
			LoadFolder("BOSS/Boss_Wing_Broken_Up3");
			LoadFolder("BOSS/Boss_Wing_Broken_Up4");
			LoadFolder("BOSS/Boss_Wing_Broken_Down1");
			LoadFolder("BOSS/Boss_Wing_Broken_Down2");
			LoadFolder("BOSS/Boss_Wing_Broken_Down3");
			LoadFolder("BOSS/Boss_Wing_Broken_Down4");
		}
		// Platform
		{
			LoadFolder("BOSS/BossPlatform/BossPlatform_A_BoosterLoop");
			LoadFolder("BOSS/BossPlatform/BossPlatform_A_Damaged");
			LoadFolder("BOSS/BossPlatform/BossPlatform_A_DamagedWarning");
			LoadFolder("BOSS/BossPlatform/BossPlatform_A_Deadparts");
			LoadFolder("BOSS/BossPlatform/BossPlatform_A_Destroy");
			LoadFolder("BOSS/BossPlatform/BossPlatform_A_Idle");
			LoadFolder("BOSS/BossPlatform/BossPlatform_A_IdleDoubleWarning");
			LoadFolder("BOSS/BossPlatform/BossPlatform_A_IdleWarning");
		}
		// Attack
		{
			LoadFolder("BOSS/BossAttack/BossAttack_Bomb_Appear");
			LoadFolder("BOSS/BossAttack/BossAttack_Bomb_Explode");
			LoadFolder("BOSS/BossAttack/BossAttack_Bomb_Falling");
			LoadFolder("BOSS/BossAttack/BossAttack_ClusterBomb_Appear");
			LoadFolder("BOSS/BossAttack/BossAttack_ClusterBomb_Explode");
			LoadFolder("BOSS/BossAttack/BossAttack_ClusterBomblet_Explode");
			LoadFolder("BOSS/BossAttack/BossAttack_ClusterBomblet_Idle");
			LoadFolder("BOSS/BossAttack/BossAttack_ShootExplode");

			{
				LoadFolder("BOSS/BossAttack/BossAttack_MachineGun/MachineGun_Appear");
				LoadFolder("BOSS/BossAttack/BossAttack_MachineGun/MachineGun_ShootEnd");
				LoadFolder("BOSS/BossAttack/BossAttack_MachineGun/MachineGun_ShootLoop");
				LoadFolder("BOSS/BossAttack/BossAttack_MachineGun/MachineGun_ShootReadyLoop");
			}

			LoadFolder("BOSS/Boss_Bomber/Boss_Bomber_OpenedLoop");
			LoadFolder("BOSS/Boss_Bomber/Boss_Bomber_Opening");
			LoadFolder("BOSS/Boss_Bomber/Boss_Bomber_Closing");

			LoadFolder("BOSS/BossAttack/BossAttack_BodySlap");
			LoadFolder("BOSS/BossAttack/BossAttack_NoImage");
		}
		// Aim
		{
			LoadFolder("BOSS/Boss_Aim/Cluster_Aim");
			LoadFolder("BOSS/Boss_Aim/Cluster_Appear");
			LoadFolder("BOSS/Boss_Aim/Cluster_Shoot");
			LoadFolder("BOSS/Boss_Aim/Incendiary_Aim");
			LoadFolder("BOSS/Boss_Aim/Incendiary_Appear");
			LoadFolder("BOSS/Boss_Aim/Incendiary_AttackLoop");
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
		LoadFolder("BackGround/FADE");
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
			LoadFolder("SNB/SNB_Damaged");

			LoadFolder("SNB/SNB_Chain");
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
			LoadFolder("SNB/SNB_Arm_Damaged");

			LoadFolder("SNB/SNB_Arm_Shoot");
			LoadFolder("SNB/SNB_Arm_Grabbed");
		}
		// Grab
		{
			LoadFolder("SNB/SNB_Grab/SNB_Grab_NoImage");
			LoadFolder("SNB/SNB_Grab/SNB_Grab_Flying");
			LoadFolder("SNB/SNB_Grab/SNB_Grab_Grabbing");
			LoadFolder("SNB/SNB_Grab/SNB_Grab_Grabed");
			LoadFolder("SNB/SNB_Grab/SNB_Grab_Lower_Grabbed");
			LoadFolder("SNB/SNB_Grab/SNB_Grab_Lower_Grabbing");
			LoadFolder("SNB/SNB_Grab/SNB_Grab_Return");
			LoadFolder("SNB/SNB_Grab/SNB_Grab_ReturnWithGrabbed");
			LoadFolder("SNB/SNB_Grab/SNB_Grab_ReturnWithoutGrabbed");
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
			LoadFolder("Mari/BossStage/008_TrainOnLoopLookBack");
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
		LoadFolder("Vfx/Vfx_AttackDonut");
		LoadFolder("Vfx/Vfx_Grabhit");
		LoadFolder("Vfx/Vfx_Landing");
		LoadFolder("Vfx/Vfx_RopeSliding");
		LoadFolder("Vfx/Vfx_ShootGas");
		LoadFolder("Vfx/Vfx_ShootMuzzleFire");		
		LoadFolder("Vfx/Vfx_WallJump");
		LoadFolder("Vfx/Vfx_WallSliding");
		LoadFolder("Vfx/Vfx_WallSlidingWithWindingSmoke");
		LoadFolder("Vfx/VfxSNB_GrabDust");
	}
	// temp
	{
		LoadFolder("temp/Aim");
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