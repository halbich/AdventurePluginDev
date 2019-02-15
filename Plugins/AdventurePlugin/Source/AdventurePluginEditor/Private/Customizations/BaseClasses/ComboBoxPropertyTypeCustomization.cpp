#include "Customizations/BaseClasses/ComboBoxPropertyTypeCustomization.h"
#include "Widgets/Text/STextBlock.h"
#include "DetailCategoryBuilder.h"
#include "IDetailChildrenBuilder.h"
#include "DetailWidgetRow.h"
#include "Slate.h"

#define LOCTEXT_NAMESPACE "ComboBoxPropertyTypeCustomization"

void FComboBoxPropertyTypeCustomization::CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
}

void FComboBoxPropertyTypeCustomization::CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	IdHandle = GetIdPropertyHandle(StructPropertyHandle);

	FName Id;
	IdHandle->GetValue(Id);

	FDetailWidgetRow& ComboBoxRow = StructBuilder.AddCustomRow(GetComboBoxName());

	ComboBoxRow.NameContent()
		[
			SNew(STextBlock)
			.Text(GetComboBoxName())
		];

	ComboBoxRow.ValueContent()
		[
			SAssignNew(ComboBox, SComboBox<FComboItemType>)
			.OptionsSource(&Options)
			.OnSelectionChanged(this, &FComboBoxPropertyTypeCustomization::OnSelectionChanged)
			.OnGenerateWidget(this, &FComboBoxPropertyTypeCustomization::MakeWidgetForName)
			[
				SNew(STextBlock)
				.Text(this, &FComboBoxPropertyTypeCustomization::GetCurrentItemLabel)
			]
		];

	ReloadComboBox(Id);
}

#undef LOCTEXT_NAMESPACE
