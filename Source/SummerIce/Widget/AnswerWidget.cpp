#include "AnswerWidget.h"
#include "Components/Button.h"


bool UAnswerWidget::Initialize()
{
	if (!Super::Initialize())
		return false;

	if (!wAnswerButton)
		wAnswerButton = Cast<UButton>(this->GetWidgetFromName("AnswerButton"));

	return true;
}

void UAnswerWidget::SetName(const ECharacter & Character)
{
	_Name = GetCharacterAsString(Character);
}

void UAnswerWidget::SetSpeech(const FString & Speech)
{
	_Speech = Speech;
}

void UAnswerWidget::SetId(const int32 & Id)
{
	_AnswerId = Id;
}

int32 UAnswerWidget::GetId() const
{
	return _AnswerId;
}

// Вызывается в BP_AnswerBubble при выборе ответа
void UAnswerWidget::ClickToChooseAnswer()
{
	OnChooseAnswer.Broadcast(_AnswerId);
}