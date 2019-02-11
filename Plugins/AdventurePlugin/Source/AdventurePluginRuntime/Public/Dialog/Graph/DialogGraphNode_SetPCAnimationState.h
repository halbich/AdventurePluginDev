#pragma once

#include "CoreMinimal.h"
#include "Common/AdventurePluginGameContext.h"
#include "DialogGraphNode.h"
#include "DialogGraph.h"
#include "DialogGraphNode_PlayCharacterAnimationOnceBase.h"
#include "AdventureCharacterManager.h"
#include "Presenter/DialogPresenterInterface.h"
#include "AnimatableObjectInterface.h"
#include "DialogGraphNode_SetPCAnimationState.generated.h"

UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UDialogGraphNode_SetPCAnimationState : public UDialogGraphNode_PlayAnimationCharacterBase
{
	GENERATED_BODY()

public:

	UDialogGraphNode_SetPCAnimationState()
	{
#if WITH_EDITORONLY_DATA
		ContextMenuName = FText::FromString("Set PC Animation State");
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

	virtual UClass* GetAnimatedObjectClass()
	{
		UDialogGraph* DialogGraph = GetDialogGraph();
		if (DialogGraph == nullptr || DialogGraph->PlayerCharacter == nullptr)
		{
			// TODO: Log error.
			return nullptr;
		}
		return DialogGraph->PlayerCharacter;
	}
};
