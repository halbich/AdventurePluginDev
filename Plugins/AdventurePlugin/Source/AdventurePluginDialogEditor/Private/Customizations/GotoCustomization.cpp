#include "Customizations/GotoCustomization.h"
#include "Dialog/Graph/DialogGraphNode_Goto.h"
#include "DetailCategoryBuilder.h"
#include "DetailWidgetRow.h"

#define LOCTEXT_NAMESPACE "GotoCustomization"

TSharedRef<IDetailCustomization> FGotoCustomization::MakeInstance()
{
	return MakeShareable(new FGotoCustomization);
}
void FGotoCustomization::SetIdHandle(IDetailLayoutBuilder& DetailLayout)
{
	IdHandle = DetailLayout.GetProperty(GET_MEMBER_NAME_CHECKED(UDialogGraphNode_Goto, TargetNodeId));
}
FText FGotoCustomization::GetComboBoxName()
{
	return LOCTEXT("TargetNodeId", "Target Node Id");
}
TSet<FComboBoxCustomization::FComboItemType> FGotoCustomization::GetComboBoxOptions(UObject* ObjectBeingCustomized)
{
	TSet<FComboItemType> Ids;
	UDialogGraphNode_Goto* GotoNode = Cast<UDialogGraphNode_Goto>(ObjectBeingCustomized);
	if (GotoNode && GotoNode->IsValidLowLevel() && GotoNode->Graph && GotoNode->Graph->IsValidLowLevel())
	{
		for (auto Node : GotoNode->Graph->AllNodes)
		{
			UDialogGraphNode* GraphNode = Cast<UDialogGraphNode>(Node);
			if (GraphNode && GraphNode->IsValidLowLevel() && !GraphNode->Id.IsNone())
			{
				FComboItemType NewItem = MakeShareable(new FName(GraphNode->Id));
				Ids.Add(NewItem);
			}
		}
	}
	return Ids;
}

#undef LOCTEXT_NAMESPACE 
