// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "ToonTanksPlayerController.h"


void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();

	HandleGameStart();
}

void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
	if (DeadActor == Tank)
	{
		Tank->HandleDestruction();
		APlayerController* PlayerController = Tank->GetPlayerController();
		if (nullptr != PlayerController)
		{
			ToonTanksPlayerController->SetPlayerEnabledState(false);
		}

		// ÅÊÅ© ÆÄ±«½Ã °ÔÀÓ¿À¹ö
		GameOver(false);
	}

	else if (ATower* Tower = Cast<ATower>(DeadActor))
	{
		Tower->HandleDestruction();
		--TargetTowers;

		if (0 >= TargetTowers)
		{
			GameOver(true);
		}
	}
}

void AToonTanksGameMode::HandleGameStart()
{
	TargetTowers = GetTargetCount();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	StartGame();
	
	if (nullptr != ToonTanksPlayerController)
	{
		ToonTanksPlayerController->SetPlayerEnabledState(false);

		FTimerHandle PlayerEnableTimerHandle;
		FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(
			ToonTanksPlayerController, 
			&AToonTanksPlayerController::SetPlayerEnabledState, 
			true
		);

		GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle,
			PlayerEnableTimerDelegate,
			StartDelay,
			false
		);
	}
}

int32 AToonTanksGameMode::GetTargetCount()
{
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), Actors);

	
	return Actors.Num();
}
