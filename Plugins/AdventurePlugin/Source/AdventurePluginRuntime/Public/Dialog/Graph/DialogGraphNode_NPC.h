#pragma once

#include "CoreMinimal.h"
#include "Common/AdventurePluginGameContext.h"
#include "DialogGraphNode.h"
#include "Presenter/DialogPresenterInterface.h"
#include "NodeInterfaces/DialogNodeShowLineCallbackInterface.h"
#include "DialogGraph.h"
#include "DialogGraphNode_DialogLineBase.h"
#include "DialogGraphNode_NPC.generated.h"

/**
* This node represents a dialog line said by an NPC.
*/
UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UDialogGraphNode_NPC : public UDialogGraphNode_DialogLineBase
{
	GENERATED_BODY()

public:

	UDialogGraphNode_NPC()
	{
#if WITH_EDITORONLY_DATA
		ContextMenuName = FText::FromString("NPC Line");
		ContextMenuCategory = NSLOCTEXT("NodeCategories", "LineCategory", "Lines");
#endif
		DialogText = NSLOCTEXT("DialogGraphNode_NPC", "DefaultDialog", "<Insert something clever>");
	}

#if WITH_EDITOR

	virtual inline FLinearColor GetBackgroundColor() const
	{
		return FLinearColor::Red;
	}

	/**
	* Get instance of the character that is speaking that is accessible without a game instance, i.e. CDO of the NPC character class.
	* Use only in editor.
	* @return The NPC character instance.
	*/
	virtual UAdventureCharacter* GetSpeakerEditorOnly() const
	{
		UDialogGraph* DialogGraph = GetDialogGraph();
		if (!IsValid(DialogGraph))
		{
			LOG_Error(NSLOCTEXT("AdventurePlugin", "DialogGraphNode_NPCGetSpeakerEditorOnly_GraphInvalid", "DialogGraphNode_NPC:GetSpeakerEditorOnly:Quest is null or invalid."));
			return nullptr;
		}
		return DialogGraph->NPCCharacter.GetDefaultObject();
	}

#endif

	/**
	* Get instance of the character that is speaking, i.e. the NPC class provided by the character manager in the GameContext.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @return The NPC character instance.
	*/
	virtual UAdventureCharacter* GetSpeaker(UAdventurePluginGameContext* GameContext) const override
	{
		UDialogGraph* DialogGraph = GetDialogGraph();
		if (!IsValid(DialogGraph))
		{
			LOG_Error(NSLOCTEXT("AdventurePlugin", "DialogGraphNode_NPCGetSpeaker_GraphInvalid", "DialogGraphNode_NPC:GetSpeaker:Quest is null or invalid."));
			return nullptr;
		}
		return DialogGraph->GetDialogNPCCharacterInstance(GameContext);
	}
};
