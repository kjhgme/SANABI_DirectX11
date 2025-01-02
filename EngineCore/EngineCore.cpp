#include "PreCompile.h"
#include "EngineCore.h"

#include <EngineBase/EngineDebug.h>
#include <EnginePlatform/EngineWindow.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineResources.h>

#include "Level.h"
#include "IContentsCore.h"

UEngineWindow UEngineCore::MainWindow;
UEngineGraphicDevice UEngineCore::Device;
HMODULE UEngineCore::ContentsDLL = nullptr;
std::shared_ptr<IContentsCore> UEngineCore::Core;
UEngineInitData UEngineCore::Data;
UEngineTimer UEngineCore::Timer;

std::shared_ptr<class ULevel> UEngineCore::NextLevel;
std::shared_ptr<class ULevel> UEngineCore::CurLevel = nullptr;

std::map<std::string, std::shared_ptr<class ULevel>> UEngineCore::LevelMap;

UEngineCore::UEngineCore()
{
}

UEngineCore::~UEngineCore()
{
}

void UEngineCore::WindowInit(HINSTANCE _Instance)
{
	UEngineWindow::EngineWindowInit(_Instance);
	MainWindow.Open("SANABI");
}

void UEngineCore::LoadContents(std::string_view _DllName)
{
	UEngineDirectory Dir;

	Dir.MoveParentToDirectory("Build");
	Dir.Move("bin/x64");

#ifdef _DEBUG
	Dir.Move("Debug");
#else
	Dir.Move("Release");
#endif

	UEngineFile File = Dir.GetFile(_DllName);

	std::string FullPath = File.GetPathToString();

	ContentsDLL = LoadLibraryA(FullPath.c_str());

	if (nullptr == ContentsDLL)
	{
		MSGASSERT("ContentsDLL is nullptr.");
		return;
	}

	INT_PTR(__stdcall * Ptr)(std::shared_ptr<IContentsCore>&) = (INT_PTR(__stdcall*)(std::shared_ptr<IContentsCore>&))GetProcAddress(ContentsDLL, "CreateContentsCore");

	if (nullptr == Ptr)
	{
		MSGASSERT("CreateContentsCore is nullptr.");
		return;
	}

	Ptr(Core);

	if (nullptr == Core)
	{
		MSGASSERT("Core is nullptr.");
		return;
	}
}

void UEngineCore::EngineStart(HINSTANCE _Instance, std::string_view _DllName)
{
	UEngineDebug::LeakCheck();

	WindowInit(_Instance);

	LoadContents(_DllName);

	UEngineWindow::WindowMessageLoop(
		[]()
		{
			Device.CreateDeviceAndContext();
			Core->EngineStart(Data);
			MainWindow.SetWindowPosAndScale(Data.WindowPos, Data.WindowSize);
			Device.CreateBackBuffer(MainWindow);
		},
		[]()
		{
			EngineFrame();
		},
		[]() 
		{
			EngineEnd();
		});		
}

std::shared_ptr<ULevel> UEngineCore::NewLevelCreate(std::string_view _Name)
{
	std::shared_ptr<ULevel> Ptr = std::make_shared<ULevel>();
	Ptr->SetName(_Name);

	LevelMap.insert({ _Name.data(), Ptr});

	std::cout << "NewLevelCreate" << std::endl;

	return Ptr;
}

void UEngineCore::OpenLevel(std::string_view _Name)
{
	if (false == LevelMap.contains(_Name.data()))
	{
		MSGASSERT(std::string(_Name) + "is not contained.");
		return;
	}
	
	NextLevel = LevelMap[_Name.data()];
}

FVector UEngineCore::GetScreenScale()
{
	return Data.WindowSize;
}

UEngineWindow& UEngineCore::GetMainWindow()
{
	return MainWindow;
}

UEngineGraphicDevice& UEngineCore::GetDevice()
{
	return Device;
}

void UEngineCore::EngineFrame()
{
	if (nullptr != NextLevel)
	{
		if (nullptr != CurLevel)
		{
			CurLevel->LevelChangeEnd();
		}

		CurLevel = NextLevel;

		CurLevel->LevelChangeStart();
		NextLevel = nullptr;
		Timer.TimeStart();
	}

	Timer.TimeCheck();
	float DeltaTime = Timer.GetDeltaTime();
	UEngineInput::KeyCheck(DeltaTime);

	CurLevel->Tick(DeltaTime);
	CurLevel->Render(DeltaTime);
}

void UEngineCore::EngineEnd()
{
	Device.Release();
	UEngineResources::Release();

	CurLevel = nullptr;
	NextLevel = nullptr;
	LevelMap.clear();

	UEngineDebug::EndConsole();
}