#include "Macro.h"

FString UMacro::GetRealName(const UObject* obj)
{
	return GetRealName(obj->GetClass()->GetName());
}

FString UMacro::GetRealName(FString n)
{
	if (n.StartsWith("BP_")) n.RemoveFromStart("BP_");
	if (n.EndsWith("_C")) n.RemoveFromEnd("_C");
	return n;
}
