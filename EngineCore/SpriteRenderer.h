#pragma once
#include <EngineBase/EngineDelegate.h>
#include "Renderer.h"
#include "EngineDataStruct.h"

class USpriteRenderer : public URenderer
{
public:
	class FrameAnimation
	{
	public:
		UEngineSprite* Sprite = nullptr;
		std::vector<int> FrameIndex;
		std::vector<float> FrameTime;
		std::map<int, EngineDelegate> Events;

		int CurIndex = 0;
		int ResultIndex = 0;
		float CurTime = 0.0f;
		bool Loop = true;
		bool IsEnd = false;

		void Reset()
		{
			CurIndex = 0;
			CurTime = 0;
			ResultIndex = 0;
			IsEnd = false;
		}
	};

	ENGINEAPI USpriteRenderer();
	ENGINEAPI ~USpriteRenderer();

	USpriteRenderer(const USpriteRenderer& _Other) = delete;
	USpriteRenderer(USpriteRenderer&& _Other) noexcept = delete;
	USpriteRenderer& operator=(const USpriteRenderer& _Other) = delete;
	USpriteRenderer& operator=(USpriteRenderer&& _Other) noexcept = delete;

	// GetFunction
	int GetCurIndex()
	{
		return CurIndex;
	}

	int GetFrameIndex()
	{
		return CurAnimation->CurIndex;
	}

	std::string GetCurSpriteName()
	{
		return Sprite->GetName();
	}

	// SetFunction
	ENGINEAPI void SetAnimationEvent(std::string_view _AnimationName, int _Frame, std::function<void()> _Function);

	ENGINEAPI void SetSprite(std::string_view _Name, UINT _CurIndex = 0);

	void SetSprite(UEngineSprite* _Sprite);

	ENGINEAPI void SetTexture(std::string_view _Name, bool AutoScale = false, float _Ratio = 1.0f);

	void SetAnimationSpeed(float _Speed)
	{
		CurAnimationSpeed = _Speed;
	}

	void SetAutoScale(bool _Value)
	{
		IsAutoScale = _Value;
	}

	void SetAutoScaleRatio(float _Scale)
	{
		AutoScaleRatio = _Scale;
	}

	void SetAlpha(float Alpha)
	{
		ColorData.MulColor.W = UEngineMath::Clamp(Alpha, 0.0f, 1.0f);
	}

	// Function
	ENGINEAPI void CreateAnimation(std::string_view _AnimationName, std::string_view _SpriteName, bool _Loop = true, float Time = 0.3f);
	ENGINEAPI void CreateAnimation(std::string_view _AnimationName, std::string_view _SpriteName, int _Start, int _End, float Time = 0.1f, bool _Loop = true);
	ENGINEAPI void CreateAnimation(std::string_view _AnimationName, std::string_view _SpriteName, std::vector<int> _Indexs, std::vector<float> _Frame, bool _Loop = true);
	ENGINEAPI void CreateAnimation(std::string_view _AnimationName, std::string_view _SpriteName, std::vector<int> _Indexs, float _Frame, bool _Loop = true);
	
	ENGINEAPI bool ChangeAnimation(std::string_view _AnimationName, bool _Force = false);
	
	ENGINEAPI FrameAnimation* FindAnimation(std::string_view _AnimationName);

	bool IsCurAnimationEnd()
	{
		return CurAnimation->IsEnd;
	}

	void ResetAnimationSpeed()
	{
		CurAnimationSpeed = 1.0f;
	}

	void AddUVPlusValue(float4 _Value)
	{
		UVValue.PlusUVValue += _Value;
	}

	FResultColor ColorData;
	FUVValue UVValue;
	FSpriteData SpriteData;

protected:
	ENGINEAPI void Render(class UEngineCamera* _Camera, float _DeltaTime) override;
	void BeginPlay() override;
	void ComponentTick(float _DeltaTime) override;
	ENGINEAPI void CameraTransUpdate(UEngineCamera* _Camera) override;

private:
	URenderUnit* MainUnit;

	int CurIndex = 0;
	float CurAnimationSpeed = 1.0f;

	std::map<std::string, FrameAnimation> FrameAnimations;
	FrameAnimation* CurAnimation = nullptr;
	UEngineSprite* Sprite = nullptr;

	bool IsAutoScale = true;
	float AutoScaleRatio = 1.0f;
};

