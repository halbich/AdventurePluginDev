#pragma once

#include "AdventurePluginRuntime.h"
#include "DialogGraphNode.h"
#include "Controller/DialogController.h"
#include "AdventurePluginSaveGame.h"
#include "DialogGraphNode_SaveState.generated.h"

/**
*This node forces the immediate save of the game.
*/
UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UDialogGraphNode_SaveState : public UDialogGraphNode
{
	GENERATED_BODY()

public:

	UDialogGraphNode_SaveState()
	{
#if WITH_EDITORONLY_DATA
		ContextMenuName = NSLOCTEXT("AdventurePlugin", "UDialogGraphNode_SaveState_ContextName", "Save State");
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

	/**
	* Saves the game.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @return Always true, this never halts the execution.
	*/
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
