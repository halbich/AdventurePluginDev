#include "GraphNameCustomization.h"
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
	TSharedPtr<IPropertyHandle> NHandle = GetNamePropertyHandle(StructPropertyHandle);

	FText Desc = LOCTEXT("InvalidStructValue", "<Empty>");

	if (GHandle.IsValid() && NHandle.IsValid())
	{
		UObject* Obj;
		GHandle->GetValue(Obj);
		UGenericGraph* Graph = Cast<UGenericGraph>(Obj);
		FName Name;
		NHandle->GetValue(Name);
		if (Graph && Graph->IsValidLowLevel() && !Name.IsNone())
		{
			Desc = FText::Format(FText::FromString("{0}->{1}"), FText::FromString(Graph->Name), FText::FromName(Name));
		}
	}

	return Desc;
}

TSharedRef<SWidget> FGraphNameCustomization::MakeWidgetForName(FComboItemType InOption)
{
	return SNew(STextBlock).Text(FText::FromName(*InOption));
}

void FGraphNameCustomization::OnSelectionChanged(FComboItemType NewValue, ESelectInfo::Type)
{
	if (NameHandle.IsValid())
	{
		NameHandle->SetValue(NewValue.IsValid() ? *NewValue : FName());
	}
}

FText FGraphNameCustomization::GetCurrentItemLabel() const
{
	if (NameHandle.IsValid())
	{
		FName Name;
		NameHandle->GetValue(Name);
		if (Name.IsValid())
		{
			return FText::FromName(Name);
		}
	}

	return LOCTEXT("InvalidComboEntryText", "<Empty>");
}

void FGraphNameCustomization::ReloadComboBox()
{
	FGraphNameCustomization::ReloadComboBox(FName());
}

void FGraphNameCustomization::ReloadComboBox(FName Name)
{
	Options.Empty();
	ReloadOptions();
	
	FComboItemType Selected;
	if (!Name.IsNone())
	{
		for (TSharedPtr<FName>& Value : Options)
		{
			if (Name.IsEqual(*Value))
			{
				Selected = Value;
				break;
			}
		}
	}
	else if (NameHandle.IsValid())
	{
		NameHandle->ResetToDefault();
	}

	ComboBox->RefreshOptions();
	ComboBox->SetSelectedItem(Selected);
}

void FGraphNameCustomization::CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	GraphHandle = GetGraphPropertyHandle(StructPropertyHandle);
	NameHandle = GetNamePropertyHandle(StructPropertyHandle);

	StructBuilder.AddProperty(GraphHandle.ToSharedRef());

	GraphHandle->SetOnPropertyValueChanged(FSimpleDelegate::CreateSP(this, &FGraphNameCustomization::ReloadComboBox));

	FName Name;
	NameHandle->GetValue(Name);

	FDetailWidgetRow& ComboBoxRow = StructBuilder.AddCustomRow(LOCTEXT("Name", "Name"));

	ComboBoxRow.NameContent()
		[
			SNew(STextBlock)
			.Text(LOCTEXT("Name", "Name"))
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

	ReloadComboBox(Name);
}

#undef LOCTEXT_NAMESPACE