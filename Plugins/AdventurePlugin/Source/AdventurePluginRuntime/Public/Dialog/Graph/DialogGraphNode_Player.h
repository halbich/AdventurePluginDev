#pragma once

#include "CoreMinimal.h"
#include "Common/AdventurePluginGameContext.h"
#include "DialogGraphNode.h"
#include "Presenter/DialogPresenterInterface.h"
#include "NodeInterfaces/DialogNodeShowLineCallbackInterface.h"
#include "DialogGraphNode_DialogLineBase.h"
#include "DialogGraphNode_Player.generated.h"

UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UDialogGraphNode_Player : public UDialogGraphNode_DialogLineBase
{
	GENERATED_BODY()

public:

	UDialogGraphNode_Player()
	{
#if WITH_EDITORONLY_DATA
		ContextMenuName = FText::FromString("Player Line");
		ContextMenuCategory = NSLOCTEXT("NodeCategories", "LineCategory", "Lines");
#endif
		DialogText = NSLOCTEXT("DialogGraphNode_Player", "DefaultDialog", "<Insert something clever>");
	}

#if WITH_EDITOR

	virtual inline FLinearColor GetBackgroundColor() const
	{
		return FLinearColor::Green;
	}

	virtual UAdventureCharacter* GetSpeakerEditorOnly() const
	{
		UDialogGraph* DialogGraph = GetDialogGraph();
		return IsValid(DialogGraph) ? DialogGraph->PlayerCharacter.GetDefaultObject() : nullptr;
	}

#endif

	virtual bool Execute(UAdventurePluginGameContext* GameContext) override
	{
		if (!UAdventurePluginGameContext::IsGameContextValid(GameContext, TEXT("DialogGraphNode_Player:Execute")))
		{
			return true;
		}
		UObject* DialogPresenter = GameContext->DialogPresenter.GetObject();
		IDialogPresenterInterface::Execute_ShowDialogLine(DialogPresenter, GetDialogLine(GameContext), GameContext->DialogController);
		return false;
	}

	virtual bool IsDialogOption() const override
	{
		return true;
	}

	virtual UAdventureCharacter* GetSpeaker(UAdventurePluginGameContext* GameContext) const override
	{
		UDialogGraph* DialogGraph = GetDialogGraph();
		return IsValid(DialogGraph) ? DialogGraph->GetDialogPlayerCharacterInstance(GameContext) : nullptr;
	}
};
