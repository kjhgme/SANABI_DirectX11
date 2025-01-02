#pragma once
#include "SceneComponent.h"
#include "EngineSprite.h"
#include "RenderUnit.h"

struct FUVValue
{
	float4 PlusUVValue;
};

class URenderer : public USceneComponent
{
	friend class UEngineCamera;

public:
	ENGINEAPI URenderer();
	ENGINEAPI ~URenderer();

	URenderer(const URenderer& _Other) = delete;
	URenderer(URenderer&& _Other) noexcept = delete;
	URenderer& operator=(const URenderer& _Other) = delete;
	URenderer& operator=(URenderer&& _Other) noexcept = delete;

	// SetFunction
	ENGINEAPI void SetOrder(int _Order) override;

	ENGINEAPI void SetTexture(std::string_view _Value);

	ENGINEAPI void SetTexture(UEngineTexture* _Texture);

	ENGINEAPI void SetSpriteData(UEngineSprite* _Sprite, size_t _Index);

	ENGINEAPI void SetMesh(std::string_view _Name);

	ENGINEAPI void SetBlend(std::string_view _Name);

	// Function
	ENGINEAPI void AddUVPlusValue(float4 _Value);

protected:
	ENGINEAPI void BeginPlay() override;
	ENGINEAPI virtual void Render(UEngineCamera* _Camera, float _DeltaTime);

private:

public:
	FSpriteData SpriteData;
	FUVValue UVValueData;
	UEngineTexture* Texture = nullptr;
	class UMesh* Mesh = nullptr;
	class UEngineBlend* Blend = nullptr;

	Microsoft::WRL::ComPtr<ID3D11SamplerState> SamplerState = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Buffer> TransformConstBuffer = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Buffer> SpriteConstBuffer = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Buffer> UVValue = nullptr;
	void ShaderResInit();
	void ShaderResSetting();

	Microsoft::WRL::ComPtr<ID3D11InputLayout> InputLayOut = nullptr;
	void InputAssembler1Setting();
	void InputAssembler1LayOut();

	Microsoft::WRL::ComPtr<ID3DBlob> VSShaderCodeBlob = nullptr;
	Microsoft::WRL::ComPtr<ID3DBlob> VSErrorCodeBlob = nullptr;
	Microsoft::WRL::ComPtr<ID3D11VertexShader> VertexShader = nullptr;
	void VertexShaderInit();
	void VertexShaderSetting();

	D3D11_PRIMITIVE_TOPOLOGY Topology = D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	void InputAssembler2Setting();

	Microsoft::WRL::ComPtr<ID3D11RasterizerState> RasterizerState = nullptr;
	void RasterizerInit();
	void RasterizerSetting();

	Microsoft::WRL::ComPtr<ID3DBlob> PSShaderCodeBlob = nullptr;
	Microsoft::WRL::ComPtr<ID3DBlob> PSErrorCodeBlob = nullptr;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> PixelShader = nullptr;
	void PixelShaderInit();
	void PixelShaderSetting();

	void OutPutMergeSetting();

	std::vector<URenderUnit> Units;
};