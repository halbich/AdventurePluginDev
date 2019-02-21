#pragma once

#include "CoreMinimal.h"
#include "Common/AdventurePluginGameContext.h"
#include "DialogGraphNode.h"
#include "Presenter/DialogPresenterInterface.h"
#include "NodeInterfaces/DialogNodeShowLineCallbackInterface.h"
#include "DialogGraphNode_DialogLineBase.h"
#include "DialogGraphNode_Player.generated.h"
/*
* Represents a line that can be said by player. When executed that line is displayed.
* Is a dialog line option.
*/
UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UDialogGraphNode_Player : public UDialogGraphNode_DialogLineBase
{
	GENERATED_BODY()

public:

	UDialogGraphNode_Player()
	{
#if WITH_EDITORONLY_DATA
		ContextMenuName = FText::FromString("Player Line");
		ContextMenuCategory = NSLOCTEXT("NodeCategories", "LineCategory", "Lines");
#endif
		DialogText = NSLOCTEXT("DialogGraphNode_Player", "DefaultDialog", "<Insert something clever>");
	}

#if WITH_EDITOR

	virtual inline FLinearColor GetBackgroundColor() const
	{
		return FLinearColor::Green;
	}
	/*
	* Returns the editor time instance of the PC character class.
	* @return CDO of the player character class.
	*/
	virtual UAdventureCharacter* GetSpeakerEditorOnly() const
	{
		UDialogGraph* DialogGraph = GetDialogGraph();
		if (!IsValid(DialogGraph))
		{
			LOG_Error(NSLOCTEXT("AdventurePlugin", "DialogGraphNode_Player_GetSpeakerEditorOnly_GraphInvalid", "DialogGraphNode_Player:GetSpeaker:Dialog graph is null or invalid."));
			return nullptr;
		}
		return DialogGraph->PlayerCharacter.GetDefaultObject();
	}

#endif

	virtual bool IsDialogOption() const override
	{
		return true;
	}
	/**
	* Returns the instance of the PC character class.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @return The instance of the PC character class.
	*/
	virtual UAdventureCharacter* GetSpeaker(UAdventurePluginGameContext* GameContext) const override
	{
		UDialogGraph* DialogGraph = GetDialogGraph();
		if (!IsValid(DialogGraph))
		{
			LOG_Error(NSLOCTEXT("AdventurePlugin", "DialogGraphNode_Player_GetSpeakerGraphInvalid", "DialogGraphNode_Player:GetSpeaker:Dialog graph is null or invalid."));
			return nullptr;
		}
		return DialogGraph->GetDialogPlayerCharacterInstance(GameContext);
	}
};
