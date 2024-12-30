#include "PreCompile.h"
#include "Renderer.h"

#include <EngineBase/EngineString.h>
#include <EngineCore/EngineCamera.h>
#include <EngineCore/EngineTexture.h>
#include <EngineCore/Mesh.h>
#include "EngineVertex.h"
#include "EngineBlend.h"

URenderer::URenderer()
{
}

URenderer::~URenderer()
{
}

ENGINEAPI void URenderer::BeginPlay()
{
	USceneComponent::BeginPlay();
	SetOrder(0);

	VertexShaderInit();
	RasterizerInit();
	PixelShaderInit();
	ShaderResInit();
}

void URenderer::Render(UEngineCamera* _Camera, float _DeltaTime)
{
	FTransform& CameraTrans = _Camera->GetTransformRef();
	FTransform& RendererTrans = GetTransformRef();

	RendererTrans.View = CameraTrans.View;
	RendererTrans.Projection = CameraTrans.Projection;
	RendererTrans.WVP = RendererTrans.World * RendererTrans.View * RendererTrans.Projection;

	ShaderResSetting();
	InputAssembler1Setting();
	VertexShaderSetting();
	InputAssembler2Setting();
	RasterizerSetting();
	PixelShaderSetting();
	OutPutMergeSetting();

	UEngineCore::Device.GetContext()->DrawIndexed(6, 0, 0);
}

void URenderer::SetOrder(int _Order)
{
	int PrevOrder = GetOrder();
	UObject::SetOrder(_Order);
	ULevel* Level = GetActor()->GetWorld();
	
	std::shared_ptr<URenderer> RendererPtr = GetThis<URenderer>();

	Level->ChangeRenderGroup(0, PrevOrder, RendererPtr);
}

void URenderer::SetSprite(std::string_view _Value)
{
	std::string UpperName = UEngineString::ToUpper(_Value);

	Sprite = UEngineSprite::Find<UEngineSprite>(UpperName).get();

	if (nullptr == Sprite)
	{
		MSGASSERT("Sprite is nullptr.");
	}
}

void URenderer::SetSprite(UEngineSprite* _Sprite)
{
	Sprite = _Sprite;

	if (nullptr == Sprite)
	{
		MSGASSERT("Sprite is nullptr.");
	}
}

void URenderer::SetSpriteData(size_t _Index)
{
	SpriteData = Sprite->GetSpriteData(_Index);
}

ENGINEAPI void URenderer::SetMesh(std::string_view _Name)
{
	std::shared_ptr<UMesh> FindMesh = UMesh::Find<UMesh>(_Name);

	Mesh = FindMesh.get();

	if (nullptr == Mesh)
	{
		MSGASSERT("Mesh is nullptr.");
	}
}

void URenderer::SetBlend(std::string_view _Name)
{
	std::shared_ptr<UEngineBlend> FindBlend = UEngineBlend::Find<UEngineBlend>(_Name);

	Blend = FindBlend.get();

	if (nullptr == Blend)
	{
		MSGASSERT("Blend is nullptr.");
	}
}

void URenderer::ShaderResInit()
{
	{
		D3D11_BUFFER_DESC BufferInfo = { 0 };
		BufferInfo.ByteWidth = sizeof(FTransform);
		BufferInfo.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		BufferInfo.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
		BufferInfo.Usage = D3D11_USAGE_DYNAMIC;

		if (S_OK != UEngineCore::GetDevice().GetDevice()->CreateBuffer(&BufferInfo, nullptr, &TransformConstBuffer))
		{
			MSGASSERT("Constant Buffer failed.");
			return;
		}
	}

	{
		D3D11_BUFFER_DESC BufferInfo = { 0 };
		BufferInfo.ByteWidth = sizeof(FSpriteData);
		BufferInfo.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		BufferInfo.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
		BufferInfo.Usage = D3D11_USAGE_DYNAMIC;

		if (S_OK != UEngineCore::GetDevice().GetDevice()->CreateBuffer(&BufferInfo, nullptr, &SpriteConstBuffer))
		{
			MSGASSERT("Constant Buffer failed.");
			return;
		}
	}

	D3D11_SAMPLER_DESC SampInfo = { D3D11_FILTER::D3D11_FILTER_MIN_MAG_MIP_POINT };
	SampInfo.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_BORDER;
	SampInfo.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_BORDER;
	SampInfo.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_CLAMP;

	SampInfo.BorderColor[0] = 0.0f;
	SampInfo.BorderColor[1] = 0.0f;
	SampInfo.BorderColor[2] = 0.0f;
	SampInfo.BorderColor[3] = 0.0f;

	UEngineCore::GetDevice().GetDevice()->CreateSamplerState(&SampInfo, &SamplerState);
}

