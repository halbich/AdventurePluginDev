#pragma once

#include "CoreMinimal.h"
#include "GenericGraph/GenericGraphNode.h"
#include "Structs/DialogLineData.h"
#include "DialogGraphNode.generated.h"

class UDialogueController;
class UAdventurePluginGameContext;


UCLASS(Abstract, Blueprintable, HideCategories = (GenericGraphNode, GenericGraphNode_Editor))
class ADVENTUREPLUGINRUNTIME_API UDialogGraphNode : public UGenericGraphNode
{
	GENERATED_BODY()

public:
	UDialogGraphNode();
	virtual ~UDialogGraphNode();

	virtual FText GetDescription_Implementation() const;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DialogNode")
		FName Id;

#if WITH_EDITORONLY_DATA

	UPROPERTY(EditAnywhere, Category = "DialogNode")
		FText Note;

#endif

#if WITH_EDITOR

	virtual void SetNodeTitle(const FText& NewTitle) override;

	virtual bool CanCreateConnection(UGenericGraphNode* Other, FText& ErrorMessage) override;

	virtual bool CanRename() const override;

#endif

	virtual bool Execute(UAdventurePluginGameContext* context)
	{
		return true;
	}

	virtual UDialogGraphNode* GetNextNode(UAdventurePluginGameContext* context)
	{
		return ChildrenNodes.Num() > 0 ? Cast<UDialogGraphNode>(ChildrenNodes[0]) : nullptr;
	}

	virtual bool IsDialogOption() const
	{
		return false;
	}

	virtual FDialogLineData GetDialogLine() const
	{
		return FDialogLineData();
	}

	
};
