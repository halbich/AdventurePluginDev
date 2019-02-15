#include "Customizations/BaseClasses/ComboBoxDetailCustomization.h"
#include "DetailCategoryBuilder.h"
#include "DetailWidgetRow.h"
#include "Slate.h"

#define LOCTEXT_NAMESPACE "ComboBoxDetailCustomization"

void FComboBoxDetailCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailLayout)
{
	IdHandle = GetIdPropertyHandle(DetailLayout);
	DetailLayout.HideProperty(IdHandle);
	FName Id;
	IdHandle->GetValue(Id);

	FDetailWidgetRow& ComboBoxRow = DetailLayout.AddCustomRowToCategory(IdHandle, GetComboBoxName());

	ComboBoxRow.NameContent()
		[
			SNew(STextBlock)
			.Text(GetComboBoxName())
		];

	ComboBoxRow.ValueContent()
		[
			SAssignNew(ComboBox, SComboBox<FComboItemType>)
			.OptionsSource(&Options)
			.OnSelectionChanged(this, &FComboBoxDetailCustomization::OnSelectionChanged)
			.OnGenerateWidget(this, &FComboBoxDetailCustomization::MakeWidgetForName)
			[
				SNew(STextBlock)
				.Text(this, &FComboBoxDetailCustomization::GetCurrentItemLabel)
			]
		];

	TArray<TWeakObjectPtr<UObject>> Objects;
	DetailLayout.GetObjectsBeingCustomized(Objects);
	if (Objects.Num() > 0) ObjectBeingCustomized = Cast<UObject>(Objects[0]);

	ReloadComboBox(Id);
}

#undef LOCTEXT_NAMESPACE
