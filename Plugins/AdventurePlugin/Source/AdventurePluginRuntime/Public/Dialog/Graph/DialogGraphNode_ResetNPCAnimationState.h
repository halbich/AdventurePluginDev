#pragma once

#include "CoreMinimal.h"
#include "Common/AdventurePluginGameContext.h"
#include "DialogGraphNode.h"
#include "DialogGraph.h"
#include "DialogPresenterInterface.h"
#include "DialogGraphNode_ResetNPCAnimationState.generated.h"

/**
* Reset the NPC Character's animation state to default.
*/
UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UDialogGraphNode_ResetNPCAnimationState : public UDialogGraphNode
{
	GENERATED_BODY()

public:

	UDialogGraphNode_ResetNPCAnimationState()
	{
#if WITH_EDITORONLY_DATA
		ContextMenuName = NSLOCTEXT("AdventurePlugin", "UDialogGraphNode_ResetNPCAnimationState_ContextName", "Reset NPC Animation State");
		ContextMenuCategory = NSLOCTEXT("NodeCategories", "AnimationCategory", "Animations");
#endif
	}

#if WITH_EDITOR

	virtual inline FText GetNodeTitle() const
	{
		return NSLOCTEXT("DialogGraphNode_ResetNPCAnimationState", "Reset NPC animation state", "Reset NPC animation state");
	}

	virtual inline FLinearColor GetBackgroundColor() const
	{
		return FLinearColor::Gray;
	}

#endif

	/**
	* Resets the animation state on the NPC character.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @return Always true, execution should not be halted.
	*/
	virtual bool Execute(UAdventurePluginGameContext* GameContext) override
	{
		if (!UAdventurePluginGameContext::IsGameContextValid(GameContext, TEXT("DialogGraphNode_ResetNPCAnimationState::Execute")))
		{
			return true;
		}

		UDialogGraph* DialogGraph = GetDialogGraph();
		UAdventureCharacter* Character = IsValid(DialogGraph) ? DialogGraph->GetDialogNPCCharacterInstance(GameContext) : nullptr;
		if (!IsValid(Character))
		{
			LOG_Warning(NSLOCTEXT(
				"AdventurePlugin",
				"DialogGraphNode_ResetNPCAnimationState_Execute_CharacterNull",
				"DialogGraphNode_ResetNPCAnimationState::Execute: Cannot retrieve valid NPC character."));
			return true;
		}

		UObject* DialogPresenter = GameContext->DialogPresenter.GetObject();
		IDialogPresenterInterface::Execute_ResetAnimationState(DialogPresenter, Character);
		return true;
	}
};
