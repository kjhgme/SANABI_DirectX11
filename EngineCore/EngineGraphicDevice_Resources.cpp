#include "PreCompile.h"
#include "EngineGraphicDevice.h"

#include "EngineDepthStencilState.h"
#include "EngineVertexBuffer.h"
#include "EngineIndexBuffer.h"
#include "EngineMaterial.h"
#include "EngineTexture.h"
#include "EngineShader.h"
#include "EngineVertex.h"
#include "EngineBlend.h"
#include "EngineFont.h"
#include "Mesh.h"

void UEngineGraphicDevice::DefaultResourcesInit()
{
	DepthStencilInit();
    TextureInit();
    MeshInit();
    BlendInit();
    RasterizerStateInit();
    ShaderInit();
    MaterialInit();

	UEngineFont::Load("�ü�", "�ü�");
	UEngineFont::Load("PFStardust", "PFStardust");
}

void UEngineGraphicDevice::DepthStencilInit()
{
	{
		D3D11_DEPTH_STENCIL_DESC Desc = { 0 };
		Desc.DepthEnable = true;
		Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		Desc.DepthFunc = D3D11_COMPARISON_LESS;
		Desc.StencilEnable = false;

		UEngineDepthStencilState::Create("BaseDepth", Desc);
	} 
	
	{
		D3D11_DEPTH_STENCIL_DESC Desc = { 0 };
		Desc.DepthEnable = false;
		Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		Desc.DepthFunc = D3D11_COMPARISON_LESS;
		Desc.StencilEnable = false;

		UEngineDepthStencilState::Create("UIDepth", Desc);
	}

	{
		D3D11_DEPTH_STENCIL_DESC Desc = { 0 };
		Desc.DepthEnable = true;
		Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		Desc.DepthFunc = D3D11_COMPARISON_ALWAYS;
		Desc.StencilEnable = false;

		UEngineDepthStencilState::Create("CollisionDebugDepth", Desc);
	}

	{
		D3D11_DEPTH_STENCIL_DESC Desc = { 0 };
		Desc.DepthEnable = true;
		Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		Desc.DepthFunc = D3D11_COMPARISON_ALWAYS;
		Desc.StencilEnable = false;

		UEngineDepthStencilState::Create("TargetMerge", Desc);
	}
}

void UEngineGraphicDevice::MeshInit()
{
	{
		std::vector<FEngineVertex> Vertexes;
		Vertexes.resize(4);
		Vertexes[0] = FEngineVertex{ FVector(-0.5f, 0.5f, 0.0f), {0.0f , 0.0f }, {1.0f, 0.0f, 0.0f, 1.0f} };
		Vertexes[1] = FEngineVertex{ FVector(0.5f, 0.5f, 0.0f), {1.0f , 0.0f } , {0.0f, 1.0f, 0.0f, 1.0f} };
		Vertexes[2] = FEngineVertex{ FVector(-0.5f, -0.5f, 0.0f), {0.0f , 1.0f } , {0.0f, 0.0f, 1.0f, 1.0f} };
		Vertexes[3] = FEngineVertex{ FVector(0.5f, -0.5f, 0.0f), {1.0f , 1.0f } , {1.0f, 1.0f, 1.0f, 1.0f} };

		UEngineVertexBuffer::Create("Rect", Vertexes);
	}

	{
		std::vector<unsigned int> Indexes;

		Indexes.push_back(0);
		Indexes.push_back(1);
		Indexes.push_back(2);

		Indexes.push_back(1);
		Indexes.push_back(3);
		Indexes.push_back(2);
		UEngineIndexBuffer::Create("Rect", Indexes);
	}

	{
		std::vector<FEngineVertex> Vertexes;
		Vertexes.resize(4);
		Vertexes[0] = FEngineVertex{ FVector(-1.0f, 1.0f, 0.0f), {0.0f , 0.0f }, {1.0f, 0.0f, 0.0f, 1.0f} };
		Vertexes[1] = FEngineVertex{ FVector(1.0f, 1.0f, 0.0f), {1.0f , 0.0f } , {0.0f, 1.0f, 0.0f, 1.0f} };
		Vertexes[2] = FEngineVertex{ FVector(-1.0f, -1.0f, 0.0f), {0.0f , 1.0f } , {0.0f, 0.0f, 1.0f, 1.0f} };
		Vertexes[3] = FEngineVertex{ FVector(1.0f, -1.0f, 0.0f), {1.0f , 1.0f } , {1.0f, 1.0f, 1.0f, 1.0f} };

		UEngineVertexBuffer::Create("FullRect", Vertexes);
	}

	{
		UMesh::Create("Rect");
		UMesh::Create("FullRect", "FullRect", "Rect");
	}
}