void URenderer::ShaderResSetting()
{
	{
		FTransform& RendererTrans = GetTransformRef();

		D3D11_MAPPED_SUBRESOURCE Data = {};
		UEngineCore::Device.GetContext()->Map(TransformConstBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &Data);

		if (nullptr == Data.pData)
		{
			MSGASSERT("Connect to GraphicCard failed.");
		}

		memcpy_s(Data.pData, sizeof(FTransform), &RendererTrans, sizeof(FTransform));

		UEngineCore::Device.GetContext()->Unmap(TransformConstBuffer.Get(), 0);

		ID3D11Buffer* ArrPtr[16] = { TransformConstBuffer.Get() };
		UEngineCore::Device.GetContext()->VSSetConstantBuffers(0, 1, ArrPtr);
	}

	{
		D3D11_MAPPED_SUBRESOURCE Data = {};
		UEngineCore::Device.GetContext()->Map(SpriteConstBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &Data);

		if (nullptr == Data.pData)
		{
			MSGASSERT("Connect to GraphicCard failed.");
		}
		memcpy_s(Data.pData, sizeof(FSpriteData), &SpriteData, sizeof(FSpriteData));
		UEngineCore::Device.GetContext()->Unmap(SpriteConstBuffer.Get(), 0);

		ID3D11Buffer* ArrPtr[16] = { SpriteConstBuffer.Get() };
		UEngineCore::Device.GetContext()->VSSetConstantBuffers(1, 1, ArrPtr);
	}

	ID3D11ShaderResourceView* ArrSRV[16] = { Sprite->GetSRV() };
	UEngineCore::Device.GetContext()->PSSetShaderResources(0, 1, ArrSRV);

	ID3D11SamplerState* ArrSMP[16] = { SamplerState.Get() };
	UEngineCore::Device.GetContext()->PSSetSamplers(0, 1, ArrSMP);
}

void URenderer::InputAssembler1Setting()
{
	Mesh->GetVertexBuffer()->Setting();
	UEngineCore::GetDevice().GetContext()->IASetInputLayout(InputLayOut.Get());
}

void URenderer::InputAssembler1LayOut()
{
	std::vector<D3D11_INPUT_ELEMENT_DESC> InputLayOutData;

	{
		D3D11_INPUT_ELEMENT_DESC Desc;
		Desc.SemanticName = "POSITION";
		Desc.InputSlot = 0;
		Desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		Desc.AlignedByteOffset = 0;
		Desc.InputSlotClass = D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA;

		Desc.SemanticIndex = 0;
		Desc.InstanceDataStepRate = 0;
		InputLayOutData.push_back(Desc);
	}

	{
		D3D11_INPUT_ELEMENT_DESC Desc;
		Desc.SemanticName = "TEXCOORD";
		Desc.InputSlot = 0;
		Desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		Desc.AlignedByteOffset = 16;
		Desc.InputSlotClass = D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA;

		Desc.SemanticIndex = 0;
		Desc.InstanceDataStepRate = 0;
		InputLayOutData.push_back(Desc);
	}

	{
		D3D11_INPUT_ELEMENT_DESC Desc;
		Desc.SemanticName = "COLOR";
		Desc.InputSlot = 0;
		Desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		Desc.AlignedByteOffset = 32;
		Desc.InputSlotClass = D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA;

		Desc.SemanticIndex = 0;
		Desc.InstanceDataStepRate = 0;
		InputLayOutData.push_back(Desc);
	}

	HRESULT Result = UEngineCore::Device.GetDevice()->CreateInputLayout(
		&InputLayOutData[0],
		static_cast<unsigned int>(InputLayOutData.size()),
		VSShaderCodeBlob->GetBufferPointer(),
		VSShaderCodeBlob->GetBufferSize(),
		&InputLayOut);

	if (S_OK != Result)
	{
		MSGASSERT("CreateInputLayout failed.");
	}
}

