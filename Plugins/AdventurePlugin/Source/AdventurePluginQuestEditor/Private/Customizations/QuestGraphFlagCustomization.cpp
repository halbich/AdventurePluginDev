#include "Customizations/QuestGraphFlagCustomization.h"
#include "Quest/Structs/QuestGraphFlag.h"
#include "Quest/Graph/QuestGraph.h"
#include "Quest/Graph/QuestGraphNode_Flag.h"

TSharedRef<IPropertyTypeCustomization> FQuestGraphFlagCustomization::MakeInstance()
{
	return MakeShareable(new FQuestGraphFlagCustomization);
}

TSharedPtr<IPropertyHandle> FQuestGraphFlagCustomization::GetGraphPropertyHandle(TSharedRef<IPropertyHandle> StructPropertyHandle) const
{
	return StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FQuestGraphFlag, Quest));
}

TSharedPtr<IPropertyHandle> FQuestGraphFlagCustomization::GetIdPropertyHandle(TSharedRef<IPropertyHandle> StructPropertyHandle) const
{
	return StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FQuestGraphFlag, FlagName));
}

void FQuestGraphFlagCustomization::ReloadOptions()
{
	if (GraphHandle.IsValid())
	{
		UObject* QuestObj;
		GraphHandle->GetValue(QuestObj);
		UQuestGraph* Quest = Cast<UQuestGraph>(QuestObj);
		if (IsValid(Quest))
		{
			for (UGenericGraphNode* Node : Quest->AllNodes)
			{
				UQuestGraphNode_Flag* FlagNode = Cast<UQuestGraphNode_Flag>(Node);
				if (FlagNode)
				{
					Options.Add(MakeShareable(new FName(FlagNode->FlagName)));
				}
			}
		}
	}
}