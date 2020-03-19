// Документация с примерами для nlohmann::json::parser_callback_t
// https://nlohmann.github.io/json/classnlohmann_1_1basic__json_ab4f78c5f9fd25172eeec84482e03f5b7.html#ab4f78c5f9fd25172eeec84482e03f5b7


#include "DialogTree.h"

#include "Misc/Paths.h"
#include "ThirdParty/json.hpp"
#include <fstream>
#include <string>


void DialogTree::SetFileName(const int32 & LvlId)
{
	_FileName = FPaths::Combine(FPaths::ProjectContentDir(),
								TEXT("Assets/Dialogs/Chapter_" + FString::FromInt(LvlId) + ".json"));
}

void DialogTree::LoadDialogFromJson(const int32 & LvlId, const int32 & DialogId)
{
	using json = nlohmann::json;

	SetFileName(LvlId);
	std::ifstream IFile(TCHAR_TO_UTF8(*_FileName));

	if (IFile.is_open()) {
		// Удалить старые элементы, не освобождая память
		_Dialog.Empty();

		// Парсить только ту часть json, которая относится к заданному DialogId
		// Ссылку на документацию с примерми см. в шапке файла
		std::string DialogKey = "dialog_id_" + std::to_string(DialogId);

		json::parser_callback_t cb = [&DialogId, &DialogKey](int depth, json::parse_event_t event, json& parsed)
		{
			if (event == json::parse_event_t::key) {
				if (parsed.dump().find("dialog_id_") != std::string::npos && parsed != json(DialogKey))
					return false;
				return true;
			}
			else return true;
		};
		
		std::function<void(json)> ParseNode;
		ParseNode = [this, &ParseNode](const json &J) -> void
		{
			DialogNode Node;
			uint32 Id = static_cast<uint32>(J["node_id"]);
			Node.Speaker = GetCharacterFromString(J["character"].get<std::string>().c_str());
			Node.Speech = J["speech"].get<std::string>().c_str();

			if (J.find("answers") != J.end()) {
				for (const auto &Answer : J["answers"]) {
					ParseNode(Answer);
					Node.answers.push_back(static_cast<uint32>(Answer["node_id"]));
				}
			}
			if (J.find("next") != J.end())
				Node.answers.push_back(static_cast<uint32>(J["next"]));
			_Dialog.Emplace(Id, Node);
		};


		json J = json::parse(IFile, cb);
		ParseNode(J[DialogKey]);

		// Освободить лишнюю память
		_Dialog.Compact();
		_Dialog.Shrink();

		// Если всё загрузилось успешно, запоминаем номер текущего диалога
		_LvlId = LvlId;
		_DialogId = DialogId;
	}
	else 
		UE_LOG(LogTemp, Warning, TEXT("DialogTree: can't open file %s"), *_FileName);

}

const DialogNode* DialogTree::GetNodeById(const int32 & NodeId) const
{
	return _Dialog.Find(NodeId);
}
