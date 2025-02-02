#include "PreCompile.h"
#include "Chain.h"

#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>

AChain::AChain()
{
    // Chain �ʱ�ȭ
    std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
    RootComponent = Default;

    ChainRenderers.resize(ChainLength);

    // Chain ������ �ʱ�ȭ
    for (int i = 0; i < ChainLength; ++i)
    {
        ChainRenderers[i] = CreateDefaultSubObject<USpriteRenderer>();
        ChainRenderers[i]->SetupAttachment(RootComponent);
        ChainRenderers[i]->SetSprite("SNB_Chain", 2); // ü�� ��ũ ��������Ʈ ����
        ChainRenderers[i]->SetAutoScaleRatio(1.0f);
    }
}

AChain::~AChain()
{
}

void AChain::BeginPlay()
{
    AActor::BeginPlay();

    // ü�� �ʱ�ȭ
    InitChain();
}

void AChain::Tick(float _DeltaTime)
{
    AActor::Tick(_DeltaTime);

    // ü�� ������Ʈ
    UpdateChain(_DeltaTime);
}

void AChain::InitChain()
{
    // ü�� ��ũ �ʱ�ȭ
    for (int i = 0; i < ChainLength; i++)
    {
        // PlayerRenderer�� GrabRenderer ������ ��ġ�� ������� ��ũ ��ġ ���
        float t = static_cast<float>(i) / (ChainLength - 1);
        FVector LinkPosition = FVector::Lerp(StartPosition, EndPosition, t);

        ChainLink link;
        link.position = LinkPosition;
        link.velocity = FVector::ZERO;
        link.length = LinkDistance;
        link.position.Z -= i;
        Links.push_back(link);
    }

    //// ü�� ��ũ �ʱ�ȭ
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
    // ù ��° ��ũ: Player ��ġ�� ����
    Links[0].position = StartPosition + FVector(0.0f, 20.0f, 0.0f);
    Links[0].velocity = FVector::ZERO; // �ӵ� �ʱ�ȭ

    // ������ ��ũ: Grab ��ġ�� ����
    Links.back().position = EndPosition;
    Links.back().velocity = FVector::ZERO; // �ӵ� �ʱ�ȭ

    // �߰� ��ũ�� ���� �ùķ��̼�
    for (size_t i = 1; i < Links.size() - 1; i++)
    {
        ChainLink& prevLink = Links[i - 1];
        ChainLink& currentLink = Links[i];
        ChainLink& nextLink = Links[i + 1];

        // �Ÿ� ���� ���� ����
        FVector deltaToPrev = currentLink.position - prevLink.position;
        float distanceToPrev = deltaToPrev.Length();
        float differenceToPrev = distanceToPrev - currentLink.length;
        FVector correctionToPrev = deltaToPrev.NormalizeReturn() * differenceToPrev * 0.5f;

        FVector deltaToNext = currentLink.position - nextLink.position;
        float distanceToNext = deltaToNext.Length();
        float differenceToNext = distanceToNext - currentLink.length;
        FVector correctionToNext = deltaToNext.NormalizeReturn() * differenceToNext * 0.5f;

        // ��ġ ����
        currentLink.position -= correctionToPrev;
        currentLink.position -= correctionToNext;

        // �ӵ� ������Ʈ
        // currentLink.velocity.Y += Gravity * _DeltaTime; // �߷� ����
        currentLink.position += currentLink.velocity * _DeltaTime;
    }

    // ü�� ������ ������Ʈ
    UpdateChainRenderer();
}

void AChain::UpdateChainRenderer()
{
    // ü�� ������ ������Ʈ
    for (size_t i = 0; i < Links.size(); i++)
    {
        // �� ��ũ�� ��ġ�� ������Ʈ
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