#pragma once

#include "CoreMinimal.h"
#include "PropertyHandle.h"
#include "Customizations/BaseClasses/GraphNameCustomization.h"
/**
* Customization giving a combobox picker to FQuestGraphString, allowing the designer to select the variable name from a combobox.
* And the combobox offers only variables specified on the selected graph.
* @see FQuestGraphString
*/
class FQuestGraphStringCustomization : public FGraphNameCustomization
{
public:

	static TSharedRef<IPropertyTypeCustomization> MakeInstance();

protected:

	virtual TSharedPtr<IPropertyHandle> GetGraphPropertyHandle(TSharedRef<IPropertyHandle> StructPropertyHandle) const override;

	virtual TSharedPtr<IPropertyHandle> GetIdPropertyHandle(TSharedRef<IPropertyHandle> StructPropertyHandle) const override;

	virtual void ReloadOptions() override;
};