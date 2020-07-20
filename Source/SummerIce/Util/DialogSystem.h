#pragma once

#include "SummerIce/Util/DialogTree.h"
#include "SummerIce/Interface/InteractInterface.h"

class ASummerIceGameModeBase;

class SUMMERICE_API DialogSystem
{

	friend ASummerIceGameModeBase;

private:
	static void LoadDialogTree(const int32 & LvlId);
	static bool IsDialogValid();
	static bool IsNodeValid();
	static void ShowCurrentNode();
	static void ChooseNextNode();

protected:
public:
	static void AddSpeaker(const IInteractInterface * Actor);
	static void RemoveSpeaker(const IInteractInterface * Actor);
	static void RemoveSpeakers();

	static void NextNode();
	static void PrevNode();

	static bool StartOrContinueDialog();

private:
	static DialogTree* _DialogTree;					// содержит все диалоги уровня
	static DialogTree::DialogMap* _Dialog;  // текущий диалог (содержит все узлы)	
	static int32 _DialogId;
	static DialogNode* _Node;						    // текущий узел

	static int32 _LaviniaNodeId;
	static TArray<int32>* _LaviniaNodeArray;

	static TMap<ECharacter, IInteractInterface*> _Speakers;		// участники диалога, попадают по триггеру, удаляются также
	static TMap<int32, int32> _DialogNodeMap;					// dialogId - nodeId
																                    // свзязь между диалогом и нодой,
																                    // на которой закончился разговор в последний раз
protected:
public:
};
