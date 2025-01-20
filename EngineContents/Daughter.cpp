#include "PreCompile.h"
#include "Daughter.h"

#include "TextBubble.h"

ADaughter::ADaughter()
{
}

ADaughter::~ADaughter()
{
}

void ADaughter::MakeTextBubble(std::string_view _Text, float _Size)
{
	DaughterText = GetWorld()->SpawnActor<ATextBubble>();
	DaughterText->SetText(_Text, _Size);
	DaughterText->SetActorLocation(GetActorLocation());
}

void ADaughter::ClearTextBubble()
{
	if (DaughterText != nullptr)
	{
		DaughterText->Destroy();
	}
}