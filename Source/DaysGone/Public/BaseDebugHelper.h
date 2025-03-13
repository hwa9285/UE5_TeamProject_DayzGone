#pragma once

namespace Debug
{
	static void Print(const FString& Msg, const FColor& Color = FColor::MakeRandomColor(), int32 InKey = -1)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(InKey, 7.0f, Color, Msg);

			UE_LOG(LogTemp, Warning, TEXT("%s"), *Msg);
		}
	}

	static void Print(const FString& FloatTitle, float FloatValueToPrint, const FColor& Color = FColor::MakeRandomColor(), int32 InKey = -1)
	{
		if (GEngine)
		{
			const FString FinalMsg = FloatTitle + TEXT(": ") + FString::SanitizeFloat(FloatValueToPrint);
			GEngine->AddOnScreenDebugMessage(InKey, 7.0f, Color, FinalMsg);

			UE_LOG(LogTemp, Warning, TEXT("%s"), *FinalMsg);
		}
	}

	static void PrintInTick(const FString& Msg, float DeltaSeconds, const FColor& Color = FColor::MakeRandomColor(), int32 InKey = -1)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(InKey, DeltaSeconds, Color, Msg);

			UE_LOG(LogTemp, Warning, TEXT("%s"), *Msg);
		}
	}
	
	static void PrintInTick(const FString& FloatTitle, float FloatValueToPrint, float DeltaSeconds, const FColor& Color = FColor::MakeRandomColor(), int32 InKey = -1)
	{
		if (GEngine)
		{
			const FString FinalMsg = FloatTitle + TEXT(": ") + FString::SanitizeFloat(FloatValueToPrint);
			GEngine->AddOnScreenDebugMessage(InKey, DeltaSeconds, Color, FinalMsg);

			UE_LOG(LogTemp, Warning, TEXT("%s"), *FinalMsg);
		}
	}
}