void UEngineGraphicDevice::BlendInit()
{
	D3D11_BLEND_DESC Desc = { 0 };

	Desc.AlphaToCoverageEnable = false;
	Desc.IndependentBlendEnable = true;
	Desc.RenderTarget[0].BlendEnable = true;
	Desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	Desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	Desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	Desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
    Desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_MAX;
	Desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	Desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;

	UEngineBlend::Create("AlphaBlend", Desc);
}

void UEngineGraphicDevice::ShaderInit()
{
	UEngineDirectory CurDir;
	CurDir.MoveParentToDirectory("EngineShader");

	std::vector<UEngineFile> ShaderFiles = CurDir.GetAllFile(true, { ".fx", ".hlsl" });

	for (size_t i = 0; i < ShaderFiles.size(); i++)
	{
		UEngineShader::ReflectionCompile(ShaderFiles[i]);
	}
}

void UEngineGraphicDevice::MaterialInit()
{
	{
		std::shared_ptr<UEngineMaterial> Mat = UEngineMaterial::Create("SpriteMaterial");
		Mat->SetVertexShader("EngineSpriteShader.fx");
		Mat->SetPixelShader("EngineSpriteShader.fx");
	}

	{
		std::shared_ptr<UEngineMaterial> Mat = UEngineMaterial::Create("WidgetMaterial");
		Mat->SetVertexShader("EngineSpriteShader.fx");
		Mat->SetPixelShader("EngineSpriteShader.fx");
		Mat->SetDepthStencilState("UIDepth");
	}

	{
		std::shared_ptr<UEngineMaterial> Mat = UEngineMaterial::Create("CollisionDebugMaterial");
		Mat->SetVertexShader("EngineDebugCollisionShader.fx");
		Mat->SetPixelShader("EngineDebugCollisionShader.fx");

		Mat->SetDepthStencilState("CollisionDebugDepth");
		Mat->SetRasterizerState("CollisionDebugRas");
	}

	{
		std::shared_ptr<UEngineMaterial> Mat = UEngineMaterial::Create("TileMap");
		Mat->SetVertexShader("EngineTileMapShader.fx");
		Mat->SetPixelShader("EngineTileMapShader.fx");
	}

	{
		std::shared_ptr<UEngineMaterial> Mat = UEngineMaterial::Create("TargetMerge");
		Mat->SetVertexShader("EngineTargetMergeShader.fx");
		Mat->SetPixelShader("EngineTargetMergeShader.fx");
		Mat->SetDepthStencilState("TargetMerge");
	}
}

void UEngineGraphicDevice::RasterizerStateInit()
{
	{
		D3D11_RASTERIZER_DESC Desc = {};
		Desc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
		Desc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;

		UEngineRasterizerState::Create("EngineBase", Desc);
	}

	{
		D3D11_RASTERIZER_DESC Desc = {};
		Desc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
		Desc.FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;

		UEngineRasterizerState::Create("CollisionDebugRas", Desc);
	}
}

void UEngineGraphicDevice::TextureInit()
{
	D3D11_SAMPLER_DESC SampInfo = { D3D11_FILTER::D3D11_FILTER_MIN_MAG_MIP_POINT };
	SampInfo.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
	SampInfo.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
	SampInfo.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_CLAMP;

	SampInfo.BorderColor[0] = 0.0f;
	SampInfo.BorderColor[1] = 0.0f;
	SampInfo.BorderColor[2] = 0.0f;
	SampInfo.BorderColor[3] = 0.0f;

	UEngineSampler::Create("WRAPSampler", SampInfo);

	{
		UEngineDirectory Dir;
		if (false == Dir.MoveParentToDirectory("EngineShader"))
		{
			MSGASSERT("EngineShader path is false.");
			return;
		}
		std::vector<UEngineFile> ImageFiles = Dir.GetAllFile(true, { ".PNG", ".BMP", ".JPG" });
		for (size_t i = 0; i < ImageFiles.size(); i++)
		{
			std::string FilePath = ImageFiles[i].GetPathToString();
			UEngineTexture::Load(FilePath);
		}
	}
}
