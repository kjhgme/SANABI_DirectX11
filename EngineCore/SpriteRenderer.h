#pragma once
#include "Renderer.h"

class USpriteRenderer : public URenderer
{
public:
	ENGINEAPI USpriteRenderer();
	ENGINEAPI ~USpriteRenderer();

	USpriteRenderer(const USpriteRenderer& _Other) = delete;
	USpriteRenderer(USpriteRenderer&& _Other) noexcept = delete;
	USpriteRenderer& operator=(const USpriteRenderer& _Other) = delete;
	USpriteRenderer& operator=(USpriteRenderer&& _Other) noexcept = delete;

protected:

private:

};

