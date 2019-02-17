#pragma once

#include "CoreMinimal.h"
#include "Customizations/BaseClasses/ComboBoxPropertyTypeCustomization.h"

// https://answers.unrealengine.com/questions/384327/slate-scombobox-example.html
/**
* Base class for customizations that contain both a graph and some other property and allow the user to select first the graph and then a property based on that graph.
*/
class ADVENTUREPLUGINEDITOR_API FGraphNameCustomization : public FComboBoxPropertyTypeCustomization
{
public:

	virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;

	virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;

protected:

	virtual FText GetComboBoxName() const override;

	virtual FText GetHeaderRowName(TSharedRef<IPropertyHandle> StructPropertyHandle) const;

	virtual TSharedPtr<IPropertyHandle> GetGraphPropertyHandle(TSharedRef<IPropertyHandle> StructPropertyHandle) const = 0;

	TSharedPtr<IPropertyHandle> GraphHandle;
};