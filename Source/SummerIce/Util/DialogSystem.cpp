#include "DialogSystem.h"
#include "GameFramework/Actor.h"
#include "SummerIce/StateAndTrigger/GameEvent.h"

DialogTree* DialogSystem::_DialogTree;

DialogTree::DialogMap* DialogSystem::_Dialog;
int32 DialogSystem::_DialogId;
DialogNode* DialogSystem::_Node;

TArray<int32>* DialogSystem::_LaviniaNodeArray;
int32 DialogSystem::_LaviniaNodeId;

TMap<ECharacter, IInteractInterface*> DialogSystem::_Speakers;
TMap<int32, int32> DialogSystem::_DialogNodeMap;



void DialogSystem::LoadDialogTree(const int32 & LvlId)
{
	_DialogTree = new DialogTree();
	_DialogTree->LoadDialogFromJson(LvlId);
	_DialogNodeMap.Empty();
	RemoveSpeakers();
}

void DialogSystem::AddSpeaker(const IInteractInterface * Actor)
{
	if (Actor) _Speakers.Emplace(Actor->GetName(), const_cast<IInteractInterface*>(Actor));	
}

void DialogSystem::RemoveSpeaker(const IInteractInterface * Actor)
{
	if (Actor) _Speakers.Remove(Actor->GetName());
}

void DialogSystem::RemoveSpeakers()
{
	_Speakers.Empty();

	_LaviniaNodeArray = nullptr;
	_LaviniaNodeId = 0;

	_Dialog = nullptr;
	_DialogId = -1;
	_Node = nullptr;
}

AActor * DialogSystem::FindItemInSpeaker()
{
  return Cast<AActor>(*_Speakers.Find(ECharacter::Object));
}

bool DialogSystem::IsDialogValid()
{
	if (!_Dialog || _DialogId == -1) {
		for (const auto& Speaker : _Speakers) {
			_DialogId = Speaker.Value->GetDialogId();
			_Dialog = _DialogTree->GetDialogById(_DialogId);
			if (_Dialog) return true;			
		}
    return false;
	}
	else {
		return true;
	}
}

bool DialogSystem::IsNodeValid()
{
	int32 NodeId = _DialogNodeMap.FindOrAdd(_DialogId);
	_Node = _Dialog->Find(NodeId);

	if (_Node) {
		if (_Node->Speaker != ECharacter::Lavinia && _Node->Answers.Num() > 1) {
			_LaviniaNodeArray = &_Node->Answers;
		}
		else if (_LaviniaNodeArray && !_LaviniaNodeArray->Contains(NodeId)) {
			_LaviniaNodeArray = nullptr;
			_LaviniaNodeId = 0;
		}

		return true;
	}

  _DialogId = -1;
	return false;	
}

bool DialogSystem::ShowCurrentNode()
{
  // пропустить пустую ноду и перейти к следующей
  // но в пустой ноде может быть действие - выполнить
  if (_Node->Speaker == ECharacter::Error) {
    
    if (_Node->Action == EGameEventType::RestartDialog) {
      _DialogNodeMap[_DialogId] = 0;
      return false;
    }
    else {
      UGameEvent::Instance()->CallDialogEvent(_Node->Action);
      ChooseNextNode();
      if (!IsNodeValid()) return false;  
    }
  
  }

	if (const auto& Actor = _Speakers.Find(_Node->Speaker)) {
		bool bCanChoose = (_LaviniaNodeArray) ? true : false;
		(*Actor)->ShowDialogWidget(&_Node->Speech, bCanChoose);
    UGameEvent::Instance()->CallDialogEvent(_Node->Action);
		ChooseNextNode();
	}
  return true;
}

void DialogSystem::ChooseNextNode()
{
	int32 Size = _Node->Answers.Num();

	// если говорит игрок, то выбрать следующей нодой случайный ответ нпс
	// в противном случае выбирается первый доступный
	if (_Node->Speaker == ECharacter::Lavinia && Size > 1)
		_DialogNodeMap[_DialogId] = _Node->Answers[FMath::Rand() % Size];
	else
		_DialogNodeMap[_DialogId] = (Size > 0) ? _Node->Answers[0] : -1;
}

void DialogSystem::NextNode()
{
	if (_LaviniaNodeArray) {
		_LaviniaNodeId = (_LaviniaNodeId + 1) % _LaviniaNodeArray->Num();
		_Node = _Dialog->Find((*_LaviniaNodeArray)[_LaviniaNodeId]);
		ShowCurrentNode();
	}
}

void DialogSystem::PrevNode()
{
	if (_LaviniaNodeArray) {
		_LaviniaNodeId = (_LaviniaNodeId > 0) ? (_LaviniaNodeId - 1) : (_LaviniaNodeArray->Num() - 1);
		_Node = _Dialog->Find((*_LaviniaNodeArray)[_LaviniaNodeId]);
		ShowCurrentNode();
	}
}

bool DialogSystem::StartOrContinueDialog()
{
	for (const auto& Speaker : _Speakers)
		Speaker.Value->HideDialogWidget();	

	if (IsDialogValid() && IsNodeValid()) {
		return ShowCurrentNode();
	}
	return false;
}
