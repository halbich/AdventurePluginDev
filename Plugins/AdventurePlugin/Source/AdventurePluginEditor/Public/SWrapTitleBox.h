#include "CoreMinimal.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Text/SInlineEditableTextBlock.h"

class ADVENTUREPLUGINEDITOR_API SWrapTitleBox : public SInlineEditableTextBlock
{
public:

	void Construct(const FArguments& InArgs)
	{
		SInlineEditableTextBlock::Construct(InArgs);
		TextBlock->SetAutoWrapText(true);
	}
};