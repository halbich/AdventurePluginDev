#pragma once

#include "CoreMinimal.h"
#include "DialogGraphNode.h"
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

	virtual inline bool CanCreateConnection(UGenericGraphNode* Other, FText& ErrorMessage)
	{
		/*if (Other->IsA(UDialogGraphNode_Player::StaticClass()))
		{
			ErrorMessage = FText::FromString("Don't do that!!!");
			return false;
		}*/
		return true;
	}

#endif


	virtual bool Execute(UDialogueController* controller, IDialoguePresenterInterface* widget) override
	{
		widget->Execute_ShowDialogueLine(widget->_getUObject(), this, controller);
		return false;
	};

	virtual bool ShowDialogueLineCallback_Implementation(UDialogueController* controller) override {
		return true;
	}
};
