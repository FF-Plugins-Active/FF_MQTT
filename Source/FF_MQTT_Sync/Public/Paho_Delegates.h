#pragma once

#include "CoreMinimal.h"

#include "Paho_Structs.h"

#include "Paho_Delegates.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegate_Paho_Int, int32, Out_Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegate_Paho_String, FString, Out_Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegate_Paho_Json, FJsonObjectWrapper, Out_Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegate_Paho_Message, FPahoMessage, Out_Message);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FDelegate_Paho_Connection, bool, bIsSuccessfull, FJsonObjectWrapper, Out_Code);