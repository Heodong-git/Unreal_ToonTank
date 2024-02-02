// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

ATower::ATower()
{
}

void ATower::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}

void ATower::BeginPlay()
{
	Super::BeginPlay();
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
}

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (true == InFireRange())
	{
		RotateTurret(Tank->GetActorLocation(), DeltaTime);
	}
}

void ATower::CheckFireCondition()
{
	if (true == InFireRange())
	{
		Fire();
	}
}

bool ATower::InFireRange()
{
	if (nullptr != Tank)
	{
		// 탱크까지의 거리를 구한다.
		float Distance = FVector::Dist(Tank->GetActorLocation(), GetActorLocation());

		// 사거리 안에 들어왔다면
		if (Distance <= FireRange)
		{
			return true;
		}
	}

	return false;
}
