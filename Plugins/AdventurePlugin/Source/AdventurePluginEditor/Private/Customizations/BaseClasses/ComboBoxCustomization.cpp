#include "Customizations/BaseClasses/ComboBoxCustomization.h"
#include "DetailCategoryBuilder.h"
#include "DetailWidgetRow.h"
#include "Slate.h"

#define LOCTEXT_NAMESPACE "ComboBoxCustomization"

void FComboBoxCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailLayout)
{
	SetIdHandle(DetailLayout);
	DetailLayout.HideProperty(IdHandle);
	FName Id;
	IdHandle->GetValue(Id);

	FDetailWidgetRow& ComboBoxRow = DetailLayout.AddCustomRowToCategory(IdHandle, GetComboBoxName());

	ComboBoxRow.NameContent()
		[
			SNew(STextBlock)
			.Text(GetComboBoxName())
		];

	TSharedPtr<SComboBox<FComboItemType>> ComboBox;

	ComboBoxRow.ValueContent()
		[
			SAssignNew(ComboBox, SComboBox<FComboItemType>)
			.OptionsSource(&Options)
		.OnSelectionChanged(this, &FComboBoxCustomization::OnSelectionChanged)
		.OnGenerateWidget(this, &FComboBoxCustomization::MakeWidgetForName)
		[
			SNew(STextBlock)
			.Text(this, &FComboBoxCustomization::GetCurrentItemLabel)
		]
		];

	TArray<TWeakObjectPtr<UObject>> Objects;
	DetailLayout.GetObjectsBeingCustomized(Objects);

	if (Objects.Num() > 0)
	{
		UObject* ObjectBeingCustomized = Cast<UObject>(Objects[0]);
		TSet<TSharedPtr<FName>> ComboBoxOptionsSet = GetComboBoxOptions(ObjectBeingCustomized);
		Options = ComboBoxOptionsSet.Array();
		FComboItemType SelectedId;
		for (TSharedPtr<FName> ComboBoxId : ComboBoxOptionsSet)
		{
			if (*ComboBoxId == Id)
			{
				SelectedId = ComboBoxId;
			}
		}
		ComboBox->RefreshOptions();
		ComboBox->SetSelectedItem(SelectedId);
	}
}

FText FComboBoxCustomization::GetCurrentItemLabel() const
{
	if (IdHandle.IsValid())
	{
		FName Name;
		IdHandle->GetValue(Name);
		if (Name.IsValid())
		{
			return FText::FromName(Name);
		}
	}

	return LOCTEXT("InvalidComboEntryText", "<Empty>");
}

TSharedRef<SWidget> FComboBoxCustomization::MakeWidgetForName(FComboItemType InOption)
{
	return SNew(STextBlock).Text(FText::FromName(*InOption));
}

void FComboBoxCustomization::OnSelectionChanged(FComboItemType NewValue, ESelectInfo::Type)
{
	if (IdHandle.IsValid())
	{
		IdHandle->SetValue(NewValue.IsValid() ? *NewValue : FName());
	}
}
void FComboBoxCustomization::SetIdHandle(IDetailLayoutBuilder& DetailLayout)
{
	check(false && "This method must be overriden");
}
FText FComboBoxCustomization::GetComboBoxName()
{
	check(false && "This method must be overriden");
	return FText();
}
TSet<FComboBoxCustomization::FComboItemType> FComboBoxCustomization::GetComboBoxOptions(UObject* ObjectBeingCustomized)
{
	check(false && "This method must be overriden");
	return TSet<FComboItemType>();
}

#undef LOCTEXT_NAMESPACE 
