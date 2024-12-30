#include "PreCompile.h"
#include "SpriteRenderer.h"

USpriteRenderer::USpriteRenderer()
{
}

USpriteRenderer::~USpriteRenderer()
{
}

void USpriteRenderer::BeginPlay()
{
	URenderer::BeginPlay();
	SetMesh("Rect");
	SetBlend("AlphaBlend");
}

void USpriteRenderer::SetSprite(std::string_view _Name, size_t _Index)
{
	std::string UpperString = UEngineString::ToUpper(_Name);

	Sprite = UEngineSprite::Find<UEngineSprite>(UpperString).get();

	URenderer::SetTexture(Sprite->GetTexture(_Index));
	SetSpriteData(Sprite, _Index);
}

void USpriteRenderer::SetSprite(UEngineSprite* _Sprite)
{
	Sprite = _Sprite;

	if (nullptr == Sprite)
	{
		MSGASSERT("Sprite is nullptr.");
	}
}

USpriteRenderer::FrameAnimation* USpriteRenderer::FindAnimation(std::string_view _AnimationName)
{
	std::string UpperString = UEngineString::ToUpper(_AnimationName);

	if (false == FrameAnimations.contains(UpperString))
	{
		return nullptr;
	}

	return &FrameAnimations[UpperString];
}

void USpriteRenderer::Render(UEngineCamera* _Camera, float _DeltaTime)
{
	if (nullptr != CurAnimation)
	{
		UEngineSprite* Sprite = CurAnimation->Sprite;
		size_t CurIndex = CurAnimation->CurIndex;

		URenderer::SetTexture(Sprite->GetTexture(CurIndex));
		URenderer::SetSpriteData(Sprite, CurIndex);
	}

	URenderer::Render(_Camera, _DeltaTime);
}

void USpriteRenderer::ComponentTick(float _DeltaTime)
{
	URenderer::ComponentTick(_DeltaTime);

	if (nullptr != CurAnimation)
	{
		CurAnimation->IsEnd = false;
		std::vector<int>& Indexes = CurAnimation->FrameIndex;
		std::vector<float>& Times = CurAnimation->FrameTime;

		Sprite = CurAnimation->Sprite;


		CurAnimation->CurTime += _DeltaTime * CurAnimationSpeed;

		float CurFrameTime = Times[CurAnimation->CurIndex];

		if (CurAnimation->CurTime > CurFrameTime)
		{

			CurAnimation->CurTime -= CurFrameTime;
			++CurAnimation->CurIndex;

			if (CurAnimation->Events.contains(CurIndex))
			{
				CurAnimation->Events[CurIndex]();
			}

			if (CurAnimation->CurIndex >= Indexes.size())
			{
				CurAnimation->IsEnd = true;
			}
			else {
				CurAnimation->IsEnd = false;
			}

			if (CurAnimation->CurIndex >= Indexes.size())
			{
				if (true == CurAnimation->Loop)
				{
					CurAnimation->CurIndex = 0;

					if (CurAnimation->Events.contains(CurIndex))
					{
						CurAnimation->Events[CurIndex]();
					}
				}
				else
				{
					CurAnimation->IsEnd = true;
					--CurAnimation->CurIndex;
				}
			}
		}

		CurIndex = Indexes[CurAnimation->CurIndex];

		if (true == CurAnimation->IsAutoScale)
		{
			FVector Scale = CurAnimation->Sprite->GetSpriteScaleToReal(CurIndex);
			Scale.Z = 1.0f;
			SetRelativeScale3D(Scale * CurAnimation->AutoScaleRatio);
		}
	}
}


