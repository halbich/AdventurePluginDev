#pragma once

#include "CoreMinimal.h"
#include "Common/AdventurePluginGameContext.h"
#include "DialogGraphNode.h"
#include "DialogGraphNode_PlayAnimationCharacterBase.h"
#include "DialogGraph.h"
#include "AdventureCharacterManager.h"
#include "Presenter/DialogPresenterInterface.h"
#include "AnimatableObjectInterface.h"
#include "NodeInterfaces/DialogNodePlayAnimationCallbackInterface.h"
#include "DialogGraphNode_PlayCharacterAnimationOnceBase.generated.h"

/**
* Base class for nodes that play an animation on a character once.
*/
UCLASS(Abstract, Blueprintable, HideCategories = (GenericGraphNode, GenericGraphNode_Editor))
class ADVENTUREPLUGINRUNTIME_API UDialogGraphNode_PlayCharacterAnimationOnceBase : public UDialogGraphNode_PlayAnimationCharacterBase, public IDialogNodePlayAnimationCallbackInterface
{
	GENERATED_BODY()

public:
	/**
	* Playes the specified animation on a character once.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @return False if we could start the animation, as the execution should only continue once this animation finishes.
	*/
	virtual bool Execute(UAdventurePluginGameContext* GameContext) override
	{
		TScriptInterface<IAnimatableObjectInterface> CharacterInstance = GetAnimatedObject(GameContext);
		if (CharacterInstance == nullptr)
		{
			LOG_Error(NSLOCTEXT("AdventurePlugin", "DialogGraphNode_PlayCharacterAnimationOnce_Execute_CharacterNull", "DialogGraphNode_PlayCharacterAnimationOnceBase::Execute::Character is NULL"));
			return true;
		}
		if (!UAdventurePluginGameContext::IsGameContextValid(GameContext, TEXT("DialogGraphNode_PlayCharacterAnimationOnceBase:Execute")))
		{
			return true;
		}
		UObject* DialogPresenter = GameContext->DialogPresenter.GetObject();
		IDialogPresenterInterface::Execute_PlayAnimationOnce(DialogPresenter, CharacterInstance, AnimationName, GameContext->DialogController);
		return false;
	}

	/**
	* Called when an animation finishes on the animated character.
	* Returns true if the execution should continue, which if the animation is the one this node started.
	* @param AnimationName The name of the animation that finished.
	* @param Success True if the animation completed successfully. Ignored, as we just want to know if the animation is over, successful or not.
	* @return True if the animation should continue, that is if the AnimationName is the same as the the name of the animation represented by this node.
	*/
	virtual bool PlayAnimationCallback_Implementation(FName AnimationName, bool Success) override {
		return AnimationName == this->AnimationName;
	}
};
