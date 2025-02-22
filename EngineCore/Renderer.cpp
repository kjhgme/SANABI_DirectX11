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

void URenderer::BeginPlay()
{
	USceneComponent::BeginPlay();
	SetOrder(GetOrder());
}

void URenderer::Render(UEngineCamera* _Camera, float _DeltaTime)
{
	this->CameraTransUpdate(_Camera);
	for (size_t i = 0; i < Units.size(); i++)
	{
		Units[i].Render(_Camera, _DeltaTime);
	}
}

URenderUnit& URenderer::GetRenderUnit(UINT _Index)
{
	return Units[_Index];
}

void URenderer::SetOrder(int _Order)
{
	if (0 != GetOrder() && _Order == GetOrder())
	{
		return;
	}
	int PrevOrder = GetOrder();
	UObject::SetOrder(_Order);
	ULevel* Level = GetActor()->GetWorld();

	std::shared_ptr<URenderer> RendererPtr = GetThis<URenderer>();
	Level->ChangeRenderGroup(0, PrevOrder, RendererPtr);
}

void URenderer::SetMesh(std::string_view _Name, UINT _Index /*= 0*/)
{
	URenderUnit& Unit = GetRenderUnit(_Index);
	Unit.SetMesh(_Name);
}

void URenderer::SetMaterial(std::string_view _Name, UINT _Index /*= 0*/)
{
	URenderUnit& Unit = GetRenderUnit(_Index);
	Unit.SetMaterial(_Name);
}

URenderUnit& URenderer::CreateRenderUnit()
{
	URenderUnit& NewUnit = Units.emplace_back();
	NewUnit.ParentRenderer = this;
	return NewUnit;
}