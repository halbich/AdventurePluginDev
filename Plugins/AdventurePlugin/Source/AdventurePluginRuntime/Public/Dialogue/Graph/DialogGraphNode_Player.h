#pragma once

#include "CoreMinimal.h"
#include "Common/AdventurePluginGameContext.h"
#include "DialogGraphNode.h"
#include "Presenter/DialoguePresenterInterface.h"
#include "NodeInterfaces/DialogueNodeShowLineCallbackInterface.h"
#include "DialogGraphNode_Player.generated.h"

UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UDialogGraphNode_Player : public UDialogGraphNode, public IDialogueNodeShowLineCallbackInterface
{
	GENERATED_BODY()

public:

	UDialogGraphNode_Player()
	{
#if WITH_EDITORONLY_DATA
		ContextMenuName = FText::FromString("Player Line");
#endif
		DialogText = NSLOCTEXT("DialogGraphNode_Player", "DefaultDialog", "<Insert something clever>");
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DialogGraphNode_Editor")
	FText DialogText;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DialogGraphNode_Editor")
	USoundBase* DialogSound;

#if WITH_EDITOR

	virtual inline FText GetNodeTitle() const
	{
		return FText::Format(NSLOCTEXT("DialogGraphNode_Player", "PlayerSay", "Player: \"{0}\""), DialogText);
	}

	virtual inline FLinearColor GetBackgroundColor() const
	{
		return FLinearColor::Green;
	}

#endif


	virtual bool Execute(UAdventurePluginGameContext* context) override
	{
		auto widget = Cast<IDialoguePresenterInterface>(context->DialoguePresenter.GetObject());
		IDialoguePresenterInterface::Execute_ShowDialogueLine(widget->_getUObject(), GetDialogLine(), context->DialogueController);
		return false;
	}

	virtual bool IsDialogOption() const override
	{
		return true;
	}

	virtual bool ShowDialogueLineCallback_Implementation(UDialogueController* controller) override {
		return true;
	}

	virtual FDialogLineData GetDialogLine() const override
	{
		auto toReturn = FDialogLineData();
		toReturn.DialogSound = DialogSound;
		toReturn.LineText = DialogText;
		toReturn.OptionText = DialogText;
		//TODO: Use correct variables here
		toReturn.Skippable = true;
		toReturn.TextDuration = 10;
		toReturn.UserData = nullptr;
		toReturn.IsPlayerCharacterLine = true;
		return toReturn;
	}
};
