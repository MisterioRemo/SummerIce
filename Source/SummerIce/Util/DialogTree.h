#pragma once

//#include "CoreMinimal.h"
#include "Util/CharacterEnum.h"
#include <vector>

class UDialogWidget;

struct DialogNode
{
	ECharacter Speaker;
	FString Speech;
	std::vector<uint32> answers;	// хранятся id следующих узлов-ответов на данную реплику
};

class SUMMERICE_API DialogTree
{
	friend UDialogWidget;

private:
	void SetFileName(const int32 & LvlId);

protected:
	void LoadDialogFromJson(const int32 & LvlId, const int32 & DialogId);

public:
	DialogTree() {};
	~DialogTree() {};

	const DialogNode* GetNodeById(const int32 & NodeId) const;
	const int32 GetLevelId() const { return _LvlId; }
	const int32 GetDialogId() const { return _DialogId; }
	
private:
	FString _FileName;
	int32 _LvlId;
	int32 _DialogId;
	TMap<uint32, DialogNode> _Dialog;

protected:

public:
};
