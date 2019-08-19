// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSGameMode.h"
#include "FPSHUD.h"
#include "FPSCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

AFPSGameMode::AFPSGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_Player"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPSHUD::StaticClass();
}

void AFPSGameMode::CompleteMission(APawn* InstigatorPawn )
{
	if (InstigatorPawn)
	{
		InstigatorPawn->DisableInput(nullptr);
		//AActor* NewViewTarget;

		if (SpectatingViewpointClass)
		{

			TArray<AActor*> ReturnedActor;
			UGameplayStatics::GetAllActorsOfClass(this, SpectatingViewpointClass, ReturnedActor);

			// change viewtarget if any valid actor found
			if (ReturnedActor.Num() > 0)
			{
				AActor* NewViewTarget = ReturnedActor[0];
				APlayerController* PC = Cast<APlayerController>(InstigatorPawn->GetController());
				if (PC)
				{
					PC->SetViewTargetWithBlend(NewViewTarget, 0.5f, EViewTargetBlendFunction::VTBlend_Cubic);
				}
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("SpectatingViewpointClass is nullptr. Please update GameMode class with valid subclass. Cannot change spectating view target."));
		}

	}

	OnMissionCompleted(InstigatorPawn);

}


