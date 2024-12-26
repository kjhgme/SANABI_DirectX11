#pragma once
#include <EngineBase/EngineDelegate.h>
#include <EngineBase/EngineDebug.h>

#include <vector>
#include <functional>

enum class KeyEvent
{
	Down,
	Press,
	Free,
	Up,
};

class UEngineInput
{
public:
	~UEngineInput();

	UEngineInput(const UEngineInput& _Other) = delete;
	UEngineInput(UEngineInput&& _Other) noexcept = delete;
	UEngineInput& operator=(const UEngineInput& _Other) = delete;
	UEngineInput& operator=(UEngineInput&& _Other) noexcept = delete;

	static UEngineInput& GetInst()
	{
		static UEngineInput Inst = UEngineInput();
		return Inst;
	}

private:
	class UEngineKey
	{
	public:
		int Key = -1;

		bool IsDown = false;
		bool IsPress = false;
		bool IsUp = false;
		bool IsFree = true;

		float PressTime = 0.0f;

		std::vector<std::function<void(float)>> PressEvents;
		std::vector<std::function<void(float)>> DownEvents;
		std::vector<std::function<void(float)>> UpEvents;
		std::vector<std::function<void(float)>> FreeEvents;

		UEngineKey()
		{
		}

		UEngineKey(int _Key) : Key(_Key)
		{
		}

		void EventCheck(float _DeltaTime);
		void KeyCheck(float _DeltaTime);
	};

public:
	void KeyCheck(float _DeltaTime);
	void EventCheck(float _DeltaTime);

	bool IsDown(int _KeyIndex)
	{
		if (false == Keys.contains(_KeyIndex))
		{
			MSGASSERT("Entered keys that is not yet registered.(EngineInput)");
			return false;
		}

		return Keys[_KeyIndex].IsDown;
	}

	bool IsUp(int _KeyIndex)
	{
		if (false == Keys.contains(_KeyIndex))
		{
			MSGASSERT("Entered keys that is not yet registered.(EngineInput)");
			return false;
		}

		return Keys[_KeyIndex].IsUp;
	}

	bool IsPress(int _KeyIndex)
	{
		if (false == Keys.contains(_KeyIndex))
		{
			MSGASSERT("Entered keys that is not yet registered.(EngineInput)");
			return false;
		}

		return Keys[_KeyIndex].IsPress;
	}

	float IsPressTime(int _KeyIndex)
	{
		if (false == Keys.contains(_KeyIndex))
		{
			MSGASSERT("Entered keys that is not yet registered.(EngineInput)");
			return false;
		}

		return Keys[_KeyIndex].PressTime;
	}

	bool IsFree(int _KeyIndex)
	{
		if (false == Keys.contains(_KeyIndex))
		{
			MSGASSERT("Entered keys that is not yet registered.(EngineInput)");
			return false;
		}

		return Keys[_KeyIndex].IsFree;
	}

	void BindAction(int _KeyIndex, KeyEvent _EventType, std::function<void(float)> _Function);

protected:

private:
	std::map<int, UEngineKey> Keys;

	UEngineInput();
};

