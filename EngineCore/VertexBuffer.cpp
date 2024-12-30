#include "PreCompile.h"
#include "VertexBuffer.h"

UVertexBuffer::UVertexBuffer()
{
}

UVertexBuffer::~UVertexBuffer()
{
}

std::shared_ptr<UVertexBuffer> UVertexBuffer::Create(std::string_view _Name, const void* _InitData, size_t _VertexSize, size_t _VertexCount)
{
	std::string UpperName = ToUpperName(_Name);

	if (true == Contains(UpperName))
	{
		MSGASSERT(UpperName + " is already contained.");
		return nullptr;
	}

	std::shared_ptr<UVertexBuffer> NewRes = std::make_shared<UVertexBuffer>();
	PushRes<UVertexBuffer>(NewRes, _Name, "");
	NewRes->ResCreate(_InitData, _VertexSize, _VertexCount);

	return NewRes;
}

void UVertexBuffer::Setting()
{
	UINT Offset = 0;
	ID3D11Buffer* ArrBuffer[1];
	ArrBuffer[0] = VertexBuffer.Get();
	UEngineCore::GetDevice().GetContext()->IASetVertexBuffers(0, 1, ArrBuffer, &VertexSize, &Offset);
}

void UVertexBuffer::ResCreate(const void* _InitData, size_t _VertexSize, size_t _VertexCount)
{
	VertexSize = static_cast<UINT>(_VertexSize);
	VertexCount = static_cast<UINT>(_VertexCount);

	BufferInfo.ByteWidth = static_cast<UINT>(_VertexSize * _VertexCount);
	BufferInfo.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	BufferInfo.CPUAccessFlags = 0;
	BufferInfo.Usage = D3D11_USAGE_DEFAULT;

	D3D11_SUBRESOURCE_DATA Data;
	Data.pSysMem = _InitData;

	if (S_OK != UEngineCore::GetDevice().GetDevice()->CreateBuffer(&BufferInfo, &Data, &VertexBuffer))
	{
		MSGASSERT("CreateBuffer failed.");
		return;
	}
}