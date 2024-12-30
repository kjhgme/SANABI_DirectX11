#include "PreCompile.h"
#include "EngineBlend.h"

#include "EngineCore.h"

UEngineBlend::UEngineBlend()
{
}

UEngineBlend::~UEngineBlend()
{
}

std::shared_ptr<UEngineBlend> UEngineBlend::Create(std::string_view _Name, const D3D11_BLEND_DESC& _Value)
{
	std::string UpperName = ToUpperName(_Name);

	if (true == Contains(UpperName))
	{
		MSGASSERT(UpperName + " is already contained.");
		return nullptr;
	}

	std::shared_ptr<UEngineBlend> NewRes = std::make_shared<UEngineBlend>();
	PushRes<UEngineBlend>(NewRes, _Name, "");
	NewRes->ResCreate(_Value);

	return NewRes;
}


void UEngineBlend::ResCreate(const D3D11_BLEND_DESC& _Value)
{
	if (UEngineCore::GetDevice().GetDevice()->CreateBlendState(&_Value, &State))
	{
		MSGASSERT("CreateBlendState failed.");
		return;
	}
}

void UEngineBlend::Setting()
{
	UEngineCore::GetDevice().GetContext()->OMSetBlendState(State.Get(), BlendFactor.Arr1D, Mask);
}
