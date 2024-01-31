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
		// ��ũ������ �Ÿ��� ���Ѵ�.
		float Distance = FVector::Dist(Tank->GetActorLocation(), GetActorLocation());

		// ��Ÿ� �ȿ� ���Դٸ�
		if (Distance <= FireRange)
		{
			RotateTurret(Tank->GetActorLocation(), DeltaTime);
		}
	}
	
	// �����Ÿ� �ȿ� �ִ��� üũ 

	// �����Ÿ� �ȿ� �ִٸ� ��ž�� ��ũ�� ���� ȸ���ϰ�

}