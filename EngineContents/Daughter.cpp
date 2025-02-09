#include "PreCompile.h"
#include "Daughter.h"

#include "TextBubble.h"

ADaughter::ADaughter()
{
}

ADaughter::~ADaughter()
{
}


void ADaughter::MakeTextBubble(std::string_view _Text, float _X, float _Y, float _BoxSize, float _TextSize)
{
	ClearTextBubble();

	DaughterText = GetWorld()->SpawnActor<ATextBubble>();
	DaughterText->SetText(_Text, _Y, _X, _BoxSize, _TextSize);
	DaughterText->SetActorLocation(GetActorLocation());
}

void ADaughter::ClearTextBubble()
{
	if (DaughterText != nullptr)
	{
		DaughterText->Destroy();
	}
}