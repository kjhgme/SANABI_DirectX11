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

    // ü���� ���� ��ġ ����
    void SetStartPosition(const FVector& _StartPosition);

    // ü���� �� ��ġ ����
    void SetEndPosition(const FVector& _EndPosition);

protected:
    void BeginPlay() override;
    void Tick(float _DeltaTime) override;

private:
    // ü�� ��ũ ����ü
    struct ChainLink
    {
        FVector position; // ��ũ�� ��ġ
        FVector velocity; // ��ũ�� �ӵ�
        float length;     // ���� ��ũ���� �Ÿ�
    };

    // ü�� �ʱ�ȭ
    void InitChain();

    // ü�� ������Ʈ
    void UpdateChain(float _DeltaTime);

    // ü�� ������ ������Ʈ
    void UpdateChainRenderer();

    // ü�� ������
    std::vector<std::shared_ptr<class USpriteRenderer>> ChainRenderers;

    // ü�� ��ũ��
    std::vector<ChainLink> Links;

    // ü�� ����
    int ChainLength = 30;

    // ��ũ �� �Ÿ�
    float LinkDistance = 1.0f;

    // �߷�
    float Gravity = -98.0f * 2.0f;

    // ü���� ���� ��ġ
    FVector StartPosition;

    // ü���� �� ��ġ
    FVector EndPosition;
};