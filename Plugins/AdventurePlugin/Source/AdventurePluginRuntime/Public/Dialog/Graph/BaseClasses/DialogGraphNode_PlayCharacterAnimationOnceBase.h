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

UCLASS(Abstract, Blueprintable, HideCategories = (GenericGraphNode, GenericGraphNode_Editor))
class ADVENTUREPLUGINRUNTIME_API UDialogGraphNode_PlayCharacterAnimationOnceBase : public UDialogGraphNode_PlayAnimationCharacterBase, public IDialogNodePlayAnimationCallbackInterface
{
	GENERATED_BODY()

public:

	virtual bool Execute(UAdventurePluginGameContext* GameContext) override
	{
		TScriptInterface<IAnimatableObjectInterface> CharacterInstance = GetAnimatedObject(GameContext);
		if (CharacterInstance == nullptr)
		{
			LOG_Error(NSLOCTEXT("AP", "PlayCharacterAnimationOnceCharacterNull", "UDialogGraphNode_PlayCharacterAnimationOnceBase::Execute::Character is NULL"));
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

	/*The animation is finished if the animation for which callback is called is the same one.
	We just check by name, we do not know if it actually is the concrete animation that was started by this node. 
	Success is ignored, as the execution should always continue, if the animation failed we would be stuck here forever.*/
	virtual bool PlayAnimationCallback_Implementation(FName AnimationName, bool Success) override {
		return AnimationName == this->AnimationName;
	}
};
