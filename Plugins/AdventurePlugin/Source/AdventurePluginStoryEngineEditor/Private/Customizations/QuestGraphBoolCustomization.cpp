#include "Customizations/QuestGraphBoolCustomization.h"
#include "StoryEngine/Structs/QuestGraphBool.h"
#include "StoryEngine/Graph/QuestGraph.h"

TSharedRef<IPropertyTypeCustomization> FQuestGraphBoolCustomization::MakeInstance()
{
	return MakeShareable(new FQuestGraphBoolCustomization);
}

TSharedPtr<IPropertyHandle> FQuestGraphBoolCustomization::GetGraphPropertyHandle(TSharedRef<IPropertyHandle> StructPropertyHandle) const
{
	return StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FQuestGraphBool, Quest));
}

TSharedPtr<IPropertyHandle> FQuestGraphBoolCustomization::GetNamePropertyHandle(TSharedRef<IPropertyHandle> StructPropertyHandle) const
{
	return StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FQuestGraphBool, BoolName));
}

void FQuestGraphBoolCustomization::ReloadOptions()
{
	if (GraphHandle.IsValid())
	{
		UObject* QuestObj;
		GraphHandle->GetValue(QuestObj);
		UQuestGraph* Quest = Cast<UQuestGraph>(QuestObj);
		if (Quest && Quest->IsValidLowLevel())
		{
			for (auto KeyValue : Quest->BoolVariables)
			{
				Options.Add(MakeShareable(new FName(KeyValue.Key)));
			}
		}
	}
}