#pragma once

#include "CoreMinimal.h"
#include "DialogGraphNode.h"
#include "BaseClasses/DialogGraphNode_TrueFalse.h"
#include "AdventurePluginGameContext.h"
#include"SaveGame/AdventurePluginSaveGame.h"
#include "DialogGraphNode_Once.generated.h"

#pragma optimize("", off)
/*This node is true until the first time it is visited by DialogController, i.e. Execute is called, followed by GetNextNode. */
UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UDialogGraphNode_Once : public UDialogGraphNode_TrueFalse
{
	GENERATED_BODY()

public:

	UDialogGraphNode_Once()
	{
#if WITH_EDITORONLY_DATA
		ContextMenuName = FText::FromString("Once");
		ContextMenuCategory = NSLOCTEXT("NodeCategories", "BranchingCategory", "Branching");
#endif
	}

#if WITH_EDITOR

	virtual inline FText GetNodeTitle() const
	{
		return NSLOCTEXT("DialogGraphNode_Once","Once","ONCE");
	}

#endif
	/* Called as part of GetNextNode, this return true if it was not yet visited by Dialog Controller. When called as part of Dialog Controller execution, i.e. after Execute was called, this will be false forever. */
	virtual bool IsTrue(UAdventurePluginGameContext* GameContext) override
	{
		if (!IsValid(GameContext) || !IsValid(GameContext->SaveGame) || !NodeGuid.IsValid())
		{
			return false;
		}
		bool bToReturn = GameContext->SaveGame->GetBoolOrDefault(GetBoolVariableName(), true);
		if (bWasJustExecuted && bToReturn)
		{
			GameContext->SaveGame->SetBool(GetBoolVariableName(), false);
		}
		bWasJustExecuted = false;
		return bToReturn;
	}

	virtual bool Execute(UAdventurePluginGameContext* GameContext) override
	{
		bWasJustExecuted = true;
		return true;
	};
protected:
	/* The name in the save file where this node will save its truth value. Based on node GUID.*/
	FName GetBoolVariableName()
	{
		return FName(*(TEXT("ONCE_") + NodeGuid.ToString()));
	}
	/*Marks that execute was just called, so IsTrue sets this node to false once executed.*/
	UPROPERTY(Transient)
		bool bWasJustExecuted;
};


#pragma optimize("", on)