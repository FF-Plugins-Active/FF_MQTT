#include "Paho_Sync_Manager.h"

#pragma region Internals

bool APaho_Manager_Sync::SetSSLParams(FString In_Protocol, FPahoSslOptions In_Options)
{
	if (In_Protocol == TEXT("wss") || In_Protocol == TEXT("mqtts") || In_Protocol == TEXT("ssl") || In_Protocol == TEXT("WSS") || In_Protocol == TEXT("MQTTS") || In_Protocol == TEXT("SSL"))
	{
		this->SSL_Options = MQTTClient_SSLOptions_initializer;
		this->SSL_Options.enableServerCertAuth = 0;
		this->SSL_Options.verify = 1;

		if (!In_Options.CAPath.IsEmpty() && FPaths::FileExists(In_Options.CAPath))
		{
			this->SSL_Options.CApath = APaho_Manager_Sync::FStringToStdString(In_Options.CAPath).c_str();
		}

		if (!In_Options.Path_KeyStore.IsEmpty() && FPaths::FileExists(In_Options.Path_KeyStore))
		{
			this->SSL_Options.keyStore = APaho_Manager_Sync::FStringToStdString(In_Options.Path_KeyStore).c_str();
		}

		if (!In_Options.Path_TrustStore.IsEmpty() && FPaths::FileExists(In_Options.Path_TrustStore))
		{
			this->SSL_Options.trustStore = APaho_Manager_Sync::FStringToStdString(In_Options.Path_TrustStore).c_str();
		}

		if (!In_Options.Path_PrivateKey.IsEmpty() && FPaths::FileExists(In_Options.Path_PrivateKey))
		{
			this->SSL_Options.privateKey = APaho_Manager_Sync::FStringToStdString(In_Options.Path_PrivateKey).c_str();
		}

		if (!In_Options.PrivateKeyPass.IsEmpty())
		{
			this->SSL_Options.privateKeyPassword = APaho_Manager_Sync::FStringToStdString(In_Options.PrivateKeyPass).c_str();
		}

		if (!In_Options.CipherSuites.IsEmpty())
		{
			this->SSL_Options.enabledCipherSuites = APaho_Manager_Sync::FStringToStdString(In_Options.CipherSuites).c_str();
		}

		return true;
	}

	else
	{
		return false;
	}
}

#pragma endregion Internals

#pragma region Callbacks

void APaho_Manager_Sync::MessageDelivered(void* CallbackContext, MQTTClient_deliveryToken In_DeliveryToken)
{
	AsyncTask(ENamedThreads::GameThread, [CallbackContext, In_DeliveryToken]()
	{
		APaho_Manager_Sync* Owner = Cast<APaho_Manager_Sync>((APaho_Manager_Sync*)CallbackContext);
		
		if (!Owner)
		{
			return;
		}

		Owner->Delegate_Message_Delivered.Broadcast(In_DeliveryToken);
	});
}

int APaho_Manager_Sync::MessageArrived(void* CallbackContext, char* TopicName, int TopicLenght, MQTTClient_message* Message)
{
	const FString TopicNameStr = APaho_Manager_Sync::Utf8ToFString(TopicName);
	const FString PayloadStr = APaho_Manager_Sync::Utf8ToFString((const char*)Message->payload);

	FJsonObjectWrapper MessageJson;
	const bool bIsJsonOk = MessageJson.JsonObjectFromString(PayloadStr);

	FJsonObjectWrapper Arrived;
	Arrived.JsonObject->SetStringField(TEXT("TopicName"), TopicNameStr);
	Arrived.JsonObject->SetNumberField(TEXT("TopicLength"), TopicLenght);

	if (bIsJsonOk)
	{
		Arrived.JsonObject->SetObjectField(TEXT("Message"), MessageJson.JsonObject);
	}

	else
	{
		Arrived.JsonObject->SetStringField(TEXT("Message"), PayloadStr);
	}

	MQTTClient_freeMessage(&Message);
	MQTTClient_free(TopicName);

	AsyncTask(ENamedThreads::GameThread, [CallbackContext, Arrived]()
	{
		APaho_Manager_Sync* Owner = Cast<APaho_Manager_Sync>((APaho_Manager_Sync*)CallbackContext);

		if (!Owner)
		{
			return;
		}

		Owner->Delegate_Message_Arrived.Broadcast(Arrived);
	});

	return 1;
}

void APaho_Manager_Sync::ConnectionLost(void* CallbackContext, char* Cause)
{
	const FString CauseStr = StringCast<UTF8CHAR>(Cause).Get();

	AsyncTask(ENamedThreads::GameThread, [CallbackContext, CauseStr]()
	{
		APaho_Manager_Sync* Owner = Cast<APaho_Manager_Sync>((APaho_Manager_Sync*)CallbackContext);

		if (!Owner)
		{
			return;
		}

		Owner->Delegate_Connection_Lost.Broadcast(CauseStr);
	});
}

#pragma endregion Callbacks