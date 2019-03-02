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
#include "DialogGraphNode_PlayPCAnimationOnce.generated.h"

/**
* Plays just once the specified animation on the player character.
*/
UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UDialogGraphNode_PlayPCAnimationOnce : public UDialogGraphNode_PlayCharacterAnimationOnceBase
{
	GENERATED_BODY()

public:

	UDialogGraphNode_PlayPCAnimationOnce()
	{
#if WITH_EDITORONLY_DATA
		ContextMenuName = FText::FromString("Play PC Animation Once");
		ContextMenuCategory = NSLOCTEXT("NodeCategories", "AnimationCategory", "Animations");
#endif
	}

#if WITH_EDITOR

	virtual inline FText GetNodeTitle() const
	{
		if (AnimationName.IsNone())
		{
			return NSLOCTEXT("DialogGraphNode_PlayPCAnimationOnce", "Play PC animation once no animation", "PC animation once: No animation");
		}
		else
		{
			return FText::Format(NSLOCTEXT("DialogGraphNode_PlayPCAnimationOnce", "Play PC animation once", "PC animation once: {0}"), FText::FromName(AnimationName));
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
			LOG_Error(NSLOCTEXT("AdventurePlugin", "PlayPCAnimationOnceNodePlayerCharacterNull", "DialogGraphNode_PlayPCAnimationOnce::GetAnimatedObjectClass::Player is NULL"));
			return nullptr;
		}
		return DialogGraph->PlayerCharacter;
	}
};
