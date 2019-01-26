#pragma once

#include "CoreMinimal.h"
#include "Common/AdventurePluginGameContext.h"
#include "DialogGraphNode.h"
#include "DialogGraph.h"
#include "AdventureCharacterManager.h"
#include "Presenter/DialoguePresenterInterface.h"
#include "NodeInterfaces/DialogNodePlayAnimationCallbackInterface.h"
#include "DialogGraphNode_PlayPCAnimation.generated.h"

UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UDialogGraphNode_PlayPCAnimation : public UDialogGraphNode, public IDialogNodePlayAnimationCallbackInterface
{
	GENERATED_BODY()

public:

	UDialogGraphNode_PlayPCAnimation()
	{
#if WITH_EDITORONLY_DATA
		ContextMenuName = FText::FromString("Play PC Animation");
		ContextMenuCategory = NSLOCTEXT("NodeCategories", "AnimationCategory", "Animations");
#endif
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PCAnimationNode")
		FName AnimationName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PCAnimationNode")
		USoundBase* DialogSound;

#if WITH_EDITOR

	virtual inline FText GetNodeTitle() const
	{
		if (AnimationName.IsNone())
		{
			return NSLOCTEXT("DialogGraphNode_PlayPCAnimation", "Play PC animation no animation", "PC animation: No animation");
		}
		else
		{
			return FText::Format(NSLOCTEXT("DialogGraphNode_PlayPCAnimation", "Play PC animation", "PC animation: {0}"), FText::FromName(AnimationName));
		}
		return FText::FromName(AnimationName);
	}

	virtual inline FLinearColor GetBackgroundColor() const
	{
		return FLinearColor::Gray;
	}

#endif


	virtual bool Execute(UAdventurePluginGameContext* context) override
	{
		if (context == nullptr || !context->IsValidLowLevel() ||
			context->AdventureCharacterManager == nullptr || !context->AdventureCharacterManager->IsValidLowLevel())
		{
			// TODO: Log warning/error.
			return true;
		}
		auto* dialogGraph = GetDialogGraph();
		if (dialogGraph == nullptr)
		{
			// TODO: Log error.
			return true;
		}
		auto* playerCharacterInstance = context->AdventureCharacterManager->GetCharacter(dialogGraph->PlayerCharacter);
		if (playerCharacterInstance == nullptr)
		{
			// TODO: Log Warning.
			return true;
		}
		auto widget = Cast<IDialoguePresenterInterface>(context->DialoguePresenter.GetObject());
		IDialoguePresenterInterface::Execute_PlayAnimationOnce(widget->_getUObject(), playerCharacterInstance, AnimationName,  context->DialogueController);
		return false;
	}

	virtual bool PlayAnimationCallback_Implementation(FName AnimationName, bool Success) override {
		return AnimationName == this->AnimationName;
	}
};
