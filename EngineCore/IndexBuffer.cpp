#include "PreCompile.h"
#include "IndexBuffer.h"

UIndexBuffer::UIndexBuffer()
{
}

UIndexBuffer::~UIndexBuffer()
{
}

std::shared_ptr<UIndexBuffer> UIndexBuffer::Create(std::string_view _Name, const void* _InitData, size_t _VertexSize, size_t _VertexCount)
{
	std::string UpperName = ToUpperName(_Name);

	if (true == Contains(UpperName))
	{
		MSGASSERT(UpperName + " is already contained.");
		return nullptr;
	}

	std::shared_ptr<UIndexBuffer> NewRes = std::make_shared<UIndexBuffer>();
	PushRes<UIndexBuffer>(NewRes, _Name, "");
	NewRes->ResCreate(_InitData, _VertexSize, _VertexCount);

	return NewRes;
}

void UIndexBuffer::ResCreate(const void* _InitData, size_t _Size, size_t _Count)
{
	BufferInfo.ByteWidth = static_cast<UINT>(_Size * _Count);
	BufferInfo.BindFlags = D3D11_BIND_INDEX_BUFFER;
	BufferInfo.CPUAccessFlags = 0;
	BufferInfo.Usage = D3D11_USAGE_DEFAULT;

	D3D11_SUBRESOURCE_DATA Data; // 초기값 넣어주는 용도의 구조체
	Data.pSysMem = _InitData;

	if (S_OK != UEngineCore::GetDevice().GetDevice()->CreateBuffer(&BufferInfo, &Data, IndexBuffer.GetAddressOf()))
	{
		MSGASSERT("CreateBuffer failed.");
		return;
	}
}