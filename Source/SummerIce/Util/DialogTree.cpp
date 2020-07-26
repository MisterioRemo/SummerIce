// Документация с примерами для nlohmann::json::parser_callback_t
// https://nlohmann.github.io/json/classnlohmann_1_1basic__json_ab4f78c5f9fd25172eeec84482e03f5b7.html#ab4f78c5f9fd25172eeec84482e03f5b7


#include "DialogTree.h"

#include "Misc/Paths.h"
#include "json.hpp"
#include <fstream>
#include <string>


void DialogTree::SetFileName(const int32 & LvlId)
{
	_FileName = FPaths::Combine(FPaths::ProjectContentDir(),
								TEXT("Dialogs/Chapter_" + FString::FromInt(LvlId) + ".json"));
}

void DialogTree::LoadDialogFromJson(const int32 & LvlId)
{
	using json = nlohmann::json;

	SetFileName(LvlId);
	std::ifstream IFile(TCHAR_TO_UTF8(*_FileName));

	if (IFile.is_open()) {
		// Удалить старые элементы, не освобождая память
		_Dialogs.Empty();
		DialogMap DialogNodes;
				
		std::function<void(json)> ParseNode;
		ParseNode = [this, &ParseNode, &DialogNodes](const json &J) -> void
		{
			DialogNode Node;
			int32 Id = static_cast<int32>(J["node_id"]);
			Node.Speaker = GetCharacterFromString(J["character"].get<std::string>().c_str());
			Node.Speech = UTF8_TO_TCHAR(J["speech"].get<std::string>().c_str());

			if (J.find("answers") != J.end()) {
				for (const auto &Answer : J["answers"]) {
					ParseNode(Answer);
					Node.Answers.Emplace(static_cast<int32>(Answer["node_id"]));
				}
			}
			if (J.find("next") != J.end())
				Node.Answers.Emplace(static_cast<int32>(J["next"]));
			DialogNodes.Emplace(Id, Node);
		};

		json J = json::parse(IFile);
		for (const auto &Dialog : J["dialogs"]) {
			DialogNodes.Empty();
			int32 Id = static_cast<int32>(Dialog["dialog_id"]);
      for(const auto &Node : Dialog["nodes"]) ParseNode(Node);
			_Dialogs.Emplace(Id, MoveTemp(DialogNodes));
		}

		// Освободить лишнюю память
		_Dialogs.Compact();
		_Dialogs.Shrink();
	}
	else 
		UE_LOG(LogTemp, Warning, TEXT("DialogTree: can't open file %s"), *_FileName);

}

DialogTree::DialogMap* DialogTree::GetDialogById(const int32 & DialogId)
{
	return _Dialogs.Find(DialogId);
}

DialogNode* DialogTree::GetNodeById(DialogTree::DialogMap *CurrentDialog, const int32 & NodeId)
{
	return CurrentDialog->Find(NodeId);
}
