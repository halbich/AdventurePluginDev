#pragma once

#include "CoreMinimal.h"
#include "Common/AdventurePluginGameContext.h"
#include "Dialog/Graph/DialogGraphNode.h"
#include "Dialog/Graph/DialogGraph.h"
#include "AdventureCharacterManager.h"
#include "Animations/AnimatableObjectInterface.h"
#include "Dialog/Presenter/DialogPresenterInterface.h"
#include "DialogGraphNode_PlayAnimationBase.generated.h"

/**
* Base class for dialog nodes that play animations.
*/
UCLASS(Abstract, Blueprintable, HideCategories = (GenericGraphNode, GenericGraphNode_Editor))
class ADVENTUREPLUGINRUNTIME_API UDialogGraphNode_PlayAnimationBase : public UDialogGraphNode
{
	GENERATED_BODY()

public:

	/**
	* The name of the animation this class will play.
	*/
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

	/**
	* Use only in editor. Retrieves an instance of the animated object that does not depend on a game context.
	* @return The animated object.
	*/
	virtual TScriptInterface<IAnimatableObjectInterface> GetEditorTimeAnimatableObject()
	{
		UClass* AnimatableObjectClass = GetAnimatedObjectClass();
		if (AnimatableObjectClass == nullptr)
		{
			LOG_Error(NSLOCTEXT("AdventurePlugin","DialogGraphNode_PlayAnimationBase_GetEditorTimeAnimatableObject_ClassNull", "DialogGraphNode_PlayAnimationBase:GetEditorTimeAnimatableObject: The animatable object class is null."));
			return nullptr;
		}
		return AnimatableObjectClass->ClassDefaultObject;
	}

#endif

	/**
	* Returns the class representing the object that this node should animate. Must be overriden by child classes.
	* @return The class this node is animating.
	*/
	virtual UClass* GetAnimatedObjectClass()
	{
		// Must be overriden.
		check(false && "Get Animated Object Class method must be overriden");
		return nullptr;
	}

	/**
	* Returns the instance of the class that should be animated. Must be overriden by child classes.
	* @return The animated object.
	*/
	virtual TScriptInterface<IAnimatableObjectInterface> GetAnimatedObject(UAdventurePluginGameContext* GameContext)
	{
		// Must be overriden.
		check(false && "Get Animated Object method must be overriden");
		return nullptr;
	}

	/**
	* Sets the animation state on the animatable object represented by this node.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @return Always true, execution should not be halted.
	*/
	virtual bool Execute(UAdventurePluginGameContext* GameContext) override
	{
		TScriptInterface<IAnimatableObjectInterface> AnimatedObjectInstance = GetAnimatedObject(GameContext);
		if (!IsValid(AnimatedObjectInstance.GetObject()))
		{
			LOG_Error(NSLOCTEXT("AdventurePlugin", "DialogGraphNode_PlayAnimationBase_Execute_AnimatedObjectInvalid", "DialogGraphNode_PlayAnimationBase:Execute: Animated object is null or invalid."));
			return true;
		}
		if (!UAdventurePluginGameContext::IsGameContextValid(GameContext, TEXT("DialogGraphNode_PlayAnimationBase:Execute")))
		{
			return true;
		}
		UObject* DialogPresenter = GameContext->DialogPresenter.GetObject();
		IDialogPresenterInterface::Execute_SetAnimationState(DialogPresenter, AnimatedObjectInstance, AnimationName);
		return true;
	}
};
