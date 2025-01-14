#include "PreCompile.h"
#include "SpriteRenderer.h"

#include "EngineCamera.h"

USpriteRenderer::USpriteRenderer()
{
	CreateRenderUnit();
	SetMesh("Rect");
	SetMaterial("SpriteMaterial");

	GetRenderUnit().ConstantBufferLinkData("ResultColor", ColorData);
	GetRenderUnit().ConstantBufferLinkData("FSpriteData", SpriteData);
	GetRenderUnit().ConstantBufferLinkData("FUVValue", UVValue);


	UVValue.PlusUVValue = { 0.0f, 0.0f, 0.0f, 0.0f };
	SpriteData.CuttingPos = { 0.0f, 0.0f };
	SpriteData.CuttingSize = { 1.0f, 1.0f };
	SpriteData.Pivot = { 0.5f, 0.5f };

	ColorData.PlusColor = { 0.0f, 0.0f, 0.0f, 0.0f };
	ColorData.MulColor = { 1.0f, 1.0f, 1.0f, 1.0f };
}

USpriteRenderer::~USpriteRenderer()
{
}

void USpriteRenderer::BeginPlay()
{
	URenderer::BeginPlay();
}

void USpriteRenderer::SetSprite(std::string_view _Name, UINT _Index)
{
	Sprite = UEngineSprite::Find<UEngineSprite>(_Name).get();

	GetRenderUnit().SetTexture("ImageTexture", Sprite->GetTexture(_Index)->GetName());
	SpriteData = Sprite->GetSpriteData(_Index);

	CurIndex = _Index;
}

void USpriteRenderer::SetSprite(UEngineSprite* _Sprite)
{
	Sprite = _Sprite;

	if (nullptr == Sprite)
	{
		MSGASSERT("Sprite is nullptr.");
	}
}

ENGINEAPI void USpriteRenderer::SetTexture(std::string_view _Name, bool AutoScale, float _Ratio)
{
	std::shared_ptr<UEngineTexture> Texture = UEngineTexture::Find<UEngineTexture>(_Name);

	if (nullptr == Texture)
	{
		MSGASSERT("Texture is nullptr.");
	}

	GetRenderUnit().SetTexture("ImageTexture", _Name);

	if (true == AutoScale)
	{
		SetRelativeScale3D(Texture->GetTextureSize() * _Ratio);
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
		Sprite = CurAnimation->Sprite;

		GetRenderUnit().SetTexture("ImageTexture", Sprite->GetTexture(CurIndex)->GetName());
		SpriteData = Sprite->GetSpriteData(CurIndex);
	}

	if (true == IsAutoScale && nullptr != Sprite)
	{
		FVector Scale = Sprite->GetSpriteScaleToReal(CurIndex);
		Scale.Z = 1.0f;
		SetRelativeScale3D(Scale * AutoScaleRatio);
	}

	URenderer::Render(_Camera, _DeltaTime);
}

//void USpriteRenderer::ComponentTick(float _DeltaTime)
//{
//	URenderer::ComponentTick(_DeltaTime);
//
//	if (nullptr != CurAnimation)
//	{
//		CurAnimation->IsEnd = false;
//		FrameAnimation* EventAnimation = nullptr;
//		int EventFrame = -1;
//
//		std::vector<int>& Indexes = CurAnimation->FrameIndex;
//		std::vector<float>& Times = CurAnimation->FrameTime;
//
//		Sprite = CurAnimation->Sprite;
//
//
//		CurAnimation->CurTime += _DeltaTime * CurAnimationSpeed;
//
//		float CurFrameTime = Times[CurAnimation->CurIndex];
//
//		if (CurAnimation->CurTime > CurFrameTime)
//		{
//
//			CurAnimation->CurTime = 0.0f;
//			++CurAnimation->CurIndex;
//
//			if (CurAnimation->Events.contains(CurIndex))
//			{
//				EventAnimation = CurAnimation;
//				EventFrame = CurIndex;
//			}
//
//
//			if (CurAnimation->CurIndex >= Indexes.size())
//			{
//				CurAnimation->IsEnd = true;
//				if (true == CurAnimation->Loop)
//				{
//					CurAnimation->CurIndex = 0;
//
//					if (CurAnimation->Events.contains(CurIndex))
//					{
//						EventAnimation = CurAnimation;
//						EventFrame = CurIndex;
//					}
//				}
//				else
//				{
//					--CurAnimation->CurIndex;
//				}
//			}
//		}
//
//
//
//		CurIndex = Indexes[CurAnimation->CurIndex];
//		if (nullptr != EventAnimation)
//		{
//			if (EventAnimation->Events.contains(CurIndex))
//			{
//				EventAnimation->Events[CurIndex]();
//			}
//		}
//	}
//}

