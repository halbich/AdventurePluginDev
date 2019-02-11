#pragma once

#include "CoreMinimal.h"
#include "SubclassOf.h"
#include "TextProperty.h"
#include "Map.h"
#include "GenericGraphNode.generated.h"

class UGenericGraph;

UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UGenericGraphNode : public UObject
{
	GENERATED_BODY()

public:
	UGenericGraphNode();
	virtual ~UGenericGraphNode();

	UPROPERTY(VisibleDefaultsOnly, Category = "GenericGraphNode")
	UGenericGraph* Graph;

	UPROPERTY(BlueprintReadOnly, Category = "GenericGraphNode")
	TArray<UGenericGraphNode*> ParentNodes;

	UPROPERTY(BlueprintReadOnly, Category = "GenericGraphNode")
	TArray<UGenericGraphNode*> ChildrenNodes;

	UPROPERTY()
		FGuid NodeGuid;

	UFUNCTION(BlueprintCallable, Category = "Adventure Plugin|Graph")
	bool IsLeafNode() const;

	UFUNCTION(BlueprintCallable, Category = "Adventure Plugin|Graph")
	UGenericGraph* GetGraph() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Adventure Plugin|Graph")
	FText GetDescription() const;
	virtual FText GetDescription_Implementation() const;

	virtual void ResetSpecialChildren() { }

	//////////////////////////////////////////////////////////////////////////
#if WITH_EDITORONLY_DATA
	UPROPERTY(EditDefaultsOnly, Category = "GenericGraphNode_Editor")
	FText NodeTitle;

	UPROPERTY(VisibleDefaultsOnly, Category = "GenericGraphNode_Editor")
	TSubclassOf<UGenericGraph> CompatibleGraphType;

	UPROPERTY(EditDefaultsOnly, Category = "GenericGraphNode_Editor")
	FLinearColor BackgroundColor;

	UPROPERTY(EditDefaultsOnly, Category = "GenericGraphNode_Editor")
	FText ContextMenuName;

	UPROPERTY(EditDefaultsOnly, Category = "GenericGraphNode_Editor")
	FText ContextMenuCategory;
#endif

#if WITH_EDITOR
	virtual FLinearColor GetBackgroundColor() const;

	virtual FText GetNodeTitle() const;

	virtual void SetNodeTitle(const FText& NewTitle);

	virtual bool CanCreateConnection(UGenericGraphNode* Other, FText& ErrorMessage);

	virtual bool CanAdd() const;

	virtual bool CanDelete() const;

	virtual bool CanDuplicate() const;

	virtual bool CanRename() const;
#endif
};
