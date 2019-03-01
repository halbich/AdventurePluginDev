#pragma once

#include "CoreMinimal.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Text/SInlineEditableTextBlock.h"

/**
* Modification of Slate's SInlineEditableTextBlock, which autowraps the text block by default.
*/
class ADVENTUREPLUGINEDITOR_API SWrapTitleBox : public SInlineEditableTextBlock
{
public:

	void Construct(const FArguments& InArgs)
	{
		SInlineEditableTextBlock::Construct(InArgs);
		TextBlock->SetAutoWrapText(true);
	}
};