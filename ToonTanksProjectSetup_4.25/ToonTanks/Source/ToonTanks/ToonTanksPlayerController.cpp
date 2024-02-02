// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksPlayerController.h"

void AToonTanksPlayerController::SetPlayerEnabledState(const bool bPlayerEnaled)
{
	if (true == bPlayerEnaled)
	{
		GetPawn()->EnableInput(this);
	}
	else if (false == bPlayerEnaled)
	{
		GetPawn()->DisableInput(this);
	}
	
	bShowMouseCursor = bPlayerEnaled;
}

void AToonTanksPlayerController::BeginPlay()
{
	Super::BeginPlay();
}
