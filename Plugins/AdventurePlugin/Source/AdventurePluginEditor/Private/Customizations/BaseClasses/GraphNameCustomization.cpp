#include "Customizations/BaseClasses/GraphNameCustomization.h"
#include "Widgets/Text/STextBlock.h"
#include "IDetailChildrenBuilder.h"
#include "DetailWidgetRow.h"
#include "GenericGraph/GenericGraph.h"

#define LOCTEXT_NAMESPACE "GraphNameCustomization"

void FGraphNameCustomization::CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	FText Desc = GetHeaderRowName(StructPropertyHandle);
	if (!Desc.IsEmpty())
	{
		HeaderRow.NameContent()
			[
				StructPropertyHandle->CreatePropertyNameWidget()
			]
		.ValueContent()
			.MaxDesiredWidth(400.0f)
			[
				SNew(STextBlock)
				.Text(Desc)
				.Font(StructCustomizationUtils.GetRegularFont())
			];
	}
}

FText FGraphNameCustomization::GetHeaderRowName(TSharedRef<IPropertyHandle> StructPropertyHandle) const
{
	TSharedPtr<IPropertyHandle> GHandle = GetGraphPropertyHandle(StructPropertyHandle);
	TSharedPtr<IPropertyHandle> IHandle = GetIdPropertyHandle(StructPropertyHandle);

	FText Desc = LOCTEXT("InvalidStructValue", "<Empty>");

	if (GHandle.IsValid() && IHandle.IsValid())
	{
		UObject* Obj;
		GHandle->GetValue(Obj);
		UGenericGraph* Graph = Cast<UGenericGraph>(Obj);
		FName Name;
		IHandle->GetValue(Name);
		if (IsValid(Graph) && !Name.IsNone())
		{
			Desc = FText::Format(FText::FromString(TEXT("{0}->{1}")), FText::FromString(Graph->Name), FText::FromName(Name));
		}
	}

	return Desc;
}

FText FGraphNameCustomization::GetComboBoxName() const
{
	return LOCTEXT("Name", "Name");
}

void FGraphNameCustomization::CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	GraphHandle = GetGraphPropertyHandle(StructPropertyHandle);
	IdHandle = GetIdPropertyHandle(StructPropertyHandle);

	StructBuilder.AddProperty(GraphHandle.ToSharedRef());

	GraphHandle->SetOnPropertyValueChanged(FSimpleDelegate::CreateSP(this, &FGraphNameCustomization::ReloadComboBox));

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
			.OnSelectionChanged(this, &FGraphNameCustomization::OnSelectionChanged)
			.OnGenerateWidget(this, &FGraphNameCustomization::MakeWidgetForName)
			[
				SNew(STextBlock)
				.Text(this, &FGraphNameCustomization::GetCurrentItemLabel)
			]
		];

	ReloadComboBox(Id);
}

#undef LOCTEXT_NAMESPACE