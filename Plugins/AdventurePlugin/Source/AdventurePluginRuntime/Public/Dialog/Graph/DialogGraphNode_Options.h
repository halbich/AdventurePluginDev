#pragma once

#include "CoreMinimal.h"
#include "Common/AdventurePluginGameContext.h"
#include "DialogGraph.h"
#include "DialogGraphNode.h"
#include "DialogGraphNode_Player.h"
#include "Presenter/DialogPresenterInterface.h"
#include "NodeInterfaces/DialogNodeShowOptionsCallbackInterface.h"
#include "DialogGraphNode_Options.generated.h"

/**
* This node should present the list of possible options to the user, allowing him to select how the dialog should continue.
* When the node is visited, it visits all of its children. If the child node can be a dialog option, it is presented to the user.
* If it is not a dialog option, GetNextNode() is called on that node and we check if that one is a dialog option. 
* We repeat that until we either get an option or a null node.
* All of the valid options are then presented to the player and the execution halts until he chooses.
* We then continue with the selected response.
* This node can also have a fallback node, which is used if no other branch of dialog tree is valid, as a fallback.
* We determine if a node is a dialog option by calling UDialogGraphNode#IsDialogOption.
*/
UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UDialogGraphNode_Options : public UDialogGraphNode, public IDialogNodeShowOptionsCallbackInterface
{
	GENERATED_BODY()

public:

	UDialogGraphNode_Options()
	{
#if WITH_EDITORONLY_DATA
		ContextMenuName = FText::FromString("Options");
		ContextMenuCategory = NSLOCTEXT("NodeCategories", "OtherCategory", "Other");
#endif
		ChoiceCount = 1;
	}

	/**
	* How many output nodes can this node have, i.e. how many options can be presented to the player.
	*/
	UPROPERTY(VisibleAnywhere, Category = "OptionsNode")
	uint32 ChoiceCount;

	/**
	* The node with which to continue if no output nodes are found.
	*/
	UPROPERTY(BlueprintReadOnly)
	UDialogGraphNode* ChildFallback;

	/**
	* The options representing the dialog options to be presented to the player.
	*/
	UPROPERTY(BlueprintReadOnly)
	TMap<int32, UDialogGraphNode*> ChildOptions;

	virtual void ResetSpecialChildren() override
	{
		ChildFallback = nullptr;
		ChildOptions.Reset();
	}

#if WITH_EDITOR

	virtual inline FText GetNodeTitle() const
	{
		return NSLOCTEXT("DialogGraphNode_Options", "OptionsName", "OPTIONS");
	}

	virtual inline FLinearColor GetBackgroundColor() const
	{
		return FLinearColor::Yellow;
	}

	virtual inline bool CanCreateConnection(UGenericGraphNode* Other, FText& ErrorMessage)
	{
		return true;
	}

#endif

	/**
	* Goes through the children to get the list of options to present and presents them.
	* See class description to get better idea how that works.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @return False if some options were found, as we need to halt the execution until the user selects an option. True is returned if no options can be displayed.
	*/
	virtual bool Execute(UAdventurePluginGameContext* GameContext) override
	{
		SelectedOptionIndex = -1;
		OptionMapping.Reset();
		// Go through all child nodes, if visiting something other than a Dialog Option go to their children, find all Dialog Option nodes and show them to the player.
		TArray<FDialogLineData> OptionsToPresent = TArray<FDialogLineData>();
		OptionsToPresent.Reserve(ChoiceCount);
		check(ChildOptions.Num() == ChoiceCount);
		for (int32 i = 0; i < (int32)ChoiceCount; ++i)
		{
			UDialogGraphNode* ChildNode = ChildOptions[i];
			while (IsValid(ChildNode))
			{
				if (ChildNode->IsDialogOption())
				{
					// Found a player line to present
					OptionMapping.Add(OptionsToPresent.Num(), i);
					OptionsToPresent.Add(ChildNode->GetDialogLine(GameContext));
					break;
				}
				// Player line not found, go to child node.
				ChildNode = ChildNode->GetNextNode(GameContext);
			}
		}
		if (OptionsToPresent.Num() != 0)
		{
			// Found some options, present them to the player.
			UObject* DialogPresenter = GameContext->DialogPresenter.GetObject();
			IDialogPresenterInterface::Execute_ShowDialogSelection(DialogPresenter, OptionsToPresent, GameContext->DialogController);
		}
		else
		{
			// This is fallback - execution of this node will end and the Controller will call GetNextNode, which will, thanks to SelectedOptionIndex being -1, return ChildFallback.
			// If ChildFallback is nullptr, execution of graph will end.
			return true;
		}
		return false;
	}

	/**
	* Called once the user selects an option. 
	* @param SelectedNodeIndex Which node did the user select.
	* @param DialogController The dialog controller that is executing this graph.
	* @return Always true, we should continue with the execution.
	*/
	virtual bool DialogOptionSelected_Implementation(int32 SelectedNodeIndex, UDialogController* DialogController) override
	{
		this->SelectedOptionIndex = OptionMapping[SelectedNodeIndex];
		return true;
	}

	/**
	* Retrieves the next node to be executed. As Execute() was called before this, we should now know which node to continue with.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @return The node to continue with.
	*/
	virtual UDialogGraphNode* GetNextNode(UAdventurePluginGameContext* GameContext) override
	{
		if (SelectedOptionIndex < 0)
		{
			return ChildFallback;
		}
		check(SelectedOptionIndex < (int32)ChoiceCount);
		if (SelectedOptionIndex >= (int32)ChoiceCount)
		{
			LOG_Warning(NSLOCTEXT("AdventurePlugin", "DialogNodeOptions_GetNextNode_UsingFallback", " A dialog options node found no options and is using a fallback node."))
			return ChildFallback;
		}
		return ChildOptions[SelectedOptionIndex];
	}

	
protected:

	/**
	* The option the user selected.
	*/
	UPROPERTY(Transient)
	int32 SelectedOptionIndex;

	/**
	* The mapping from the options presented to the player to internal option indices.
	* As some nodes could be omitted from the Options array, we need to store which option index corresponds to index of child in this node.
	*/
	UPROPERTY(Transient)
	TMap<int32, int32> OptionMapping;
};
