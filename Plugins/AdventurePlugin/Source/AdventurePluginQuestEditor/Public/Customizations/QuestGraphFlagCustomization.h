#pragma once

#include "CoreMinimal.h"
#include "PropertyHandle.h"
#include "Customizations/BaseClasses/GraphNameCustomization.h"
/**
* Customization giving a combobox picker to FQuestGraphFlag, allowing the designer to select the flag name from a combobox.
* And the combobox offers only flags defined on the selected graph.
* @see FQuestGraphFlag
*/
class FQuestGraphFlagCustomization : public FGraphNameCustomization
{
public:

	static TSharedRef<IPropertyTypeCustomization> MakeInstance();

protected:

	virtual TSharedPtr<IPropertyHandle> GetGraphPropertyHandle(TSharedRef<IPropertyHandle> StructPropertyHandle) const override;

	virtual TSharedPtr<IPropertyHandle> GetIdPropertyHandle(TSharedRef<IPropertyHandle> StructPropertyHandle) const override;

	virtual void ReloadOptions() override;
};