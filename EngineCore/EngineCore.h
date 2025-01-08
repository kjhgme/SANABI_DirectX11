#pragma once
#include <memory>

#include <EngineBase/EngineDefine.h>
#include <EngineBase/EngineTimer.h>
#include <EnginePlatform/EngineWindow.h>

#include "Level.h"
#include "IContentsCore.h"
#include "EngineGraphicDevice.h"

class UEngineCore
{
public:
	ENGINEAPI UEngineCore();
	ENGINEAPI virtual ~UEngineCore() = 0;

	ENGINEAPI static void EngineStart(HINSTANCE _Instance, std::string_view _DllName);

	template<typename GameModeType, typename MainPawnType>
	static class std::shared_ptr<class ULevel> CreateLevel(std::string_view _Name)
	{
		std::shared_ptr<ULevel> NewLevel = NewLevelCreate(_Name);
	
		std::shared_ptr<GameModeType> GameMode = NewLevel->SpawnActor<GameModeType>();
		std::shared_ptr<MainPawnType> Pawn = NewLevel->SpawnActor<MainPawnType>();

		NewLevel->InitLevel(GameMode.get(), Pawn.get());

		return NewLevel;
	}

	ENGINEAPI static void OpenLevel(std::string_view _Name);

	ENGINEAPI static FVector GetScreenScale();

	ENGINEAPI static UEngineWindow& GetMainWindow();
	ENGINEAPI static UEngineGraphicDevice& GetDevice();

protected:

private:
	ENGINEAPI static UEngineWindow MainWindow;
	ENGINEAPI static UEngineGraphicDevice Device;

	static HMODULE ContentsDLL;
	static std::shared_ptr<IContentsCore> Core;
	static UEngineInitData Data;

	static UEngineTimer Timer;

	static void WindowInit(HINSTANCE _Instance);
	static void LoadContents(std::string_view _DllName);

	static void EngineFrame();
	static void EngineEnd();

	ENGINEAPI static std::shared_ptr<ULevel> NewLevelCreate(std::string_view _Name);

	static std::map<std::string, std::shared_ptr<class ULevel>> LevelMap;
	static std::shared_ptr<class ULevel> CurLevel;
	static std::shared_ptr<class ULevel> NextLevel;
};

