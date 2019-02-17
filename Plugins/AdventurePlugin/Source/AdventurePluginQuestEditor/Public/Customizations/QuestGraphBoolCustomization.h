#pragma once

#include "CoreMinimal.h"
#include "PropertyHandle.h"
#include "Customizations/BaseClasses/GraphNameCustomization.h"
/**
* Customization giving a combobox picker to FQuestGraphBool, allowing the designer to select the variable name from a combobox.
* And the combobox offers only variables defined on the selected graph.
* @see FQuestGraphBool
*/
class FQuestGraphBoolCustomization : public FGraphNameCustomization
{
public:

	static TSharedRef<IPropertyTypeCustomization> MakeInstance();

protected:

	virtual TSharedPtr<IPropertyHandle> GetGraphPropertyHandle(TSharedRef<IPropertyHandle> StructPropertyHandle) const override;

	virtual TSharedPtr<IPropertyHandle> GetIdPropertyHandle(TSharedRef<IPropertyHandle> StructPropertyHandle) const override;

	virtual void ReloadOptions() override;
};