// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"

ATower::ATower()
{
}

void ATower::BeginPlay()
{
	Super::BeginPlay();
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (nullptr != Tank)
	{
		// 탱크까지의 거리를 구한다.
		float Distance = FVector::Dist(Tank->GetActorLocation(), GetActorLocation());

		// 사거리 안에 들어왔다면
		if (Distance <= FireRange)
		{
			RotateTurret(Tank->GetActorLocation(), DeltaTime);
		}
	}
	
	// 사정거리 안에 있는지 체크 

	// 사정거리 안에 있다면 포탑이 탱크를 향해 회전하고

}