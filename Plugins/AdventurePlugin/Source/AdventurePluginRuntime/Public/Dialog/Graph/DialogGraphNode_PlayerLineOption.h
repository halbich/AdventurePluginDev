#pragma once

#include "CoreMinimal.h"
#include "DialogGraphNode.h"
#include "NodeInterfaces/DialogNodeShowLineCallbackInterface.h"
#include "DialogGraph.h"
#include "DialogGraphNode_PlayerLineOption.generated.h"

/**
* This is node's purpose is to be a dialog option that does nothing when executed.
* Common usecase - If the option name to be offered is different than the line spoken in dialog.
*/
UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UDialogGraphNode_PlayerLineOption : public UDialogGraphNode
{
	GENERATED_BODY()

public:

	UDialogGraphNode_PlayerLineOption()
	{
#if WITH_EDITORONLY_DATA
		ContextMenuName = FText::FromString("Player Line Option");
		ContextMenuCategory = NSLOCTEXT("NodeCategories", "LineCategory", "Lines");
#endif
		OptionText = NSLOCTEXT("DialogGraphNode_PlayerLineOption", "DefaultDialog", "<Insert something clever>");
	}
	/**
	* The option to present to the player.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerLineOptionNode")
	FText OptionText;

#if WITH_EDITOR

	virtual inline FText GetNodeTitle() const
	{
		return OptionText;
	}

	virtual void SetNodeTitle(const FText& NewTitle) override
	{
		OptionText = NewTitle;
	}

	virtual inline FLinearColor GetBackgroundColor() const
	{
		return FLinearColor::Green;
	}

	virtual bool CanRename() const override
	{
		return true;
	}

#endif

	virtual bool IsDialogOption() const override
	{
		return true;
	}
	/**
	* Build a dialog line option to display.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @return The dialog option line to present to the player.
	*/
	virtual FDialogLineData GetDialogLine(UAdventurePluginGameContext* GameContext) const override
	{
		FDialogLineData DialogOptionLine = FDialogLineData();
		DialogOptionLine.OptionText = OptionText;
		UDialogGraph* DialogGraph = GetDialogGraph();
		DialogOptionLine.SpeakerCharacter = IsValid(DialogGraph) ? DialogGraph->GetDialogPlayerCharacterInstance(GameContext) : nullptr;
		if (!IsValid(DialogOptionLine.SpeakerCharacter))
		{
			LOG_Warning(NSLOCTEXT("AdventurePlugin", "DialogGraphNode_PlayerLineOption_GetDialogLine", "DialogGraphNode_PlayerLineOption:GetDialogLine:Speaker is null or invalid."));
		}
		return DialogOptionLine;
	}
};
