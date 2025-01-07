#pragma once
#include <EngineCore/Actor.h>

class AMari : public AActor
{
public:
	AMari();
	~AMari();

	AMari(const AMari& _Other) = delete;
	AMari(AMari&& _Other) noexcept = delete;
	AMari& operator=(const AMari& _Other) = delete;
	AMari& operator=(AMari&& _Other) noexcept = delete;

	void InitPlayerAnimation();

protected:

private:
	std::shared_ptr<class USpriteRenderer> MariRenderer;
};