void USpriteRenderer::ComponentTick(float _DeltaTime)
{
	URenderer::ComponentTick(_DeltaTime);

	if (nullptr != CurAnimation)
	{
		FrameAnimation* EventAnimation = nullptr;
		int EventFrame = -1;

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
				EventAnimation = CurAnimation;
				EventFrame = CurIndex;
			}

			if (CurAnimation->CurIndex >= Indexes.size())
			{
				if (CurAnimation->Loop)
				{
					CurAnimation->CurIndex = 0;

					if (CurAnimation->Events.contains(CurIndex))
					{
						EventAnimation = CurAnimation;
						EventFrame = CurIndex;
					}
				}
				else
				{
					CurAnimation->CurIndex = Indexes.size() - 1; 
					CurAnimation->IsEnd = true;
				}
			}
		}

		if (false == CurAnimation->IsEnd)
		{
			CurIndex = Indexes[CurAnimation->CurIndex];
			if (nullptr != EventAnimation && EventAnimation->Events.contains(CurIndex))
			{
				EventAnimation->Events[CurIndex]();
			}
		}
	}
}

void USpriteRenderer::CameraTransUpdate(UEngineCamera* _Camera)
{
	FTransform& CameraTrans = _Camera->GetTransformRef();
	FTransform& RendererTrans = GetTransformRef();

	RendererTrans.View = CameraTrans.View;
	FMatrix CurWorld = RendererTrans.World;

	RendererTrans.Projection = CameraTrans.Projection;
	RendererTrans.WVP = CurWorld * RendererTrans.View * RendererTrans.Projection;
}

void USpriteRenderer::CreateAnimation(std::string_view _AnimationName, std::string_view _SpriteName, bool _Loop /*= true*/, float Time /*= 0.1f*/)
{
	std::shared_ptr<UEngineSprite> FindSprite = UEngineSprite::Find<UEngineSprite>(_SpriteName);
	
	if (nullptr == FindSprite)
	{
		MSGASSERT(std::string(_SpriteName) + " is not found.");
		return;
	}

	int SpriteCount = FindSprite.get()->GetSpriteTextureCount() - 1;

	CreateAnimation(_AnimationName, _SpriteName, 0, SpriteCount, Time, _Loop);
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

bool USpriteRenderer::ChangeAnimation(std::string_view _AnimationName, bool _Force /*= false*/)
{
	std::string UpperName = UEngineString::ToUpper(_AnimationName);

	if (false == FrameAnimations.contains(UpperName))
	{
		// MSGASSERT(UpperName + " is not exists.");
		return false;
	}

	FrameAnimation* ChangeAnimation = &FrameAnimations[UpperName];

	if (CurAnimation == ChangeAnimation && false == _Force)
	{
		return true;
	}

	CurAnimation = &FrameAnimations[UpperName];
	CurAnimation->Reset();
	CurIndex = CurAnimation->FrameIndex[CurAnimation->CurIndex];

	if (CurAnimation->Events.contains(CurAnimation->CurIndex))
	{
		CurAnimation->Events[CurAnimation->CurIndex]();
	}

	if (true == IsAutoScale)
	{
		FVector Scale = CurAnimation->Sprite->GetSpriteScaleToReal(CurIndex);
		Scale.Z = 1.0f;
		SetRelativeScale3D(Scale * AutoScaleRatio);
	}

	return true;
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
