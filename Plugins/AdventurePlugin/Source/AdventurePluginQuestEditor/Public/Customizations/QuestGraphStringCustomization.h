#pragma once

#include "CoreMinimal.h"
#include "PropertyHandle.h"
#include "GraphNameCustomization.h"

class FQuestGraphStringCustomization : public FGraphNameCustomization
{
public:

	static TSharedRef<IPropertyTypeCustomization> MakeInstance();

protected:

	virtual TSharedPtr<IPropertyHandle> GetGraphPropertyHandle(TSharedRef<IPropertyHandle> StructPropertyHandle) const override;

	virtual TSharedPtr<IPropertyHandle> GetNamePropertyHandle(TSharedRef<IPropertyHandle> StructPropertyHandle) const override;

	virtual void ReloadOptions() override;
};