#pragma once

#include "CoreMinimal.h"
#include "Common/AdventurePluginGameContext.h"
#include "DialogGraphNode.h"
#include "Presenter/DialoguePresenterInterface.h"
#include "NodeInterfaces/DialogueNodeShowLineCallbackInterface.h"
#include "DialogGraph.h"
#include "DialogGraphNode_DialogLineBase.h"
#include "DialogGraphNode_NPC.generated.h"

UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UDialogGraphNode_NPC : public UDialogGraphNode_DialogLineBase
{
	GENERATED_BODY()

public:

	UDialogGraphNode_NPC()
	{
#if WITH_EDITORONLY_DATA
		ContextMenuName = FText::FromString("NPC Line");
		ContextMenuCategory = NSLOCTEXT("NodeCategories", "LineCategory", "Lines");
#endif
		DialogText = NSLOCTEXT("DialogGraphNode_NPC", "DefaultDialog", "<Insert something clever>");
	}

#if WITH_EDITOR

	virtual inline FLinearColor GetBackgroundColor() const
	{
		return FLinearColor::Red;
	}

#endif

	virtual UAdventureCharacter* GetSpeaker(UAdventurePluginGameContext* Context) const override
	{
		auto* graph = GetDialogGraph();
		return graph && graph->IsValidLowLevel() ? graph->GetDialogNPCCharacterInstance(Context) : nullptr;
	}
};
