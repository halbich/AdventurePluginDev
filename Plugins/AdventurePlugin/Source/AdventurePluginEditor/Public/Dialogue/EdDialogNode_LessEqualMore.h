#pragma once

#include "CoreMinimal.h"
#include "Slate.h"
#include "Dialogue/EdDialogNode.h"
#include "Dialogue/SEdDialogNode_LessEqualMore.h"
#include "EdDialogNode_LessEqualMore.generated.h"

UCLASS()
class ADVENTUREPLUGINEDITOR_API UEdDialogNode_LessEqualMore : public UEdDialogNode
{
	GENERATED_BODY()

public:

	UEdDialogNode_LessEqualMore() { }
	virtual ~UEdDialogNode_LessEqualMore() { }

	virtual TSharedPtr<class SGraphNode> CreateVisualWidget() override
	{
		return SNew(SEdDialogNode_LessEqualMore, this);
	}
};