#pragma once

#include "CoreMinimal.h"
#include "IPropertyTypeCustomization.h"
#include "PropertyHandle.h"
#include "Widgets/Input/SComboBox.h"

// https://answers.unrealengine.com/questions/384327/slate-scombobox-example.html
class FGraphNameCustomization : public IPropertyTypeCustomization
{
public:

	typedef TSharedPtr<FName> FComboItemType;

	virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;

	virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;

protected:

	TSharedRef<SWidget> MakeWidgetForName(FComboItemType InOption);

	virtual void OnSelectionChanged(FComboItemType NewValue, ESelectInfo::Type);

	virtual void ReloadComboBox();

	virtual void ReloadComboBox(FName Name);

	virtual FText GetHeaderRowName(TSharedRef<IPropertyHandle> StructPropertyHandle) const;

	virtual FText GetCurrentItemLabel() const;

	virtual TSharedPtr<IPropertyHandle> GetGraphPropertyHandle(TSharedRef<IPropertyHandle> StructPropertyHandle) const = 0;

	virtual TSharedPtr<IPropertyHandle> GetNamePropertyHandle(TSharedRef<IPropertyHandle> StructPropertyHandle) const = 0;

	virtual void ReloadOptions() = 0;

	TArray<FComboItemType> Options;
	TSharedPtr<IPropertyHandle> NameHandle;
	TSharedPtr<IPropertyHandle> GraphHandle;
	TSharedPtr<SComboBox<FComboItemType>> ComboBox;
};