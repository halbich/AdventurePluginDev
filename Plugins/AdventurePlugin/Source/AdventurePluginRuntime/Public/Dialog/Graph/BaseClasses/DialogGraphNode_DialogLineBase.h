#pragma once

#include "CoreMinimal.h"
#include "Common/AdventurePluginGameContext.h"
#include "DialogGraphNode.h"
#include "Presenter/DialogPresenterInterface.h"
#include "NodeInterfaces/DialogNodeShowLineCallbackInterface.h"
#include "DialogGraph.h"
#include "DialogGraphNode_DialogLineBase.generated.h"
/**
* A base class for nodes showing a dialog line.
*/
UCLASS(Abstract, Blueprintable, HideCategories = (GenericGraphNode, GenericGraphNode_Editor))
class ADVENTUREPLUGINRUNTIME_API UDialogGraphNode_DialogLineBase : public UDialogGraphNode, public IDialogNodeShowLineCallbackInterface
{
	GENERATED_BODY()

public:
	/**
	* The text that should be shown to the player.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DialogLineNode")
	FText DialogText;
	/**
	* If not empty, this text will be used instead of DialogText when presenting this line as an option to the player.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DialogLineNode")
	FText OptionText;
	/** 
	* The sound to be played for this dialog line. The line should disappear automatically after the sound finishes.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DialogLineNode")
	USoundBase* DialogSound;
	/**
	* If true, the user can skip this dialog line.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DialogLineNode")
	bool bSkippable = true;
	/**
	* If set and dialog sound is null, the text should stay on this screen for this amount of seconds.
	* If sound is defined this is ignored.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DialogLineNode")
	float TextDuration;
	/**
	* The animation that should be played while this dialog line is being shown. 
	* If None, the default animation state will be shown. @see IAnimatableObjectInterface#GetDefaultTalkingAnimationState
	*/
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
	/** 
	* Returns an instance of the speaker class that is not dependent on a game context. Use only in editor. Must be overriden.
	* @return The speaker associated with this dialog line.
	*/
	virtual UAdventureCharacter* GetSpeakerEditorOnly() const
	{
		//Override this method.
		check(false && "Get speaker function must be overriden");
		return nullptr;
	}

#endif
	/**
	* Returns the speaker associated with this dialogue line. Must be overriden.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @return The speaker associated with this dialog line.
	*/
	virtual UAdventureCharacter* GetSpeaker(UAdventurePluginGameContext* GameContext) const
	{
		//Override this method.
		check(false && "Get speaker function must be overriden");
		return nullptr;
	}
	/**
	* Displays the dialog line represented by this node.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @return False if we could start the dialog line, since we should wait for the line completion.
	*/
	virtual bool Execute(UAdventurePluginGameContext* GameContext) override
	{
		if (!UAdventurePluginGameContext::IsGameContextValid(GameContext, TEXT("DialogGraphNode_DialogLineBase:Execute")))
		{
			return true;
		}
		UObject* DialogPresenterInstance = GameContext->DialogPresenter.GetObject();
		IDialogPresenterInterface::Execute_ShowDialogLine(DialogPresenterInstance, GetDialogLine(GameContext), GameContext->DialogController);
		return false;
	};
	/**
	* Called when the dialog line finishes.
	* @return Always true, to indicate that the dialog should continue.
	*/
	virtual bool ShowDialogLineCallback_Implementation(UDialogController* DialogController) override {
		return true;
	}
	/**
	* Creates a dialog line data representing this line.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @return The data representing this dialog line.
	*/
	virtual FDialogLineData GetDialogLine(UAdventurePluginGameContext* GameContext) const override
	{
		FDialogLineData DialogLine = FDialogLineData();
		DialogLine.DialogSound = DialogSound;
		DialogLine.LineText = DialogText;
		DialogLine.OptionText = OptionText.IsEmptyOrWhitespace() ? DialogText : OptionText;
		DialogLine.bSkippable = bSkippable;
		DialogLine.TextDuration = TextDuration;
		UAdventureCharacter* SpeakerCharacter = GetSpeaker(GameContext);
		DialogLine.SpeakerCharacter = SpeakerCharacter;
		// Used default animation if the animation was not explicitly specified.
		FName DefaultTextAnimation = IsValid(SpeakerCharacter) ? SpeakerCharacter->DefaultTalkingAnimationState : FName();
		DialogLine.AnimationName = AnimationName.IsNone() ? DefaultTextAnimation : AnimationName;
		DialogLine.UserData = nullptr;
		if (!IsValid(SpeakerCharacter))
		{
			LOG_Warning(NSLOCTEXT("AdventurePlugin", "DialogGraphNode_DialogLineBase_GetDialogLine_SpeakerInvalid", "DialogGraphNode_DialogLineBase:GetDialogLine::Speaker is null or invalid."));
		}
		return DialogLine;
	}
};
