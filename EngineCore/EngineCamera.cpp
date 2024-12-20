#include "PreCompile.h"
#include "EngineCamera.h"

#include "Renderer.h"

UEngineCamera::UEngineCamera()
{
}

UEngineCamera::~UEngineCamera()
{
}

void UEngineCamera::BeginPlay()
{
	FVector Scale = UEngineCore::GetScreenScale();

	ProjectionScale = Scale;
}

void UEngineCamera::Tick(float _DeltaTime)
{	
	Transform.View;
	Transform.Projection;
}

void UEngineCamera::Render(float _DeltaTime)
{
	for (std::pair<const int, std::list<std::shared_ptr<URenderer>>>& RenderGroup : Renderers)
	{
		std::list<std::shared_ptr<URenderer>>& RenderList = RenderGroup.second;

		for (std::shared_ptr<URenderer> Renderer : RenderList)
		{
			Renderer->Render(this, _DeltaTime);
		}
	}
}

void UEngineCamera::ChangeRenderGroup(int _PrevGroupOrder, std::shared_ptr<URenderer> _Renderer)
{
	Renderers[_PrevGroupOrder].remove(_Renderer);
	Renderers[_Renderer->GetOrder()].push_back(_Renderer);
}

void UEngineCamera::CalculateViewAndProjection()
{
	FTransform& Trans = GetTransformRef();

	Trans.View.View(Trans.World.ArrVector[3], Trans.World.GetFoward(), Trans.World.GetUp());

	Trans.Projection.OrthographicLH(ProjectionScale.X, ProjectionScale.Y, Near, Far);

}