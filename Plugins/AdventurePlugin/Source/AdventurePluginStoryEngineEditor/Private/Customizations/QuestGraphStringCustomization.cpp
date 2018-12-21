#include "Customizations/QuestGraphStringCustomization.h"
#include "StoryEngine/Structs/QuestGraphString.h"
#include "StoryEngine/Graph/QuestGraph.h"

TSharedRef<IPropertyTypeCustomization> FQuestGraphStringCustomization::MakeInstance()
{
	return MakeShareable(new FQuestGraphStringCustomization);
}

TSharedPtr<IPropertyHandle> FQuestGraphStringCustomization::GetGraphPropertyHandle(TSharedRef<IPropertyHandle> StructPropertyHandle) const
{
	return StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FQuestGraphString, Quest));
}

TSharedPtr<IPropertyHandle> FQuestGraphStringCustomization::GetNamePropertyHandle(TSharedRef<IPropertyHandle> StructPropertyHandle) const
{
	return StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FQuestGraphString, StringName));
}

void FQuestGraphStringCustomization::ReloadOptions()
{
	if (GraphHandle.IsValid())
	{
		UObject* QuestObj;
		GraphHandle->GetValue(QuestObj);
		UQuestGraph* Quest = Cast<UQuestGraph>(QuestObj);
		if (Quest && Quest->IsValidLowLevel())
		{
			for (auto KeyValue : Quest->StringVariables)
			{
				Options.Add(MakeShareable(new FName(KeyValue.Key)));
			}
		}
	}
}