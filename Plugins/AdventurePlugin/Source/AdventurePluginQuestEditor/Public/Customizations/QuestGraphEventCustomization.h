#pragma once

#include "CoreMinimal.h"
#include "PropertyHandle.h"
#include "Customizations/BaseClasses/GraphNameCustomization.h"
/**
* Customization giving a combobox picker to FQuestGraphEvent, allowing the designer to select the event name from a combobox.
* And the combobox offers only events defined on the selected graph.
* @see FQuestGraphEvent
*/
class FQuestGraphEventCustomization : public FGraphNameCustomization
{
public:

	static TSharedRef<IPropertyTypeCustomization> MakeInstance();

protected:

	virtual TSharedPtr<IPropertyHandle> GetGraphPropertyHandle(TSharedRef<IPropertyHandle> StructPropertyHandle) const override;

	virtual TSharedPtr<IPropertyHandle> GetIdPropertyHandle(TSharedRef<IPropertyHandle> StructPropertyHandle) const override;

	virtual void ReloadOptions() override;
};