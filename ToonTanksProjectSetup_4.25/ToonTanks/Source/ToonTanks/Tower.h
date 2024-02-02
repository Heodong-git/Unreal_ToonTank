// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()

public:
	ATower();
	
	void HandleDestruction();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	class ATank* Tank;
	
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float FireRange = 900.0f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float TurnRate = 200.0f;
	
	FTimerHandle FireRateTimerHandle;	 // 타이머핸들
	float FireRate = 2.5f;				 // 간격 
	void CheckFireCondition();			 // 콜백함수 

	bool InFireRange();
};
