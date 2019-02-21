#pragma once

#include "CoreMinimal.h"
#include "Common/AdventurePluginGameContext.h"
#include "DialogGraphNode.h"
#include "DialogGraph.h"
#include "DialogGraphNode_PlayCharacterAnimationOnceBase.h"
#include "AdventureCharacterManager.h"
#include "Presenter/DialogPresenterInterface.h"
#include "AnimatableObjectInterface.h"
#include "DialogGraphNode_SetNPCAnimationState.generated.h"

/**
* Set the Player Character's animation state. It will repeat that until it is reset or the animation is changed.
*/
UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UDialogGraphNode_SetNPCAnimationState : public UDialogGraphNode_PlayAnimationCharacterBase
{
	GENERATED_BODY()

public:

	UDialogGraphNode_SetNPCAnimationState()
	{
#if WITH_EDITORONLY_DATA
		ContextMenuName = FText::FromString("Set NPC Animation State");
		ContextMenuCategory = NSLOCTEXT("NodeCategories", "AnimationCategory", "Animations");
#endif
	}

#if WITH_EDITOR

	virtual inline FText GetNodeTitle() const
	{
		if (AnimationName.IsNone())
		{
			return NSLOCTEXT("DialogGraphNode_SetNPCAnimationState", "Set NPC animation state no animation", "NPC animation state: No animation");
		}
		else
		{
			return FText::Format(NSLOCTEXT("DialogGraphNode_SetNPCAnimationState", "Set NPC animation state", "NPC animation state: {0}"), FText::FromName(AnimationName));
		}
		return FText::FromName(AnimationName);
	}

	virtual inline FLinearColor GetBackgroundColor() const
	{
		return FLinearColor::Gray;
	}

#endif
	/**
	* Retrieve the NPC class from the dialog graph so it can be executed.
	* @return The NPC class that should animated.
	*/
	virtual UClass* GetAnimatedObjectClass()
	{
		UDialogGraph* DialogGraph = GetDialogGraph();
		if (DialogGraph == nullptr || DialogGraph->NPCCharacter == nullptr)
		{
			LOG_Error(NSLOCTEXT("AdventurePlugin", "DialogGraphNode_SetNPCAnimationState_GetAnimatedObjectClass_NPCNull", "DialogGraphNode_SetNPCAnimationState::GetAnimatedObjectClass::NPC is NULL"));
			return nullptr;
		}
		return DialogGraph->NPCCharacter;
	}
};
