#pragma once

#include "CoreMinimal.h"
#include "Common/AdventurePluginGameContext.h"
#include "DialogGraphNode.h"
#include "DialogGraph.h"
#include "AdventureCharacterManager.h"
#include "AnimatableObjectInterface.h"
#include "DialoguePresenterInterface.h"
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
		auto animatableObjectClass = GetAnimatedObjectClass();
		if (animatableObjectClass == nullptr)
		{
			// TODO: Log error.
			return nullptr;
		}
		return animatableObjectClass->ClassDefaultObject;
	}

#endif

	virtual UClass* GetAnimatedObjectClass()
	{
		// Must be overriden.
		return nullptr;
	}

	virtual TScriptInterface<IAnimatableObjectInterface> GetAnimatedObject(UAdventurePluginGameContext* context)
	{
		// Must be overriden.
		return nullptr;
	}

	virtual bool Execute(UAdventurePluginGameContext* context) override
	{
		TScriptInterface<IAnimatableObjectInterface> animatedObjectInstance = GetAnimatedObject(context);
		if (animatedObjectInstance == nullptr)
		{
			// TODO: Log Warning.
			return true;
		}
		auto widget = Cast<IDialoguePresenterInterface>(context->DialoguePresenter.GetObject());
		IDialoguePresenterInterface::Execute_SetAnimationState(widget->_getUObject(), animatedObjectInstance, AnimationName);
		return true;
	}
};
