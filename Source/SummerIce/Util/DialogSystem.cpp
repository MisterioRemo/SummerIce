#include "DialogSystem.h"

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

bool DialogSystem::IsDialogValid()
{
	if (!_Dialog || _DialogId == -1) {
		for (const auto& Speaker : _Speakers) {
			_DialogId = Speaker.Value->GetDialogId();
			_Dialog = _DialogTree->GetDialogById(_DialogId);
			if (_Dialog) return true;			
		}
	}
	else {
		return true;
	}

	return false;
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

	return false;	
}

void DialogSystem::ShowCurrentNode()
{
	if (const auto& Actor = _Speakers.Find(_Node->Speaker)) {
		bool bCanChoose = (_LaviniaNodeArray) ? true : false;
		(*Actor)->ShowDialogWidget(&_Node->Speech, bCanChoose);
		ChooseNextNode();
	}
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
	for (const auto& Speaker : _Speakers) Speaker.Value->HideDialogWidget();	

	if (IsDialogValid() && IsNodeValid()) {
		ShowCurrentNode();
		return true;
	}
	return false;
}
