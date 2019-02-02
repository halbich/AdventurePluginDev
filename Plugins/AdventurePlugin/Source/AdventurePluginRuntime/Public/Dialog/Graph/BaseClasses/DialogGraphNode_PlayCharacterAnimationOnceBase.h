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

	virtual bool Execute(UAdventurePluginGameContext* context) override
	{
		TScriptInterface<IAnimatableObjectInterface> characterInstance = GetAnimatedObject(context);
		if (characterInstance == nullptr)
		{
			// TODO: Log Warning.
			return true;
		}
		auto widget = Cast<IDialogPresenterInterface>(context->DialogPresenter.GetObject());
		IDialogPresenterInterface::Execute_PlayAnimationOnce(widget->_getUObject(), characterInstance, AnimationName, context->DialogController);
		return false;
	}

	virtual bool PlayAnimationCallback_Implementation(FName AnimationName, bool Success) override {
		return AnimationName == this->AnimationName;
	}
};
