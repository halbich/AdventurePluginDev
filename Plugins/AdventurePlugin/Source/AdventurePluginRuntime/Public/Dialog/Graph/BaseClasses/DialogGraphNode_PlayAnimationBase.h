#pragma once

#include "CoreMinimal.h"
#include "Common/AdventurePluginGameContext.h"
#include "DialogGraphNode.h"
#include "DialogGraph.h"
#include "AdventureCharacterManager.h"
#include "AnimatableObjectInterface.h"
#include "DialogPresenterInterface.h"
#include "DialogGraphNode_PlayAnimationBase.generated.h"

UCLASS(Abstract, Blueprintable, HideCategories = (GenericGraphNode, GenericGraphNode_Editor))
class ADVENTUREPLUGINRUNTIME_API UDialogGraphNode_PlayAnimationBase : public UDialogGraphNode
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AnimationNode")
		FName AnimationName;

#if WITH_EDITOR

	virtual inline FText GetNodeTitle() const
	{
		if (AnimationName.IsNone())
		{
			return NSLOCTEXT("DialogGraphNode_PlayAnimationBase", "Play animation no animation", "Animation: No animation");
		}
		else
		{
			return FText::Format(NSLOCTEXT("DialogGraphNode_PlayAnimationBase", "Play animation", "Animation: {0}"), FText::FromName(AnimationName));
		}
		return FText::FromName(AnimationName);
	}

	virtual TScriptInterface<IAnimatableObjectInterface> GetEditorTimeAnimatableObject()
	{
		UClass* AnimatableObjectClass = GetAnimatedObjectClass();
		if (AnimatableObjectClass == nullptr)
		{
			// TODO: Log error.
			return nullptr;
		}
		return AnimatableObjectClass->ClassDefaultObject;
	}

#endif
	/*Returns the class representing the object that should be animated.*/
	virtual UClass* GetAnimatedObjectClass()
	{
		// Must be overriden.
		check(false && "Get Animated Object Class method must be overriden");
		return nullptr;
	}
	/* Returns the instance of the class that should be animated.*/
	virtual TScriptInterface<IAnimatableObjectInterface> GetAnimatedObject(UAdventurePluginGameContext* GameContext)
	{
		// Must be overriden.
		check(false && "Get Animated Object method must be overriden");
		return nullptr;
	}
	/* Plays the animation on the object.*/
	virtual bool Execute(UAdventurePluginGameContext* GameContext) override
	{
		TScriptInterface<IAnimatableObjectInterface> AnimatedObjectInstance = GetAnimatedObject(GameContext);
		if (AnimatedObjectInstance == nullptr)
		{
			// TODO: Log Warning.
			return true;
		}
		if (!IsValid(GameContext) || !IsValid(GameContext->DialogPresenter.GetObject()))
		{
			// TODO: Log Warning.
			return true;
		}
		UObject* DialogPresenter = GameContext->DialogPresenter.GetObject();
		IDialogPresenterInterface::Execute_SetAnimationState(DialogPresenter, AnimatedObjectInstance, AnimationName);
		return true;
	}
};
