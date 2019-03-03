#pragma once

#include "CoreMinimal.h"
#include "Common/AdventurePluginGameContext.h"
#include "DialogGraphNode.h"
#include "DialogGraph.h"
#include "DialogGraphNode_PlayCharacterAnimationOnceBase.h"
#include "AdventureCharacterManager.h"
#include "Presenter/DialogPresenterInterface.h"
#include "AnimatableObjectInterface.h"
#include "AdventurePluginRuntime.h"
#include "DialogGraphNode_PlayNPCAnimationOnce.generated.h"

/**
* Plays the specified animation on the NPC character once.
*/
UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UDialogGraphNode_PlayNPCAnimationOnce : public UDialogGraphNode_PlayCharacterAnimationOnceBase
{
	GENERATED_BODY()

public:

	UDialogGraphNode_PlayNPCAnimationOnce()
	{
#if WITH_EDITORONLY_DATA
		ContextMenuName = FText::FromString("Play NPC Animation Once");
		ContextMenuCategory = NSLOCTEXT("NodeCategories", "AnimationCategory", "Animations");
#endif
	}

#if WITH_EDITOR

	virtual inline FText GetNodeTitle() const
	{
		if (AnimationName.IsNone())
		{
			return NSLOCTEXT("DialogGraphNode_PlayNPCAnimationOnce", "Play NPC animation once no animation", "NPC animation once: No animation");
		}
		else
		{
			return FText::Format(NSLOCTEXT("DialogGraphNode_PlayNPCAnimationOnce", "Play NPC animation once", "NPC animation once: {0}"), FText::FromName(AnimationName));
		}
		return FText::FromName(AnimationName);
	}

	virtual inline FLinearColor GetBackgroundColor() const
	{
		return FLinearColor::Gray;
	}

#endif
	/**
	* Retrieves the NPC class from the UDialogGraph#NPCCharacter so the animation can be executed.
	* @return The NPC class that should be animated.
	*/
	virtual UClass* GetAnimatedObjectClass()
	{
		UDialogGraph* DialogGraph = GetDialogGraph();
		if (DialogGraph == nullptr || DialogGraph->NPCCharacter == nullptr)
		{
			LOG_Error(NSLOCTEXT("AdventurePlugin", "DialogGraphNode_PlayNPCAnimationOnce_GetAnimatedObjectClass_NPCCharacterNull", "DialogGraphNode_PlayNPCAnimationOnce::GetAnimatedObjectClass::NPC is NULL"));
			return nullptr;
		}
		return DialogGraph->NPCCharacter;
	}
};
