#include "Customizations/QuestGraphStringCustomization.h"
#include "Quest/Structs/QuestGraphString.h"
#include "Quest/Graph/QuestGraph.h"

TSharedRef<IPropertyTypeCustomization> FQuestGraphStringCustomization::MakeInstance()
{
	return MakeShareable(new FQuestGraphStringCustomization);
}

TSharedPtr<IPropertyHandle> FQuestGraphStringCustomization::GetGraphPropertyHandle(TSharedRef<IPropertyHandle> StructPropertyHandle) const
{
	return StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FQuestGraphString, Quest));
}

TSharedPtr<IPropertyHandle> FQuestGraphStringCustomization::GetIdPropertyHandle(TSharedRef<IPropertyHandle> StructPropertyHandle) const
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
		if (IsValid(Quest))
		{
			for (TPair<FName, FStringVariable>& KeyValue : Quest->StringVariables)
			{
				Options.Add(MakeShareable(new FName(KeyValue.Key)));
			}
		}
	}
}