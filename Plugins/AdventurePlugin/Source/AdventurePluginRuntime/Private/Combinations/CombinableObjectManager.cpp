#include "Combinations/CombinableObjectManager.h"
#include "Templates/SharedPointer.h"
#include "AdventurePluginRuntime.h"

UCombinableObject* UCombinableObjectManager::GetCombinableObjectInstance(TSubclassOf<UCombinableObject> CombinableObjectClass, UObject* WorldObjectContext)
{
	if (CombinableObjectClass == nullptr)
	{
		LOG_Error(NSLOCTEXT("AdventurePlugin", "GetCombinableObjectInstance_GetObjectNull", "CombinableObjectManager::GetObject - Object is NULL."));
		return nullptr;
	}
	if (CombinableObjectClass->HasAnyClassFlags(CLASS_Abstract))
	{
		LOG_Error(NSLOCTEXT("AdventurePlugin", "GetCombinableObjectInstance_GetItemAbstract", "CombinableObjectManager::GetObject - Object is abstract."));
		return nullptr;
	}
	UCombinableObject** CombinableObjectInstance = CombinableObjects.Find(CombinableObjectClass);
	if (CombinableObjectInstance == nullptr || !IsValid(*CombinableObjectInstance))
	{
		RegisterObject(CombinableObjectClass, WorldObjectContext);
		CombinableObjectInstance = CombinableObjects.Find(CombinableObjectClass);
	}
	check(CombinableObjectInstance && *CombinableObjectInstance && "Item instance should never be null");
	return CombinableObjectInstance ? *CombinableObjectInstance : nullptr;
}

void UCombinableObjectManager::ClearMap()
{
	CombinableObjects.Empty();
}

void UCombinableObjectManager::RegisterObject(TSubclassOf<UCombinableObject> CombinableObjectClass, UObject* WorldObjectContext)
{
	UCombinableObject* NewCombinableObject = NewObject<UCombinableObject>(this, CombinableObjectClass);
	NewCombinableObject->Init();
	check(NewCombinableObject != nullptr && "It should always be possible to instantiate a combinable object");
	auto* world = WorldObjectContext ? WorldObjectContext->GetWorld() : nullptr;
	auto* gameInstance = world ? world->GetGameInstance() : nullptr;
	NewCombinableObject->CachedGameInstance = MakeWeakObjectPtr(gameInstance);
	CombinableObjects.Add(CombinableObjectClass, NewCombinableObject);
}