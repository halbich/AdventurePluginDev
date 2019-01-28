#pragma once

#include "CoreMinimal.h"
#include "Common/AdventurePluginGameContext.h"
#include "DialogGraphNode.h"
#include "Presenter/DialoguePresenterInterface.h"
#include "NodeInterfaces/DialogueNodeShowLineCallbackInterface.h"
#include "DialogGraph.h"
#include "DialogGraphNode_DialogLineBase.generated.h"

UCLASS(Abstract, Blueprintable, HideCategories = (GenericGraphNode, GenericGraphNode_Editor))
class ADVENTUREPLUGINRUNTIME_API UDialogGraphNode_DialogLineBase : public UDialogGraphNode, public IDialogueNodeShowLineCallbackInterface
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DialogLineNode")
		FText DialogText;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DialogLineNode")
		USoundBase* DialogSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DialogLineNode")
		bool bSkippable;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DialogLineNode")
		float TextDuration;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DialogLineNode")
		FName AnimationName;

#if WITH_EDITOR

	virtual inline FText GetNodeTitle() const
	{
		return DialogText;
	}

	virtual void SetNodeTitle(const FText& NewTitle) override
	{
		DialogText = NewTitle;
	}

	virtual bool CanRename() const override
	{
		return true;
	}

	virtual UAdventureCharacter* GetSpeakerEditorOnly() const
	{
		//Override this method.
		check(false && "Get speaker function must be overriden");
		return nullptr;
	}

#endif

	virtual UAdventureCharacter* GetSpeaker(UAdventurePluginGameContext* Context) const
	{
		//Override this method.
		check(false && "Get speaker function must be overriden");
		return nullptr;
	}

	virtual bool Execute(UAdventurePluginGameContext* context) override
	{
		auto widget = Cast<IDialoguePresenterInterface>(context->DialoguePresenter.GetObject());
		IDialoguePresenterInterface::Execute_ShowDialogueLine(widget->_getUObject(), GetDialogLine(context), context->DialogueController);
		return false;
	};

	virtual bool ShowDialogueLineCallback_Implementation(UDialogueController* controller) override {
		return true;
	}

	virtual FDialogLineData GetDialogLine(UAdventurePluginGameContext* Context) const override
	{
		auto toReturn = FDialogLineData();
		toReturn.DialogSound = DialogSound;
		toReturn.LineText = DialogText;
		toReturn.OptionText = DialogText;
		toReturn.Skippable = bSkippable;
		toReturn.TextDuration = TextDuration;
		auto* speakerCharacter = GetSpeaker(Context);
		toReturn.SpeakerCharacter = speakerCharacter;
		auto defaultTextAnimation = speakerCharacter && speakerCharacter->IsValidLowLevel() ? speakerCharacter->DefaultTalkingAnimationState : FName();
		toReturn.AnimationName = AnimationName.IsNone() ? defaultTextAnimation : AnimationName;
		toReturn.UserData = nullptr;
		return toReturn;
	}
};
