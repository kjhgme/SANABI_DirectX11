#include "PreCompile.h"
#include "EngineDepthStencilState.h"

#include "EngineCore.h"

UEngineDepthStencilState::UEngineDepthStencilState()
{
}

UEngineDepthStencilState::~UEngineDepthStencilState()
{
}


std::shared_ptr<UEngineDepthStencilState> UEngineDepthStencilState::Create(std::string_view _Name, const D3D11_DEPTH_STENCIL_DESC& _Value)
{
	std::string UpperName = ToUpperName(_Name);

	if (true == Contains(UpperName))
	{
		MSGASSERT(UpperName + " is already contained.");
		return nullptr;
	}

	std::shared_ptr<UEngineDepthStencilState> NewRes = std::make_shared<UEngineDepthStencilState>();
	PushRes<UEngineDepthStencilState>(NewRes, _Name, "");
	NewRes->ResCreate(_Value);

	return NewRes;
}


void UEngineDepthStencilState::ResCreate(const D3D11_DEPTH_STENCIL_DESC& _Value)
{
	if (UEngineCore::GetDevice().GetDevice()->CreateDepthStencilState(&_Value, &State))
	{
		MSGASSERT("CreateDepthStencilState failed.");
		return;
	}

}

void UEngineDepthStencilState::Setting()
{
	UEngineCore::GetDevice().GetContext()->OMSetDepthStencilState(State.Get(), 0);
}
