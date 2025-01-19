#include "PreCompile.h"
#include "TextBubble.h"

#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/EngineGraphicDevice.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/FontRenderer.h>
#include <EngineCore/EngineCore.h>

ATextBubble::ATextBubble()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	BubbleMarkerRenderer = CreateDefaultSubObject<USpriteRenderer>();
	BubbleRenderer = CreateDefaultSubObject<USpriteRenderer>();
	BubbleTailRenderer = CreateDefaultSubObject<USpriteRenderer>();
	TextRenderer = CreateDefaultSubObject<UFontRenderer>();

	BubbleRenderer->SetSprite("TextUI", 0);
	BubbleTailRenderer->SetSprite("TextUI", 1);

	BubbleMarkerRenderer->CreateAnimation("BubbleSelectionMarker", "BubbleSelectionMarker");
	BubbleMarkerRenderer->ChangeAnimation("BubbleSelectionMarker");

	BubbleRenderer->SetRelativeLocation({ 0.0f, 45.0f, -1.0f });
	BubbleTailRenderer->SetRelativeLocation({ 0.0f, 40.0f, -2.0f });
	BubbleMarkerRenderer->SetRelativeLocation({ 0.0f, 55.0f, -3.0f });

	TextRenderer->SetFont("PFStardust");
	TextRenderer->SetText("");

	BubbleRenderer->SetupAttachment(RootComponent);
	BubbleTailRenderer->SetupAttachment(RootComponent);
	BubbleMarkerRenderer->SetupAttachment(RootComponent);
	TextRenderer->SetupAttachment(RootComponent);
}

ATextBubble::~ATextBubble()
{
}

void ATextBubble::BeginPlay()
{
	AActor::BeginPlay();
}

void ATextBubble::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

}

void ATextBubble::SetText(std::string_view _Text, float _Size)
{
	TextRenderer->SetText(std::string(_Text));
	TextRenderer->SetSize(_Size);
}