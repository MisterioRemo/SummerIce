#include "DialogWidget.h"
#include "Util/DialogTree.h"

#include "UObject/ConstructorHelpers.h"
#include "Components/VerticalBox.h"
#include "Widget/AnswerWidget.h"


UDialogWidget::UDialogWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	if (!DialogAnswerClass) {
		// исходная ссылка WidgetBlueprint'/Game/Widget/W_AnswerBubble.W_AnswerBubble'
		// в ней нужно изменить WidgetBlueprint -> WidgetBlueprintGeneratedClass
		// и W_AnswerBubble -> W_AnswerBubble_C
		static ConstructorHelpers::FClassFinder<UUserWidget> Finded(TEXT("WidgetBlueprintGeneratedClass'/Game/Widget/W_AnswerBubble.W_AnswerBubble_C'"));
		if (Finded.Succeeded())
			DialogAnswerClass = Finded.Class;
	}
}

bool UDialogWidget::Initialize()
{
	if (!Super::Initialize())
		return false;

	if (!wAnswerContainer)
		wAnswerContainer = Cast<UVerticalBox>(this->GetWidgetFromName("AnswerContainer"));	
	
	return true;
}

void UDialogWidget::SetChosenNodeId(const int32 & NodeId)
{
	_ChosenNodeId = NodeId;
}

void UDialogWidget::ShowCurrentNode(const DialogNode & Node, const uint32 & NodeId)
{
	if (DialogAnswerClass) {
		UAnswerWidget * wAnswerBubble = CreateWidget<UAnswerWidget>(this, DialogAnswerClass);
		wAnswerBubble->SetName(Node.Speaker);
		wAnswerBubble->SetSpeech(Node.Speech);
		wAnswerBubble->SetId(NodeId);
		wAnswerBubble->OnChooseAnswer.AddDynamic(this, &UDialogWidget::SetChosenNodeId);
		wAnswerContainer->AddChildToVerticalBox(wAnswerBubble);
	}
}

void UDialogWidget::ShowClidrenNode(const DialogNode & ParentNode, const uint32 & NodeId)
{
	for (const uint32 & Id : ParentNode.answers) {
		const DialogNode * Node = _DialogTree->GetNodeById(Id);
		ShowCurrentNode(*Node, Id);
	}
}

// Продолжения диалога, в рамках одного DialogId (т.е. меняется _CurrentNodeId)
void UDialogWidget::ContinueDialog(const uint32 & NodeId, const bool & bSingleMode)
{
	wAnswerContainer->ClearChildren();
	const DialogNode * Node = _DialogTree->GetNodeById(NodeId);

	if (Node) {
		if (bSingleMode) ShowCurrentNode(*Node, NodeId);
		else ShowClidrenNode(*Node, NodeId);

		_ChosenNodeId = (Node->answers.empty()) ? _CurrentNodeId : Node->answers[0];
	}
	else 
		UE_LOG(LogTemp, Warning, TEXT("UDialogWidget::ContinueDialog: can't find dialog node [inddex = %d]"), NodeId);
	
	if (_CurrentNodeId == _ChosenNodeId) 
		this->SetVisibility(ESlateVisibility::Hidden);
}

// Загружается диалог по номеру уровня и индексу диалога
void UDialogWidget::StartDialog(const int32 & LvlId, const int32 & DialogId)
{
	this->SetVisibility(ESlateVisibility::Visible);

	if (_DialogTree && _DialogTree->GetLevelId() == LvlId && _DialogTree->GetDialogId() == DialogId) {
		ContinueDialog(_CurrentNodeId, false);
		return;		
	}

	_DialogTree = TSharedPtr<DialogTree>(new DialogTree());
	_DialogTree->LoadDialogFromJson(LvlId, DialogId);

	// Первый узел в диалоге всегда пустой и печатаются только его ответы
	_CurrentNodeId = 0;
	ContinueDialog(_CurrentNodeId, false);
}

// Вызывается в BP_DialogBubble
void UDialogWidget::ClickToExit()
{
	this->SetVisibility(ESlateVisibility::Hidden);
}

// Вызывается в BP_DialogBubble
void UDialogWidget::ClickToContinue()
{
	_CurrentNodeId = _ChosenNodeId;	
	ContinueDialog(_ChosenNodeId, false);		
}

