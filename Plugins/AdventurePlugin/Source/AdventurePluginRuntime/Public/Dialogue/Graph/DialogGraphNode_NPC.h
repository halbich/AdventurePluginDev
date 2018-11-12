#pragma once

#include "CoreMinimal.h"
#include "Common/AdventurePluginGameContext.h"
#include "DialogGraphNode.h"
#include "Presenter/DialoguePresenterInterface.h"
#include "NodeInterfaces/DialogueNodeShowLineCallbackInterface.h"
#include "DialogGraphNode_NPC.generated.h"

UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UDialogGraphNode_NPC : public UDialogGraphNode, public IDialogueNodeShowLineCallbackInterface
{
	GENERATED_BODY()

public:

	UDialogGraphNode_NPC()
	{
#if WITH_EDITORONLY_DATA
		ContextMenuName = FText::FromString("NPC Line");
#endif
		DialogText = NSLOCTEXT("DialogGraphNode_NPC", "DefaultDialog", "<Insert something clever>");
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DialogGraphNode_Editor")
	FText DialogText;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DialogGraphNode_Editor")
	USoundBase* DialogSound;

#if WITH_EDITOR

	virtual inline FText GetNodeTitle() const
	{
		return FText::Format(NSLOCTEXT("DialogGraphNode_NPC", "NPCSay", "NPC: \"{0}\""), DialogText);
	}

	virtual inline FLinearColor GetBackgroundColor() const
	{
		return FLinearColor::Red;
	}

#endif

	virtual bool Execute(UAdventurePluginGameContext* context) override
	{
		auto widget = Cast<IDialoguePresenterInterface>(context->DialoguePresenter.GetObject());
		IDialoguePresenterInterface::Execute_ShowDialogueLine(widget->_getUObject(), GetDialogLine(), context->DialogueController);
		return false;
	};

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
		toReturn.IsPlayerCharacterLine = false;
		return toReturn;
	}
};
