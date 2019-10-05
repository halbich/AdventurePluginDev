
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SpineSkeletonAnimationComponent.h"
#include "SpineSkeletonRendererComponent.h"
#include "SpineCharacter.generated.h"

// Based heavily on APaperCharacter
UCLASS(config=Game)
class ASpineCharacter : public ACharacter
{
	GENERATED_BODY()

	// Name of the Skeleton component
	static FName SkeletonComponentName;
	static FName RendererComponentName;

private:
	/** The main skeletal mesh associated with this Character (optional sub-object). */
	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USpineSkeletonAnimationComponent* Skeleton;
	/** The main skeletal mesh associated with this Character (optional sub-object). */
	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USpineSkeletonRendererComponent* Renderer;
public:
	ASpineCharacter(const FObjectInitializer& ObjectInitializer);
	virtual void PostInitializeComponents() override;

	/** Returns Skeleton subobject **/
	FORCEINLINE class USpineSkeletonAnimationComponent* GetSkeleton() const { return Skeleton; }
	/** Returns Renderer subobject **/
	FORCEINLINE class USpineSkeletonRendererComponent* GetRenderer() const { return Renderer; }
};

