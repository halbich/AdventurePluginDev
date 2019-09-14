#pragma once

#include "CoreMinimal.h"
#include "Common/AdventurePluginGameContext.h"
#include "DialogGraphNode.h"
#include "DialogGraph.h"
#include "BaseClasses/DialogGraphNode_PlayCharacterAnimationOnceBase.h"
#include "AdventureCharacterManager.h"
#include "Dialog/Presenter/DialogPresenterInterface.h"
#include "Animations/AnimatableObjectInterface.h"
#include "DialogGraphNode_SetPCAnimationState.generated.h"

/**
* Set the Player Character's animation state. It will repeat that until it is reset or the animation is changed.
*/
UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UDialogGraphNode_SetPCAnimationState : public UDialogGraphNode_PlayAnimationCharacterBase
{
	GENERATED_BODY()

public:

	UDialogGraphNode_SetPCAnimationState()
	{
#if WITH_EDITORONLY_DATA
		ContextMenuName = NSLOCTEXT("AdventurePlugin", "UDialogGraphNode_SetPCAnimationState_ContextName", "Set PC Animation State");
		ContextMenuCategory = NSLOCTEXT("NodeCategories", "AnimationCategory", "Animations");
#endif
	}

#if WITH_EDITOR

	virtual inline FText GetNodeTitle() const
	{
		if (AnimationName.IsNone())
		{
			return NSLOCTEXT("DialogGraphNode_SetPCAnimationState", "Set PC animation state no animation", "PC animation state: No animation");
		}
		else
		{
			return FText::Format(NSLOCTEXT("DialogGraphNode_SetPCAnimationState", "Set PC animation state", "PC animation state: {0}"), FText::FromName(AnimationName));
		}
		return FText::FromName(AnimationName);
	}

	virtual inline FLinearColor GetBackgroundColor() const
	{
		return FLinearColor::Gray;
	}

#endif

	/**
	* Retrieve the PC class from the dialog graph so it can be executed.
	* @return The PC class that should animated.
	*/
	virtual UClass* GetAnimatedObjectClass()
	{
		UDialogGraph* DialogGraph = GetDialogGraph();
		if (DialogGraph == nullptr || DialogGraph->PlayerCharacter == nullptr)
		{
			LOG_Error(NSLOCTEXT("AdventurePlugin", "DialogGraphNode_SetPCAnimationState_GetAnimatedObjectClass_PCNull", "DialogGraphNode_SetPCAnimationState::GetAnimatedObjectClass::PC is NULL"));
			return nullptr;
		}
		return DialogGraph->PlayerCharacter;
	}
};