void USpriteRenderer::CreateAnimation(std::string_view _AnimationName, std::string_view _SpriteName, int _Start, int _End, float Time /*= 0.1f*/, bool _Loop /*= true*/)
{
	int Inter = 0;

	std::vector<int> Indexes;
	std::vector<float> Times;

	if (_Start < _End)
	{
		Inter = (_End - _Start) + 1;
		for (size_t i = 0; i < Inter; i++)
		{
			Indexes.push_back(_Start);
			Times.push_back(Time);
			++_Start;
		}

	}
	else
	{
		Inter = (_Start - _End) + 1;
		for (size_t i = 0; i < Inter; i++)
		{
			Indexes.push_back(_End);
			Times.push_back(Time);
			++_End;
		}
	}


	CreateAnimation(_AnimationName, _SpriteName, Indexes, Times, _Loop);
}


void USpriteRenderer::CreateAnimation(std::string_view _AnimationName, std::string_view _SpriteName, std::vector<int> _Indexs, float _Frame, bool _Loop /*= true*/)
{
	std::vector<float> Times;

	for (size_t i = 0; i < _Indexs.size(); i++)
	{
		Times.push_back(_Frame);
	}

	CreateAnimation(_AnimationName, _SpriteName, _Indexs, Times, _Loop);
}

void USpriteRenderer::CreateAnimation(std::string_view _AnimationName, std::string_view _SpriteName, std::vector<int> _Indexs, std::vector<float> _Frame, bool _Loop /*= true*/)
{
	std::string UpperName = UEngineString::ToUpper(_AnimationName);

	if (_Frame.size() != _Indexs.size())
	{
		MSGASSERT(UpperName + "'s size is different.");
		return;
	}

	if (FrameAnimations.contains(UpperName))
	{
		return;
	}

	std::shared_ptr<UEngineSprite> FindSprite = UEngineSprite::Find<UEngineSprite>(_SpriteName);

	if (nullptr == FindSprite)
	{
		MSGASSERT(std::string(UpperName) + " is not found.");
		return;
	}

	FrameAnimation NewAnimation;
	NewAnimation.Sprite = FindSprite.get();
	NewAnimation.FrameIndex = _Indexs;
	NewAnimation.FrameTime = _Frame;
	NewAnimation.Loop = _Loop;
	NewAnimation.Reset();

	FrameAnimations.insert({ UpperName ,NewAnimation });

}

void USpriteRenderer::ChangeAnimation(std::string_view _AnimationName, bool _Force /*= false*/)
{
	std::string UpperName = UEngineString::ToUpper(_AnimationName);

	if (false == FrameAnimations.contains(UpperName))
	{
		MSGASSERT(UpperName + " is not exists.");
		return;
	}

	FrameAnimation* ChangeAnimation = &FrameAnimations[UpperName];

	if (CurAnimation == ChangeAnimation && false == _Force)
	{
		return;
	}

	CurAnimation = &FrameAnimations[UpperName];
	CurAnimation->Reset();
	CurIndex = CurAnimation->FrameIndex[CurAnimation->CurIndex];

	if (CurAnimation->Events.contains(CurAnimation->CurIndex))
	{
		CurAnimation->Events[CurAnimation->CurIndex]();
	}

	if (true == CurAnimation->IsAutoScale)
	{
		FVector Scale = CurAnimation->Sprite->GetSpriteScaleToReal(CurIndex);
		Scale.Z = 1.0f;
		SetRelativeScale3D(Scale * CurAnimation->AutoScaleRatio);
	}
}


void USpriteRenderer::SetAnimationEvent(std::string_view _AnimationName, int _Frame, std::function<void()> _Function)
{
	std::string UpperName = UEngineString::ToUpper(_AnimationName);

	if (false == FrameAnimations.contains(UpperName))
	{
		MSGASSERT(UpperName + " is not exists.");
		return;
	}

	FrameAnimation* ChangeAnimation = &FrameAnimations[UpperName];

	bool Check = false;

	for (size_t i = 0; i < ChangeAnimation->FrameIndex.size(); i++)
	{
		if (_Frame == ChangeAnimation->FrameIndex[i])
		{
			Check = true;
			break;
		}
	}

	if (false == Check)
	{
		MSGASSERT(std::string(_AnimationName) + " is not exists.");
		return;
	}

	ChangeAnimation->Events[_Frame] += _Function;

}
