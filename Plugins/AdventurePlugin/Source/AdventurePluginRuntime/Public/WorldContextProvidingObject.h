#pragma once

#include "CoreMinimal.h"
#include "Templates/SharedPointer.h"
#include "WorldContextProvidingObject.generated.h"

UCLASS()
class ADVENTUREPLUGINRUNTIME_API UWorldContextProvidingObject : public UObject {
	GENERATED_BODY()
public:
	TWeakObjectPtr<UWorld> CachedWorldObject;

	virtual class UWorld* GetWorld() const override {
		if (CachedWorldObject.IsValid()) 
		{
			return CachedWorldObject.Get();
		}
		return nullptr;
	}
};