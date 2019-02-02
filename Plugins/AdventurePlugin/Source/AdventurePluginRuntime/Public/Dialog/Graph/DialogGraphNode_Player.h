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
		auto* graph = GetDialogGraph();
		return graph && graph->IsValidLowLevel() ? graph->PlayerCharacter.GetDefaultObject() : nullptr;
	}

#endif

	virtual bool Execute(UAdventurePluginGameContext* context) override
	{
		auto widget = Cast<IDialogPresenterInterface>(context->DialogPresenter.GetObject());
		IDialogPresenterInterface::Execute_ShowDialogLine(widget->_getUObject(), GetDialogLine(context), context->DialogController);
		return false;
	}

	virtual bool IsDialogOption() const override
	{
		return true;
	}

	virtual UAdventureCharacter* GetSpeaker(UAdventurePluginGameContext* Context) const override
	{
		auto* graph = GetDialogGraph();
		return graph && graph->IsValidLowLevel() ? graph->GetDialogPlayerCharacterInstance(Context) : nullptr;
	}
};
