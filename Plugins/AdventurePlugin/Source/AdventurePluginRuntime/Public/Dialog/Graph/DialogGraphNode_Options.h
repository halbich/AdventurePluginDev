#pragma once

#include "CoreMinimal.h"
#include "Common/AdventurePluginGameContext.h"
#include "DialogGraph.h"
#include "DialogGraphNode.h"
#include "DialogGraphNode_Player.h"
#include "Presenter/DialogPresenterInterface.h"
#include "NodeInterfaces/DialogNodeShowOptionsCallbackInterface.h"
#include "DialogGraphNode_Options.generated.h"

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

	UPROPERTY(VisibleAnywhere, Category = "OptionsNode")
	uint32 ChoiceCount;

	UPROPERTY(BlueprintReadOnly)
	UDialogGraphNode* ChildFallback;

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

	virtual bool Execute(UAdventurePluginGameContext* GameContext) override
	{
		SelectedOptionIndex = -1;
		OptionMapping.Reset();
		// Go through all child nodes, if visiting something other than Player Line, go to their children, find all Player Lines and show them to the player.
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
			// This is fallback - execution of this node will end and the Controller will call GetNextNode, which will, thanks to selectedOptionIndex being -1, return ChildFallback.
			// If ChildFallback is nullptr, execution of graph will end.
			return true;
		}
		return false;
	}

	virtual bool DialogOptionSelected_Implementation(int32 SelectedNodeIndex, UDialogController* DialogController) override
	{
		this->SelectedOptionIndex = OptionMapping[SelectedNodeIndex];
		return true;
	}

	virtual UDialogGraphNode* GetNextNode(UAdventurePluginGameContext* GameContext) override
	{
		if (SelectedOptionIndex < 0)
		{
			return ChildFallback;
		}
		check(SelectedOptionIndex < (int32)ChoiceCount);
		if (SelectedOptionIndex >= (int32)ChoiceCount)
		{
			// TODO: Log warning.
			return ChildFallback;
		}
		return ChildOptions[SelectedOptionIndex];
	}

	
protected:
	UPROPERTY(Transient)
	int32 SelectedOptionIndex;

	UPROPERTY(Transient)
	TMap<int32, int32> OptionMapping;
};
