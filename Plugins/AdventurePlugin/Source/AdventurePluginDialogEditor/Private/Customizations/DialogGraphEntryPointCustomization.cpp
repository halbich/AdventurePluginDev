#include "Customizations/DialogGraphEntryPointCustomization.h"
#include "Dialogue/Structs/DialogGraphEntryPoint.h"
#include "Dialogue/Graph/DialogGraph.h"
#include "Dialogue/Graph/DialogGraphNode_EntrySecondary.h"

TSharedRef<IPropertyTypeCustomization> FDialogGraphEntryPointCustomization::MakeInstance()
{
	return MakeShareable(new FDialogGraphEntryPointCustomization);
}

TSharedPtr<IPropertyHandle> FDialogGraphEntryPointCustomization::GetGraphPropertyHandle(TSharedRef<IPropertyHandle> StructPropertyHandle) const
{
	return StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FDialogGraphEntryPoint, Dialog));
}

TSharedPtr<IPropertyHandle> FDialogGraphEntryPointCustomization::GetNamePropertyHandle(TSharedRef<IPropertyHandle> StructPropertyHandle) const
{
	return StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FDialogGraphEntryPoint, EntryPointName));
}

void FDialogGraphEntryPointCustomization::ReloadOptions()
{
	if (GraphHandle.IsValid())
	{
		UObject* DialogObj;
		GraphHandle->GetValue(DialogObj);
		UDialogGraph* Dialog = Cast<UDialogGraph>(DialogObj);
		if (Dialog && Dialog->IsValidLowLevel())
		{
			Options.Add(MakeShareable(new FName(UDialogGraph::MainEntryName)));
			for (auto KeyValue : Dialog->SecondaryEntryPoints)
			{
				Options.Add(MakeShareable(new FName(KeyValue.Key)));
			}
		}
	}
}