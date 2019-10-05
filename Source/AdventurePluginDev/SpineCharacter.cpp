#include "SpineCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Based heavily on APaperCharacter
FName ASpineCharacter::SkeletonComponentName(TEXT("SpineSkeleton0"));
FName ASpineCharacter::RendererComponentName(TEXT("SpineRenderer0"));


ASpineCharacter::ASpineCharacter(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer.DoNotCreateDefaultSubobject(ACharacter::MeshComponentName))
{
	// Try to create the sprite component
	Skeleton = CreateOptionalDefaultSubobject<USpineSkeletonAnimationComponent>(ASpineCharacter::SkeletonComponentName);
	Renderer = CreateOptionalDefaultSubobject<USpineSkeletonRendererComponent>(ASpineCharacter::RendererComponentName); 
	if (Renderer)
	{
		Renderer->AlwaysLoadOnClient = true;
		Renderer->AlwaysLoadOnServer = true;
		Renderer->bOwnerNoSee = false;
		Renderer->bAffectDynamicIndirectLighting = true;
		Renderer->PrimaryComponentTick.TickGroup = TG_PrePhysics;
		Renderer->SetupAttachment(GetCapsuleComponent());
		static FName CollisionProfileName(TEXT("CharacterMesh"));
		Renderer->SetCollisionProfileName(CollisionProfileName);
		auto rotation = FQuat::MakeFromEuler(FVector(270,0,0));
		Renderer->SetRelativeRotation(rotation);
	}
}

void ASpineCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

}
