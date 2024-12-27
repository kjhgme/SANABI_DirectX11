#pragma once
class RenderUnit
{
public:
	RenderUnit();
	~RenderUnit();

	RenderUnit(const RenderUnit& _Other) = delete;
	RenderUnit(RenderUnit&& _Other) noexcept = delete;
	RenderUnit& operator=(const RenderUnit& _Other) = delete;
	RenderUnit& operator=(RenderUnit&& _Other) noexcept = delete;

protected:

private:

};

