#pragma once

#include "CoreMinimal.h"
#include "Common/AdventurePluginGameContext.h"
#include "DialogGraphNode.h"
#include "DialogGraph.h"
#include "DialogPresenterInterface.h"
#include "DialogGraphNode_ResetPCAnimationState.generated.h"

/**
* Reset the Player Character's animation state to default.
*/
UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UDialogGraphNode_ResetPCAnimationState : public UDialogGraphNode
{
	GENERATED_BODY()

public:

	UDialogGraphNode_ResetPCAnimationState()
	{
#if WITH_EDITORONLY_DATA
		ContextMenuName = NSLOCTEXT("AdventurePlugin", "UDialogGraphNode_ResetPCAnimationState_ContextName", "Reset PC Animation State");
		ContextMenuCategory = NSLOCTEXT("NodeCategories", "AnimationCategory", "Animations");
#endif
	}

#if WITH_EDITOR

	virtual inline FText GetNodeTitle() const
	{
		return NSLOCTEXT("DialogGraphNode_ResetPCAnimationState", "Reset PC animation state", "Reset PC animation state");
	}

	virtual inline FLinearColor GetBackgroundColor() const
	{
		return FLinearColor::Gray;
	}

#endif

	/**
	* Resets the animation state on the player character.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @return Always true, execution should not be halted.
	*/
	virtual bool Execute(UAdventurePluginGameContext* GameContext) override
	{
		if (!UAdventurePluginGameContext::IsGameContextValid(GameContext, TEXT("DialogGraphNode_ResetPCAnimationState::Execute")))
		{
			return true;
		}

		UDialogGraph* DialogGraph = GetDialogGraph();
		UAdventureCharacter* Character = IsValid(DialogGraph) ? DialogGraph->GetDialogPlayerCharacterInstance(GameContext) : nullptr;
		if (!IsValid(Character))
		{
			LOG_Warning(NSLOCTEXT(
				"AdventurePlugin", 
				"DialogGraphNode_ResetPCAnimationState_Execute_CharacterNull", 
				"DialogGraphNode_ResetPCAnimationState::Execute: Cannot retrieve valid player character."));
			return true;
		}

		UObject* DialogPresenter = GameContext->DialogPresenter.GetObject();
		IDialogPresenterInterface::Execute_ResetAnimationState(DialogPresenter, Character);
		return true;
	}
};
