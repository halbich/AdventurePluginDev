#include "Customizations/QuestGraphIntegerCustomization.h"
#include "Quest/Structs/QuestGraphInteger.h"
#include "Quest/Graph/QuestGraph.h"

TSharedRef<IPropertyTypeCustomization> FQuestGraphIntegerCustomization::MakeInstance()
{
	return MakeShareable(new FQuestGraphIntegerCustomization);
}

TSharedPtr<IPropertyHandle> FQuestGraphIntegerCustomization::GetGraphPropertyHandle(TSharedRef<IPropertyHandle> StructPropertyHandle) const
{
	return StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FQuestGraphInteger, Quest));
}

TSharedPtr<IPropertyHandle> FQuestGraphIntegerCustomization::GetNamePropertyHandle(TSharedRef<IPropertyHandle> StructPropertyHandle) const
{
	return StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FQuestGraphInteger, IntegerName));
}

void FQuestGraphIntegerCustomization::ReloadOptions()
{
	if (GraphHandle.IsValid())
	{
		UObject* QuestObj;
		GraphHandle->GetValue(QuestObj);
		UQuestGraph* Quest = Cast<UQuestGraph>(QuestObj);
		if (Quest && Quest->IsValidLowLevel())
		{
			for (auto KeyValue : Quest->IntegerVariables)
			{
				Options.Add(MakeShareable(new FName(KeyValue.Key)));
			}
		}
	}
}