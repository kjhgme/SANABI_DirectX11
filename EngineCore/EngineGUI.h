#pragma once
#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"

#include <EngineBase/EngineString.h>

class UEngineGUI
{
public:
	UEngineGUI();
	~UEngineGUI();

	UEngineGUI(const UEngineGUI& _Other) = delete;
	UEngineGUI(UEngineGUI&& _Other) noexcept = delete;
	UEngineGUI& operator=(const UEngineGUI& _Other) = delete;
	UEngineGUI& operator=(UEngineGUI&& _Other) noexcept = delete;

	static void Init();
	static void Release();

	static void GUIRenderStart();

	static void GUIRenderEnd();

	ENGINEAPI static void PushGUIWindow(std::shared_ptr<class UEngineGUIWindow> _Window);

	template<typename WindowType>
	static std::shared_ptr<WindowType> CreateGUIWindow(std::string_view _Text)
	{
		std::string UpperName = UEngineString::ToUpper(_Text);

		if (nullptr != FindGUIWindow(UpperName))
		{
			MSGASSERT(UpperName + " is already created.");
			return nullptr;
		}

		std::shared_ptr<WindowType> Window = std::make_shared<WindowType>();
		Window->SetName(UpperName);
		PushGUIWindow(Window);
		return Window;
	}

	template<typename WindowType>
	static std::shared_ptr<WindowType> FindGUIWindow(std::string_view _Text)
	{
		return std::dynamic_pointer_cast<WindowType>(FindGUIWindow(_Text));
	}

	ENGINEAPI static std::shared_ptr<UEngineGUIWindow> FindGUIWindow(std::string_view _Text);

	static void GUIRender(ULevel* _Level);

	ENGINEAPI static void AllWindowOff();

	ENGINEAPI static void AllWindowOn();

protected:

private:
	static inline std::map<std::string, std::shared_ptr<class UEngineGUIWindow>> Windows;

};

