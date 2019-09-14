#pragma once

#include "CoreMinimal.h"
#include "DialogGraphNode.h"
#include "BaseClasses/DialogGraphNode_TrueFalse.h"
#include "Common/AdventurePluginGameContext.h"
#include "SaveGame/AdventurePluginSaveGame.h"
#include "DialogGraphNode_Once.generated.h"

/**
* This node is true until the first time it is visited as part of the execution.
* By that we mean that it won't become false if visited by the UDialogGraphNode_Options node looking for options to present.
* To become false it needs this path to be actually selected.
* Once false it is false forever, so it persists when the dialog is restarted.
* <p>
* Implementation detail - the behavior we described is ensured by the GetNextNode() switching the variable to false if execute was called already.
* Since this node does not halt execution, GetNextNode() is called immediately after Execute() is called.
*/
UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UDialogGraphNode_Once : public UDialogGraphNode_TrueFalse
{
	GENERATED_BODY()

public:

	UDialogGraphNode_Once()
	{
#if WITH_EDITORONLY_DATA
		ContextMenuName = NSLOCTEXT("AdventurePlugin", "UDialogGraphNode_Once_ContextName", "Once");
		ContextMenuCategory = NSLOCTEXT("NodeCategories", "BranchingCategory", "Branching");
#endif
	}

#if WITH_EDITOR

	virtual inline FText GetNodeTitle() const
	{
		return NSLOCTEXT("DialogGraphNode_Once","Once","ONCE");
	}

#endif

	/**
	* Called as part of GetNextNode(), this returns true if it was not yet visited by Dialog Controller.
	* When called as part of Dialog Controller execution, i.e. after Execute() was called, this switch
	* the node to false forever, but still return true if its the first time. 
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @return True if this is the first time we are visiting the node.
	*/
	virtual bool IsTrue(UAdventurePluginGameContext* GameContext) override
	{
		if (!UAdventurePluginGameContext::IsGameContextValid(GameContext, TEXT("DialogGraphNode_Once:IsTrue")) || !NodeGuid.IsValid())
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

	/**
	* Returns the name in the save file where this node will save its truth value. Based on node GUID.
	* @return The name of the variable in save file.
	*/
	FName GetBoolVariableName()
	{
		return FName(*(TEXT("ONCE_") + NodeGuid.ToString()));
	}

	/**
	* Marks that execute was just called, so IsTrue() sets this node to false once executed.
	*/
	UPROPERTY(Transient)
	bool bWasJustExecuted;
};
