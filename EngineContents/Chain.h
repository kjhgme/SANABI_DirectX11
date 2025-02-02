#pragma once
#include <EngineCore/Actor.h>

class AChain : public AActor
{
public:
    AChain();
    ~AChain();

    AChain(const AChain& _Other) = delete;
    AChain(AChain&& _Other) noexcept = delete;
    AChain& operator=(const AChain& _Other) = delete;
    AChain& operator=(AChain&& _Other) noexcept = delete;

    // 체인의 시작 위치 설정
    void SetStartPosition(const FVector& _StartPosition);

    // 체인의 끝 위치 설정
    void SetEndPosition(const FVector& _EndPosition);

protected:
    void BeginPlay() override;
    void Tick(float _DeltaTime) override;

private:
    // 체인 링크 구조체
    struct ChainLink
    {
        FVector position; // 링크의 위치
        FVector velocity; // 링크의 속도
        float length;     // 이전 링크와의 거리
    };

    // 체인 초기화
    void InitChain();

    // 체인 업데이트
    void UpdateChain(float _DeltaTime);

    // 체인 렌더링 업데이트
    void UpdateChainRenderer();

    // 체인 렌더러
    std::vector<std::shared_ptr<class USpriteRenderer>> ChainRenderers;

    // 체인 링크들
    std::vector<ChainLink> Links;

    // 체인 길이
    int ChainLength = 30;

    // 링크 간 거리
    float LinkDistance = 1.0f;

    // 중력
    float Gravity = -98.0f * 2.0f;

    // 체인의 시작 위치
    FVector StartPosition;

    // 체인의 끝 위치
    FVector EndPosition;
};