#include "CombinableObjectManager.h"
#include "AdventurePluginRuntime.h"

UCombinableObject* UCombinableObjectManager::GetCombinableObjectInstance(TSubclassOf<UCombinableObject> CombinableObjectClass)
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
		RegisterObject(CombinableObjectClass);
		CombinableObjectInstance = CombinableObjects.Find(CombinableObjectClass);
	}
	check(CombinableObjectInstance && *CombinableObjectInstance && "Item instance should never be null");
	return CombinableObjectInstance ? *CombinableObjectInstance : nullptr;
}

void UCombinableObjectManager::ClearMap()
{
	CombinableObjects.Empty();
}

void UCombinableObjectManager::RegisterObject(TSubclassOf<UCombinableObject> CombinableObjectClass)
{
	UCombinableObject* NewCombinableObject = NewObject<UCombinableObject>(this, CombinableObjectClass);
	NewCombinableObject->Init();
	check(NewCombinableObject != nullptr && "It should always be possible to instantiate a combinable object");
	CombinableObjects.Add(CombinableObjectClass, NewCombinableObject);
}