void URenderer::VertexShaderInit()
{
	UEngineDirectory CurDir;
	CurDir.MoveParentToDirectory("EngineShader");
	UEngineFile File = CurDir.GetFile("EngineSpriteShader.fx");

	std::string Path = File.GetPathToString();

	std::wstring WPath = UEngineString::AnsiToUnicode(Path);

	std::string version = "vs_5_0";

	int Flag0 = 0;
	int Flag1 = 0;

#ifdef _DEBUG
	Flag0 = D3D10_SHADER_DEBUG;
#endif
	Flag0 |= D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;

	D3DCompileFromFile(
		WPath.c_str(),
		nullptr,
		nullptr,
		"VertexToWorld",
		version.c_str(),
		Flag0,
		Flag1,
		&VSShaderCodeBlob,
		&VSErrorCodeBlob
	);

	if (nullptr == VSShaderCodeBlob)
	{
		std::string ErrString = reinterpret_cast<char*>(VSErrorCodeBlob->GetBufferPointer());
		MSGASSERT(ErrString + "GetBufferPointer failed.");
		return;
	}

	HRESULT Result = UEngineCore::Device.GetDevice()->CreateVertexShader(
		VSShaderCodeBlob->GetBufferPointer(),
		VSShaderCodeBlob->GetBufferSize(),
		nullptr,
		&VertexShader
	);

	if (S_OK != Result)
	{
		MSGASSERT("CreateVertexShader failed.");
	}

	InputAssembler1LayOut();
}

void URenderer::VertexShaderSetting()
{
	UEngineCore::GetDevice().GetContext()->VSSetShader(VertexShader.Get(), nullptr, 0);
}

void URenderer::InputAssembler2Setting()
{
	Mesh->GetIndexBuffer()->Setting();
	UEngineCore::GetDevice().GetContext()->IASetPrimitiveTopology(Topology);
}

void URenderer::RasterizerInit()
{
	D3D11_RASTERIZER_DESC Desc = {};

	Desc.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;
	Desc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;

	UEngineCore::Device.GetDevice()->CreateRasterizerState(&Desc, RasterizerState.GetAddressOf());

	ViewPortInfo.Height = 720.0f;
	ViewPortInfo.Width = 1280.0f;
	ViewPortInfo.TopLeftX = 0.0f;
	ViewPortInfo.TopLeftY = 0.0f;
	ViewPortInfo.MinDepth = 0.0f;
	ViewPortInfo.MaxDepth = 1.0f;
}

void URenderer::RasterizerSetting()
{
	UEngineCore::GetDevice().GetContext()->RSSetViewports(1, &ViewPortInfo);
	UEngineCore::GetDevice().GetContext()->RSSetState(RasterizerState.Get());
}

void URenderer::PixelShaderInit()
{
	UEngineDirectory CurDir;
	CurDir.MoveParentToDirectory("EngineShader");
	UEngineFile File = CurDir.GetFile("EngineSpriteShader.fx");

	std::string Path = File.GetPathToString();
	std::wstring WPath = UEngineString::AnsiToUnicode(Path);
	std::string version = "ps_5_0";

	int Flag0 = 0;
	int Flag1 = 0;

#ifdef _DEBUG
	Flag0 = D3D10_SHADER_DEBUG;
#endif

	Flag0 |= D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;

	D3DCompileFromFile(
		WPath.c_str(),
		nullptr,
		nullptr,
		"PixelToWorld",
		version.c_str(),
		Flag0,
		Flag1,
		&PSShaderCodeBlob,
		&PSErrorCodeBlob
	);

	if (nullptr == PSShaderCodeBlob)
	{
		std::string ErrString = reinterpret_cast<char*>(PSErrorCodeBlob->GetBufferPointer());
		MSGASSERT(ErrString + "GetBufferPointer failed.");
		return;
	}

	HRESULT Result = UEngineCore::Device.GetDevice()->CreatePixelShader(
		PSShaderCodeBlob->GetBufferPointer(),
		PSShaderCodeBlob->GetBufferSize(),
		nullptr,
		&PixelShader
	);

	if (S_OK != Result)
	{
		MSGASSERT("CreatePixelShader failed");
	}
}

void URenderer::PixelShaderSetting()
{
	UEngineCore::GetDevice().GetContext()->PSSetShader(PixelShader.Get(), nullptr, 0);
}

void URenderer::OutPutMergeSetting()
{
	if (nullptr != Blend)
	{
		Blend->Setting();
	}

	ID3D11RenderTargetView* RTV = UEngineCore::Device.GetRTV();

	ID3D11RenderTargetView* ArrRtv[16] = { 0 };
	ArrRtv[0] = RTV;

	UEngineCore::GetDevice().GetContext()->OMSetRenderTargets(1, &ArrRtv[0], nullptr);
}
