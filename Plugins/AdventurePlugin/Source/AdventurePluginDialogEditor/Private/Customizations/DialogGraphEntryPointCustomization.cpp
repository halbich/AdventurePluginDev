#include "Customizations/DialogGraphEntryPointCustomization.h"
#include "Dialog/Structs/DialogGraphEntryPoint.h"
#include "Dialog/Graph/DialogGraph.h"
#include "Dialog/Graph/DialogGraphNode_EntrySecondary.h"

TSharedRef<IPropertyTypeCustomization> FDialogGraphEntryPointCustomization::MakeInstance()
{
	return MakeShareable(new FDialogGraphEntryPointCustomization);
}

TSharedPtr<IPropertyHandle> FDialogGraphEntryPointCustomization::GetGraphPropertyHandle(TSharedRef<IPropertyHandle> StructPropertyHandle) const
{
	return StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FDialogGraphEntryPoint, Dialog));
}

TSharedPtr<IPropertyHandle> FDialogGraphEntryPointCustomization::GetIdPropertyHandle(TSharedRef<IPropertyHandle> StructPropertyHandle) const
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
		if (IsValid(Dialog))
		{
			Options.Add(MakeShareable(new FName(UDialogGraph::MainEntryName)));
			for (TPair<FName, UDialogGraphNode*> KeyValue : Dialog->SecondaryEntryPoints)
			{
				Options.Add(MakeShareable(new FName(KeyValue.Key)));
			}
		}
	}
}