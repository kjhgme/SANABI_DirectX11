#include "PreCompile.h"
#include "TextBubble.h"
#include "ContentsEnum.h"

#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/EngineGraphicDevice.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/FontRenderer.h>
#include <EngineCore/EngineCore.h>
#include <EngineCore/FontWidget.h>

ATextBubble::ATextBubble()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	BubbleMarkerRenderer = CreateDefaultSubObject<USpriteRenderer>();
	BubbleLRenderer = CreateDefaultSubObject<USpriteRenderer>();
	BubbleMRenderer = CreateDefaultSubObject<USpriteRenderer>();
	BubbleRRenderer = CreateDefaultSubObject<USpriteRenderer>();
	BubbleTailRenderer = CreateDefaultSubObject<USpriteRenderer>();
	TextRenderer = CreateDefaultSubObject<UFontRenderer>();

	BubbleLRenderer->SetSprite("TextUI", 0);
	BubbleMRenderer->SetSprite("TextUI", 1);
	BubbleRRenderer->SetSprite("TextUI", 2);
	BubbleTailRenderer->SetSprite("TextUI", 3);

	BubbleMarkerRenderer->CreateAnimation("BubbleSelectionMarker", "BubbleSelectionMarker");
	BubbleMarkerRenderer->ChangeAnimation("BubbleSelectionMarker");

	BubbleLRenderer->SetRelativeLocation({ 0.0f, 45.0f, static_cast<float>(ERenderOrder::UI) });
	BubbleMRenderer->SetRelativeLocation({ 0.0f, 45.0f, static_cast<float>(ERenderOrder::UI) });
	BubbleRRenderer->SetRelativeLocation({ 0.0f, 45.0f, static_cast<float>(ERenderOrder::UI) });
	BubbleTailRenderer->SetRelativeLocation({ 0.0f, 40.0f, static_cast<float>(ERenderOrder::UI) -1.0f });
	BubbleMarkerRenderer->SetRelativeLocation({ 0.0f, 55.0f, static_cast<float>(ERenderOrder::UI) -2.0f });

	TextRenderer->SetRelativeLocation(BubbleMRenderer->GetWorldLocation());
	TextRenderer->AddRelativeLocation({ 0, 0, static_cast<float>(ERenderOrder::UI) - 3.0f });

	TextRenderer->SetFont("PFStardust");
	TextRenderer->SetText("");

	BubbleLRenderer->SetupAttachment(RootComponent);
	BubbleMRenderer->SetupAttachment(RootComponent);
	BubbleRRenderer->SetupAttachment(RootComponent);
	BubbleTailRenderer->SetupAttachment(RootComponent);
	BubbleMarkerRenderer->SetupAttachment(RootComponent);
	TextRenderer->SetupAttachment(RootComponent);

	BubbleLRenderer->SetAutoScale(false);
	BubbleMRenderer->SetAutoScale(false);
	BubbleRRenderer->SetAutoScale(false);
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
	BubbleLRenderer->AddRelativeLocation({ (- _Size * static_cast<float>(_Text.size()) / 5.0f) / 2.0f, 0.0f, 0.0f});
	BubbleRRenderer->AddRelativeLocation({ (_Size * static_cast<float>(_Text.size()) / 5.0f) / 2.0f + 1.0f, 0.0f, 0.0f });
	BubbleLRenderer->SetScale3D({ 5.0f, _Size / 2.0f, 1.0f });
	BubbleMRenderer->SetScale3D({ _Size * static_cast<float>(_Text.size()) / 5.0f, _Size / 2.0f, 1.0f});
	BubbleRRenderer->SetScale3D({ 5.0f, _Size / 2.0f, 1.0f });

	TextRenderer->SetText(std::string(_Text));
	TextRenderer->SetSize(_Size);
}