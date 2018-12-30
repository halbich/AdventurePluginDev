#include "Customizations/QuestGraphEventCustomization.h"
#include "StoryEngine/Structs/QuestGraphEvent.h"
#include "StoryEngine/Graph/QuestGraph.h"

TSharedRef<IPropertyTypeCustomization> FQuestGraphEventCustomization::MakeInstance()
{
	return MakeShareable(new FQuestGraphEventCustomization);
}

TSharedPtr<IPropertyHandle> FQuestGraphEventCustomization::GetGraphPropertyHandle(TSharedRef<IPropertyHandle> StructPropertyHandle) const
{
	return StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FQuestGraphEvent, Quest));
}

TSharedPtr<IPropertyHandle> FQuestGraphEventCustomization::GetNamePropertyHandle(TSharedRef<IPropertyHandle> StructPropertyHandle) const
{
	return StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FQuestGraphEvent, EventName));
}

void FQuestGraphEventCustomization::ReloadOptions()
{
	if (GraphHandle.IsValid())
	{
		UObject* QuestObj;
		GraphHandle->GetValue(QuestObj);
		UQuestGraph* Quest = Cast<UQuestGraph>(QuestObj);
		if (Quest && Quest->IsValidLowLevel())
		{
			for (auto KeyValue : Quest->QuestEvents)
			{
				Options.Add(MakeShareable(new FName(KeyValue.Key)));
			}
		}
	}
}