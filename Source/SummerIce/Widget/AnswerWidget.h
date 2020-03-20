#pragma once

#include "Blueprint/UserWidget.h"
#include "Util/CharacterEnum.h"
#include "AnswerWidget.generated.h"

class UButton;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChooseAnswer, const int32 &, AnswerId);

UCLASS()
class SUMMERICE_API UAnswerWidget : public UUserWidget
{
	GENERATED_BODY()

private:

protected:
	virtual bool Initialize() override;

	// Выбор ответа в диалоге
	UFUNCTION(BlueprintCallable, Category = "Dialog action")
	void ClickToChooseAnswer();

public:
	void SetName(const ECharacter & Character);
	void SetSpeech(const FString & Speech);
	void SetId(const int32 & Id);
	int32 GetId() const;

private:
	UButton * wAnswerButton;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widget Text")
	FString _Speech;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widget Text")
	FString _Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widget Text")
	int32 _AnswerId;

public:
	UPROPERTY(BlueprintAssignable, Category = "Delegate")
	FOnChooseAnswer OnChooseAnswer;
};
