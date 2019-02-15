#include "Customizations/GotoCustomization.h"
#include "Dialog/Graph/DialogGraphNode_Goto.h"
#include "DetailCategoryBuilder.h"
#include "DetailWidgetRow.h"

#define LOCTEXT_NAMESPACE "GotoCustomization"

TSharedRef<IDetailCustomization> FGotoCustomization::MakeInstance()
{
	return MakeShareable(new FGotoCustomization);
}
TSharedPtr<IPropertyHandle> FGotoCustomization::GetIdPropertyHandle(IDetailLayoutBuilder& DetailLayout) const
{
	return DetailLayout.GetProperty(GET_MEMBER_NAME_CHECKED(UDialogGraphNode_Goto, TargetNodeId));
}
FText FGotoCustomization::GetComboBoxName() const
{
	return LOCTEXT("TargetNodeId", "Target Node Id");
}
void FGotoCustomization::ReloadOptions()
{
	UDialogGraphNode_Goto* GotoNode = Cast<UDialogGraphNode_Goto>(ObjectBeingCustomized);
	if (IsValid(GotoNode) && IsValid(GotoNode->Graph))
	{
		for (UGenericGraphNode* Node : GotoNode->Graph->AllNodes)
		{
			UDialogGraphNode* GraphNode = Cast<UDialogGraphNode>(Node);
			if (IsValid(GraphNode) && !GraphNode->Id.IsNone())
			{
				FComboItemType NewItem = MakeShareable(new FName(GraphNode->Id));
				Options.Add(NewItem);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE 
