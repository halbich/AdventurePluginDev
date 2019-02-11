#pragma once

#include "CoreMinimal.h"
#include "Sound/SoundBase.h"
#include "DialogLineData.generated.h"

class UAdventureCharacter;

USTRUCT(BlueprintType)
struct FDialogLineData
{
	GENERATED_USTRUCT_BODY()
public:
	/** The text that should be displayed for this line. */
	UPROPERTY(BlueprintReadWrite, Category = "DialogPlayerOptionData")
		FText LineText;
	/** The text that should be displayed when the player is selecting what to say. */
	UPROPERTY(BlueprintReadWrite, Category = "DialogPlayerOptionData")
		FText OptionText;
	/** How long should the text stay on screen when displayed. Only used if audio track is not specified. */
	UPROPERTY(BlueprintReadWrite, Category = "DialogPlayerOptionData")
		float TextDuration;
	/** Specifies whether the user should be able to skip this particular line of dialogue or not.. */
	UPROPERTY(BlueprintReadWrite, Category = "DialogPlayerOptionData")
		bool bSkippable;
	/** The character saying this line.*/
	UPROPERTY(BlueprintReadWrite, Category = "DialogPlayerOptionData")
		UAdventureCharacter* SpeakerCharacter;
	/** Specifies the sound that should be played when this option is displayed. */
	UPROPERTY(BlueprintReadWrite, Category = "DialogPlayerOptionData")
		USoundBase* DialogSound;
	/** The text that should be displayed for this line. */
	UPROPERTY(BlueprintReadWrite, Category = "DialogPlayerOptionData")
		FName AnimationName;
	/** Game specific additional information, like text color etc. */
	UPROPERTY(BlueprintReadWrite, Category = "DialogPlayerOptionData")
		UObject* UserData;
};