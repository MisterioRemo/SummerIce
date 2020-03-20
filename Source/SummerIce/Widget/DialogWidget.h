#pragma once

#include "Blueprint/UserWidget.h"
#include "Util/CharacterEnum.h"
#include "DialogWidget.generated.h"

class DialogTree;
struct DialogNode;

class UVerticalBox;
class UAnswerWidget;

UCLASS()
class SUMMERICE_API UDialogWidget : public UUserWidget
{
	GENERATED_BODY()

private:	
	// Должен быть с UFUNCTION, потому что используется делегатом
	UFUNCTION()
	void SetChosenNodeId(const int32 & NodeId);

	void ContinueDialog(const uint32 & NodeId = 0, const bool & bSingleMode = true);
	void ShowCurrentNode(const DialogNode & Node, const uint32 & NodeId);
	void ShowClidrenNode(const DialogNode & ParentNode, const uint32 & NodeId);

protected:
	virtual bool Initialize() override;

	UFUNCTION(BlueprintCallable, Category = "Dialog buttons")
	void ClickToExit();

	UFUNCTION(BlueprintCallable, Category = "Dialog buttons")
	void ClickToContinue();

public:
	UDialogWidget(const FObjectInitializer& ObjectInitializer);

	void StartDialog(const int32 & LvlId, const int32 & DialogId);

private:
	TSharedPtr<DialogTree> _DialogTree;
	uint32 _CurrentNodeId;
	uint32 _ChosenNodeId;

	UVerticalBox * wAnswerContainer;
	TSubclassOf<UAnswerWidget> DialogAnswerClass;

protected:
public:
};
