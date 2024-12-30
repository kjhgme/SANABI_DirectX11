#include "PreCompile.h"
#include "EngineGraphicDevice.h"

#include "EngineVertex.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "EngineBlend.h"
#include "Mesh.h"

void UEngineGraphicDevice::DefaultResourcesInit()
{
    MeshInit();
    BlendInit();
}

void UEngineGraphicDevice::MeshInit()
{
    {
        std::vector<EngineVertex> Vertexes;
        Vertexes.resize(4);
        Vertexes[0] = EngineVertex{ FVector(-0.5f, 0.5f, -0.0f), {0.0f , 0.0f }, {1.0f, 0.0f, 0.0f, 1.0f} };
        Vertexes[1] = EngineVertex{ FVector(0.5f, 0.5f, -0.0f), {1.0f , 0.0f } , {0.0f, 1.0f, 0.0f, 1.0f} };
        Vertexes[2] = EngineVertex{ FVector(-0.5f, -0.5f, -0.0f), {0.0f , 1.0f } , {0.0f, 0.0f, 1.0f, 1.0f} };
        Vertexes[3] = EngineVertex{ FVector(0.5f, -0.5f, -0.0f), {1.0f , 1.0f } , {1.0f, 1.0f, 1.0f, 1.0f} };

        UVertexBuffer::Create("Rect", Vertexes);
    }

    {
        std::vector<unsigned int> Indexes;

        Indexes.push_back(0);
        Indexes.push_back(1);
        Indexes.push_back(2);

        Indexes.push_back(1);
        Indexes.push_back(3);
        Indexes.push_back(2);


        UIndexBuffer::Create("Rect", Indexes);
    }

    {
        UMesh::Create("Rect");
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
    Desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	Desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	Desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;

	UEngineBlend::Create("AlphaBlend", Desc);
}

