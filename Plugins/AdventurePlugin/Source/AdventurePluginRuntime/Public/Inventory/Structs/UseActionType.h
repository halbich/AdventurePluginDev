#pragma once

#include "CoreMinimal.h"
#include "UseActionType.generated.h"
/**
* Specifies the type of an action a user can do with an item or when combining items.
* For example, using a talking sword might be Talk action, combining two parts of an item might be Put Together action.
* Adventure Plugin does not give these actions meaning. The expected use case of this is changing a cursor icon when the user is about to do that action.
* The possible action types are defined in plugin configuration, @see UAdventurePluginConfig#UseActionTypes
*/
USTRUCT(BlueprintType)
struct ADVENTUREPLUGINRUNTIME_API FUseActionType
{
	GENERATED_USTRUCT_BODY()

public:
	/**
	* The name of this action type.
	* Must be defined in the Adventure Plugin configuration, @see UAdventurePluginConfig#UseActionTypes
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UseActionType")
	FName UseActionTypeName;
	/**
	* Compares two action types. They are same if their names are the same.
	*/
	bool operator==(const FUseActionType& OtherAction) const
	{
		return UseActionTypeName == OtherAction.UseActionTypeName;
	}
};