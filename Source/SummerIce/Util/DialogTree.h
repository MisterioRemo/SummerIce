#pragma once

#include "SummerIce/Util/CharacterEnum.h"
#include "SummerIce/StateAndTrigger/GameEventType.h"

class DialogSystem;

struct DialogNode
{
  ECharacter Speaker;
  FString Speech;
  TArray<int32> Answers;	// хранятся id следующих узлов-ответов на данную реплику
  EGameEventType Action = EGameEventType::NoAction;
  FString ActionData;
};

class SUMMERICE_API DialogTree
{
  friend DialogSystem;

public:
  using DialogMap = TMap<int32, DialogNode>;

private:
  void SetFileName(const int32 & LvlId);

protected:
  void LoadDialogFromJson(const int32 & LvlId);

public:
  DialogTree() {};
  ~DialogTree() {};

  DialogTree::DialogMap * GetDialogById(const int32 & DialogId);
  DialogNode* GetNodeById(DialogTree::DialogMap* CurrentDialog, const int32 & NodeId);

private:
  FString _FileName;
  TMap<int32, DialogMap> _Dialogs;

protected:

public:
};
