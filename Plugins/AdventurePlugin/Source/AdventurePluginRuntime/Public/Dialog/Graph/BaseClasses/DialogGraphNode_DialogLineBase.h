#pragma once

#include "CoreMinimal.h"
#include "Common/AdventurePluginGameContext.h"
#include "DialogGraphNode.h"
#include "Presenter/DialogPresenterInterface.h"
#include "NodeInterfaces/DialogNodeShowLineCallbackInterface.h"
#include "DialogGraph.h"
#include "DialogGraphNode_DialogLineBase.generated.h"

UCLASS(Abstract, Blueprintable, HideCategories = (GenericGraphNode, GenericGraphNode_Editor))
class ADVENTUREPLUGINRUNTIME_API UDialogGraphNode_DialogLineBase : public UDialogGraphNode, public IDialogNodeShowLineCallbackInterface
{
	GENERATED_BODY()

public:
	/*The text that should be shown to the player.*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DialogLineNode")
		FText DialogText;
	/*The sound to be played for this dialog line. The line should disappear automatically after the sound finishes. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DialogLineNode")
		USoundBase* DialogSound;
	/*If true, the user can skip this dialog line.*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DialogLineNode")
		bool bSkippable = true;
	/* If set and dialog sound is nullptr, the text should stay on this screen for this amount of time.*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DialogLineNode")
		float TextDuration;
	/*The animation that should be played while this dialog line is being shown.*/
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
	/*Returns the CDO of the speaker that does not depend on a game context. Use only in editor. Must be overriden.*/
	virtual UAdventureCharacter* GetSpeakerEditorOnly() const
	{
		//Override this method.
		check(false && "Get speaker function must be overriden");
		return nullptr;
	}

#endif
	/* Returns the speaker associated with this dialogue line. Must be overriden.*/
	virtual UAdventureCharacter* GetSpeaker(UAdventurePluginGameContext* GameContext) const
	{
		//Override this method.
		check(false && "Get speaker function must be overriden");
		return nullptr;
	}
	/*Displays the dialog line.*/
	virtual bool Execute(UAdventurePluginGameContext* GameContext) override
	{
		auto widget = Cast<IDialogPresenterInterface>(GameContext->DialogPresenter.GetObject());
		IDialogPresenterInterface::Execute_ShowDialogLine(widget->_getUObject(), GetDialogLine(GameContext), GameContext->DialogController);
		return false;
	};

	virtual bool ShowDialogLineCallback_Implementation(UDialogController* DialogController) override {
		return true;
	}
	/*Creates a dialog line data representing this line.*/
	virtual FDialogLineData GetDialogLine(UAdventurePluginGameContext* GameContext) const override
	{
		FDialogLineData DialogLine = FDialogLineData();
		DialogLine.DialogSound = DialogSound;
		DialogLine.LineText = DialogText;
		DialogLine.OptionText = DialogText;
		DialogLine.bSkippable = bSkippable;
		DialogLine.TextDuration = TextDuration;
		UAdventureCharacter* SpeakerCharacter = GetSpeaker(GameContext);
		DialogLine.SpeakerCharacter = SpeakerCharacter;
		// Used default animation if the animation was not explicitly specified.
		FName DefaultTextAnimation = SpeakerCharacter && SpeakerCharacter->IsValidLowLevel() ? SpeakerCharacter->DefaultTalkingAnimationState : FName();
		DialogLine.AnimationName = AnimationName.IsNone() ? DefaultTextAnimation : AnimationName;
		DialogLine.UserData = nullptr;
		return DialogLine;
	}
};
