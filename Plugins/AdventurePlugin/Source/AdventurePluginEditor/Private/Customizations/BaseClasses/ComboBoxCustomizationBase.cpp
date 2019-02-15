#include "Customizations/BaseClasses/ComboBoxCustomizationBase.h"

#define LOCTEXT_NAMESPACE "ComboBoxCustomizationBase"

FComboBoxCustomizationBase::~FComboBoxCustomizationBase()
{
}

FText FComboBoxCustomizationBase::GetCurrentItemLabel() const
{
	if (IdHandle.IsValid())
	{
		FName Id;
		IdHandle->GetValue(Id);
		if (Id.IsValid())
		{
			return FText::FromName(Id);
		}
	}

	return LOCTEXT("InvalidComboEntryText", "<Empty>");
}

TSharedRef<SWidget> FComboBoxCustomizationBase::MakeWidgetForName(FComboItemType InOption)
{
	return SNew(STextBlock).Text(FText::FromName(*InOption));
}

void FComboBoxCustomizationBase::OnSelectionChanged(FComboItemType NewValue, ESelectInfo::Type)
{
	if (IdHandle.IsValid())
	{
		IdHandle->SetValue(NewValue.IsValid() ? *NewValue : FName());
	}
}

void FComboBoxCustomizationBase::ReloadComboBox()
{
	FComboBoxCustomizationBase::ReloadComboBox(FName());
}

void FComboBoxCustomizationBase::ReloadComboBox(FName Id)
{
	Options.Empty();
	ReloadOptions();

	FComboItemType Selected;
	if (!Id.IsNone())
	{
		for (TSharedPtr<FName>& Value : Options)
		{
			if (Id.IsEqual(*Value))
			{
				Selected = Value;
				break;
			}
		}
	}
	else if (IdHandle.IsValid())
	{
		IdHandle->ResetToDefault();
	}

	ComboBox->RefreshOptions();
	ComboBox->SetSelectedItem(Selected);
}

#undef LOCTEXT_NAMESPACE 
