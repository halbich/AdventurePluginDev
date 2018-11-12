#pragma once

#include "AdventurePluginRuntime.h"
#include "DialogGraphNode.h"
#include "Controller/DialogueController.h"
#include "AdventurePluginSaveGame.h"
#include "DialogGraphNode_SaveState.generated.h"

UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UDialogGraphNode_SaveState : public UDialogGraphNode
{
	GENERATED_BODY()

public:

	UDialogGraphNode_SaveState()
	{
#if WITH_EDITORONLY_DATA
		ContextMenuName = FText::FromString("Save State");
#endif
	}

#if WITH_EDITOR

	virtual inline FText GetNodeTitle() const
	{
		return FText::FromString("Save State");;
	}

	virtual inline FLinearColor GetBackgroundColor() const
	{
		return FLinearColor::White;
	}

#endif

	virtual bool Execute(UAdventurePluginGameContext* context) override
	{
		if (!context || !context->IsValidLowLevel())
		{
			LOG_Error(NSLOCTEXT("AP", "ContextNull", "NodeSaveState::gameContext is NULL"));
			return false;
		}


		auto save = context->SaveGame;
		if (!save || !save->IsValidLowLevel())
		{
			LOG_Error(NSLOCTEXT("AP", "SaveNull", "NodeSaveState::gameContext->SaveGame is NULL"));
			return false;
		}

		return save->Save();
	}
};
