#include "PreCompile.h"
#include "Chain.h"

#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>

AChain::AChain()
{
    // Chain 초기화
    std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
    RootComponent = Default;

    ChainRenderers.resize(ChainLength);

    // Chain 렌더러 초기화
    for (int i = 0; i < ChainLength; ++i)
    {
        ChainRenderers[i] = CreateDefaultSubObject<USpriteRenderer>();
        ChainRenderers[i]->SetupAttachment(RootComponent);
        ChainRenderers[i]->SetSprite("SNB_Chain", 2); // 체인 링크 스프라이트 설정
        ChainRenderers[i]->SetAutoScaleRatio(1.0f);
    }
}

AChain::~AChain()
{
}

void AChain::BeginPlay()
{
    AActor::BeginPlay();

    // 체인 초기화
    InitChain();
}

void AChain::Tick(float _DeltaTime)
{
    AActor::Tick(_DeltaTime);

    // 체인 업데이트
    UpdateChain(_DeltaTime);
}

void AChain::InitChain()
{
    // 체인 링크 초기화
    for (int i = 0; i < ChainLength; i++)
    {
        // PlayerRenderer와 GrabRenderer 사이의 위치를 기반으로 링크 위치 계산
        float t = static_cast<float>(i) / (ChainLength - 1);
        FVector LinkPosition = FVector::Lerp(StartPosition, EndPosition, t);

        ChainLink link;
        link.position = LinkPosition;
        link.velocity = FVector::ZERO;
        link.length = LinkDistance;
        link.position.Z -= i;
        Links.push_back(link);
    }

    //// 체인 링크 초기화
    //for (int i = 0; i < ChainLength; i++)
    //{
    //    ChainLink link;
    //    link.position = StartPosition + FVector(0.0f, -LinkDistance * i, 0.0f);
    //    link.velocity = FVector::ZERO;
    //    link.length = LinkDistance;
    //    Links.push_back(link);
    //}

}

void AChain::UpdateChain(float _DeltaTime)
{
    // 첫 번째 링크: Player 위치에 고정
    Links[0].position = StartPosition + FVector(0.0f, 20.0f, 0.0f);
    Links[0].velocity = FVector::ZERO; // 속도 초기화

    // 마지막 링크: Grab 위치에 고정
    Links.back().position = EndPosition;
    Links.back().velocity = FVector::ZERO; // 속도 초기화

    // 중간 링크들 물리 시뮬레이션
    for (size_t i = 1; i < Links.size() - 1; i++)
    {
        ChainLink& prevLink = Links[i - 1];
        ChainLink& currentLink = Links[i];
        ChainLink& nextLink = Links[i + 1];

        // 거리 제약 조건 적용
        FVector deltaToPrev = currentLink.position - prevLink.position;
        float distanceToPrev = deltaToPrev.Length();
        float differenceToPrev = distanceToPrev - currentLink.length;
        FVector correctionToPrev = deltaToPrev.NormalizeReturn() * differenceToPrev * 0.5f;

        FVector deltaToNext = currentLink.position - nextLink.position;
        float distanceToNext = deltaToNext.Length();
        float differenceToNext = distanceToNext - currentLink.length;
        FVector correctionToNext = deltaToNext.NormalizeReturn() * differenceToNext * 0.5f;

        // 위치 보정
        currentLink.position -= correctionToPrev;
        currentLink.position -= correctionToNext;

        // 속도 업데이트
        // currentLink.velocity.Y += Gravity * _DeltaTime; // 중력 적용
        currentLink.position += currentLink.velocity * _DeltaTime;
    }

    // 체인 렌더링 업데이트
    UpdateChainRenderer();
}

void AChain::UpdateChainRenderer()
{
    // 체인 렌더링 업데이트
    for (size_t i = 0; i < Links.size(); i++)
    {
        // 각 링크의 위치를 업데이트
        ChainRenderers[i]->SetWorldLocation(Links[i].position);
    }
}

void AChain::SetStartPosition(const FVector& _StartPosition)
{
    StartPosition = _StartPosition;
}

void AChain::SetEndPosition(const FVector& _EndPosition)
{
    EndPosition = _EndPosition;
}