#include "Customizations/DialogGraphCustomization.h"
#include "DetailCategoryBuilder.h"
#include "DetailWidgetRow.h"

#define LOCTEXT_NAMESPACE "DialogGraphCustomization"

TSharedRef<IDetailCustomization> FDialogGraphCustomization::MakeInstance()
{
	return MakeShareable(new FDialogGraphCustomization);
}

void FDialogGraphCustomization::OnPlayerChanged()
{
	UObject* Obj;
	PickerPlayerHandle->GetValue(Obj);
	Graph->PlayerCharacter = Obj 
		? CastChecked<UAdventureCharacterBlueprint>(Obj)->GeneratedClass 
		: nullptr;
}

void FDialogGraphCustomization::OnNPCChanged()
{
	UObject* Obj;
	PickerNPCHandle->GetValue(Obj);
	Graph->NPCCharacter = Obj
		? CastChecked<UAdventureCharacterBlueprint>(Obj)->GeneratedClass
		: nullptr;
}

void FDialogGraphCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailLayout)
{
	TArray<TWeakObjectPtr<UObject>> Objects;
	DetailLayout.GetObjectsBeingCustomized(Objects);
	check(Objects.Num() > 0);
	Graph = CastChecked<UDialogGraph>(Objects[0]);

	PickerPlayerHandle = DetailLayout.GetProperty(GET_MEMBER_NAME_CHECKED(UDialogGraph, PickerPlayerCharacter));
	PickerPlayerHandle->SetOnPropertyValueChanged(FSimpleDelegate::CreateSP(this, &FDialogGraphCustomization::OnPlayerChanged));

	PickerNPCHandle = DetailLayout.GetProperty(GET_MEMBER_NAME_CHECKED(UDialogGraph, PickerNPCCharacter));
	PickerNPCHandle->SetOnPropertyValueChanged(FSimpleDelegate::CreateSP(this, &FDialogGraphCustomization::OnNPCChanged));
}

#undef LOCTEXT_NAMESPACE 