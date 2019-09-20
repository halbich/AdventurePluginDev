#pragma once

#include "CoreMinimal.h"
#include "Templates/SharedPointer.h"
#include "Engine/GameInstance.h"
#include "WorldContextProvidingObject.generated.h"

UCLASS()
class ADVENTUREPLUGINRUNTIME_API UWorldContextProvidingObject : public UObject {
	GENERATED_BODY()
public:
	TWeakObjectPtr<UGameInstance> CachedGameInstance;

	virtual class UWorld* GetWorld() const override {
		if (CachedGameInstance.IsValid())
		{
			return CachedGameInstance.Get()->GetWorld();
		}
		return nullptr;
	}
};