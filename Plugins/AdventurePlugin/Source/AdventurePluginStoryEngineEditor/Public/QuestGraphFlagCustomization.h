#pragma once

#include "CoreMinimal.h"
//#include "IPropertyTypeCustomization.h"
#include "PropertyHandle.h"
//#include "Widgets/Text/STextBlock.h"
//#include "Widgets/Input/SComboBox.h"
#include "GraphNameCustomization.h"

class FQuestGraphFlagCustomization : public FGraphNameCustomization
{
public:

	static TSharedRef<IPropertyTypeCustomization> MakeInstance();

protected:

	virtual TSharedPtr<IPropertyHandle> GetGraphPropertyHandle(TSharedRef<IPropertyHandle> StructPropertyHandle) const override;

	virtual TSharedPtr<IPropertyHandle> GetNamePropertyHandle(TSharedRef<IPropertyHandle> StructPropertyHandle) const override;

	virtual void ReloadOptions() override;

/*
public:

	typedef TSharedPtr<FName> FComboItemType;

	virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;

	virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;

	static TSharedRef<IPropertyTypeCustomization> MakeInstance();

protected:

	TSharedRef<SWidget> MakeWidgetForName(FComboItemType InOption);

	virtual void OnSelectionChanged(FComboItemType NewValue, ESelectInfo::Type);

	virtual void ReloadComboBox();

	virtual void ReloadComboBox(FName Name);

	virtual FText GetHeaderRowName(TSharedRef<IPropertyHandle> StructPropertyHandle) const;

	virtual FText GetCurrentItemLabel() const;

	TArray<FComboItemType> Options;
	TSharedPtr<IPropertyHandle> QuestHandle;
	TSharedPtr<IPropertyHandle> FlagNameHandle;
	TSharedPtr<SComboBox<FComboItemType>> ComboBox;
*/
};