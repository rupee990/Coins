// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "TheCoinsGameMode.h"
#include "TheCoinsPlayerController.h"
#include "TheCoinsCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATheCoinsGameMode::ATheCoinsGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ATheCoinsPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}