#pragma once
#include "SceneComponent.h"

struct EngineVertex
{
public:
	FVector Pos;
	FVector Color;
};

class URenderer : public USceneComponent
{
	friend class ULevel;

public:
	ENGINEAPI URenderer();
	ENGINEAPI ~URenderer();

	URenderer(const URenderer& _Other) = delete;
	URenderer(URenderer&& _Other) noexcept = delete;
	URenderer& operator=(const URenderer& _Other) = delete;
	URenderer& operator=(URenderer&& _Other) noexcept = delete;

	void SetOrder(int _Order) override;

protected:
	ENGINEAPI void BeginPlay() override;

private:
	virtual void Render(float _DeltaTime);

public:
	ID3D11Buffer* VertexBuffer = nullptr;
	void InputAssembler1Init();
	void InputAssembler1Setting();
};

