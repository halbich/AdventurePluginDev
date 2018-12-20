#include "QuestGraphFlagCustomization.h"
#include "StoryEngine/Structs/QuestGraphFlag.h"
#include "StoryEngine/Graph/QuestGraph.h"
#include "StoryEngine/Graph/QuestGraphNode_Flag.h"

TSharedRef<IPropertyTypeCustomization> FQuestGraphFlagCustomization::MakeInstance()
{
	return MakeShareable(new FQuestGraphFlagCustomization);
}

TSharedPtr<IPropertyHandle> FQuestGraphFlagCustomization::GetGraphPropertyHandle(TSharedRef<IPropertyHandle> StructPropertyHandle) const
{
	return StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FQuestGraphFlag, Quest));
}

TSharedPtr<IPropertyHandle> FQuestGraphFlagCustomization::GetNamePropertyHandle(TSharedRef<IPropertyHandle> StructPropertyHandle) const
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
		if (Quest && Quest->IsValidLowLevel())
		{
			for (UGenericGraphNode* Node : Quest->AllNodes)
			{
				auto* FlagNode = Cast<UQuestGraphNode_Flag>(Node);
				if (FlagNode)
				{
					Options.Add(MakeShareable(new FName(FlagNode->FlagName)));
				}
			}
		}
	}
}