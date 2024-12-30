#include "PreCompile.h"
#include "EngineGraphicDevice.h"

#include "EngineVertex.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Mesh.h"

void UEngineGraphicDevice::DefaultResourcesInit()
{
    MeshInit();
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
