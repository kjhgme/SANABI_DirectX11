#include "PreCompile.h"
#include "TextBubble.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineGraphicDevice.h>
#include <EngineCore/EngineCore.h>

ATextBubble::ATextBubble()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	BubbleMarkerRenderer = CreateDefaultSubObject<USpriteRenderer>();
	BubbleRenderer = CreateDefaultSubObject<USpriteRenderer>();
	BubbleTailRenderer = CreateDefaultSubObject<USpriteRenderer>();

	BubbleRenderer->SetSprite("TextUI", 0);
	BubbleTailRenderer->SetSprite("TextUI", 1);

	BubbleMarkerRenderer->CreateAnimation("BubbleSelectionMarker", "BubbleSelectionMarker");
	BubbleMarkerRenderer->ChangeAnimation("BubbleSelectionMarker");

	BubbleRenderer->SetRelativeLocation({ 0.0f, 50.0f, -1.0f });
	BubbleTailRenderer->SetRelativeLocation({ 0.0f, 40.0f, -1.0f });
	BubbleMarkerRenderer->SetRelativeLocation({ 0.0f, 55.0f, -1.0f });

	BubbleMarkerRenderer->SetAutoScaleRatio(5.0f);

	BubbleRenderer->SetupAttachment(RootComponent);
	BubbleTailRenderer->SetupAttachment(RootComponent);
	BubbleMarkerRenderer->SetupAttachment(RootComponent);
}

ATextBubble::~ATextBubble()
{
}

void ATextBubble::BeginPlay()
{
	AActor::BeginPlay();

	SetText();
}

void ATextBubble::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

}

void ATextBubble::SetText()
{
	UEngineGraphicDevice& test = UEngineCore::GetDevice();

	test.RenderText("한글가능?", 100.f, 10.f, 10.0f);
}