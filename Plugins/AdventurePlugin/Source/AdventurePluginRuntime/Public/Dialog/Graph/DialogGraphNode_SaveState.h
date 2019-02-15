#pragma once

#include "AdventurePluginRuntime.h"
#include "DialogGraphNode.h"
#include "Controller/DialogController.h"
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
		ContextMenuCategory = NSLOCTEXT("NodeCategories", "OtherCategory", "Other");
#endif
	}

#if WITH_EDITOR

	virtual inline FText GetNodeTitle() const
	{
		return FText::FromString("SAVE STATE");
	}

	virtual inline FLinearColor GetBackgroundColor() const
	{
		return FLinearColor::White;
	}

#endif

	virtual bool Execute(UAdventurePluginGameContext* GameContext) override
	{
		if (!UAdventurePluginGameContext::IsGameContextValid(GameContext, TEXT("DialogGraphNode_SaveState:Execute")))
		{
			return false;
		}

		UAdventurePluginSaveGame* SaveGame = GameContext->SaveGame;

		return SaveGame->Save();
	}
};
