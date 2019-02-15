#include "Customizations/QuestGraphEventCustomization.h"
#include "Quest/Structs/QuestGraphEvent.h"
#include "Quest/Graph/QuestGraph.h"

TSharedRef<IPropertyTypeCustomization> FQuestGraphEventCustomization::MakeInstance()
{
	return MakeShareable(new FQuestGraphEventCustomization);
}

TSharedPtr<IPropertyHandle> FQuestGraphEventCustomization::GetGraphPropertyHandle(TSharedRef<IPropertyHandle> StructPropertyHandle) const
{
	return StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FQuestGraphEvent, Quest));
}

TSharedPtr<IPropertyHandle> FQuestGraphEventCustomization::GetIdPropertyHandle(TSharedRef<IPropertyHandle> StructPropertyHandle) const
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
		if (IsValid(Quest))
		{
			for (TPair<FName, FQuestEvent>& KeyValue : Quest->QuestEvents)
			{
				Options.Add(MakeShareable(new FName(KeyValue.Key)));
			}
		}
	}
}