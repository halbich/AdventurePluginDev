#pragma once

#include "CoreMinimal.h"
#include "GenericGraphRuntime/Public/GenericGraphNode.h"
#include "DialogGraphNode.generated.h"

UCLASS(Abstract, Blueprintable, HideCategories = (GenericGraphNode, GenericGraphNode_Editor))
class ADVENTUREPLUGINRUNTIME_API UDialogGraphNode : public UGenericGraphNode
{
	GENERATED_BODY()

public:
	UDialogGraphNode();
	virtual ~UDialogGraphNode();

	virtual FText GetDescription_Implementation() const;

	UPROPERTY(EditAnywhere, Category = "DialogGraphNode_Editor")
		FText DialogText;

#if WITH_EDITORONLY_DATA
	UPROPERTY(EditAnywhere, Category = "DialogGraphNode_Editor")
		int NumberOfSomething;
#endif

#if WITH_EDITOR

	virtual void SetNodeTitle(const FText& NewTitle) override;

	virtual bool CanCreateConnection(UGenericGraphNode* Other, FText& ErrorMessage) override;

#endif
};
