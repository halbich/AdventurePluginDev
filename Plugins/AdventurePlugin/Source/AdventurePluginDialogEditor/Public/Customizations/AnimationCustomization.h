#pragma once

#include "CoreMinimal.h"
#include "IDetailCustomization.h"
#include "Customizations/BaseClasses/ComboBoxDetailCustomization.h"

/**
* Property editor customization for UDialogGraphNode_PlayAnimationBase class,
* which replaces its UDialogGraphNode_PlayAnimationBase#AnimationName property
* with a ComboBox picker, allowing to choose one of defined animation states.
*/
class FAnimationCustomization : public FComboBoxDetailCustomization
{
public:

	/**
	* Creates an instance of FAnimationCustomization
	*/
	static TSharedRef<IDetailCustomization> MakeInstance();

	/**
	* Retrieves the UDialogGraphNode_PlayAnimationBase#AnimationName property
	* of the customized UDialogGraphNode_PlayAnimationBase,
	* which should be represented as a ComboBox.
	*/
	virtual TSharedPtr<IPropertyHandle> GetIdPropertyHandle(IDetailLayoutBuilder& DetailLayout) const override;

	/**
	* Retrieves the label of this ComboBox, which will be displayed next
	* to it in property editor.
	*/
	virtual FText GetComboBoxName() const override;

	/**
	* Fills the animation states to the FComboBoxCustomizationBase#Options array when the ComboBox reloads.
	*/
	virtual void ReloadOptions() override;
};