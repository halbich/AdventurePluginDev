#pragma once

#include "CoreMinimal.h"
#include "GenericGraphRuntime/Public/GenericGraphNode.h"
#include "DialogGraphNode.generated.h"

UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UDialogGraphNode : public UGenericGraphNode
{
	GENERATED_BODY()

public:
	UDialogGraphNode();
	virtual ~UDialogGraphNode();

	virtual FText GetDescription_Implementation() const;

#if WITH_EDITORONLY_DATA
	UPROPERTY(EditAnywhere, Category = "DialogGraphNode_Editor")
	FText DialogText;

	UPROPERTY(EditAnywhere, Category = "DialogGraphNode_Editor")
	int NumberOfSomething;
#endif

#if WITH_EDITOR
	virtual bool CanCreateConnection(UGenericGraphNode* Other, FText& ErrorMessage);
#endif
};
