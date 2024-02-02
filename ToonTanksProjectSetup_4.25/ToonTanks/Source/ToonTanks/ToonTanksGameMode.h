// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTanksGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

	// 이렇게 선언하면 블루프린트에서 사용이 가능하고 실제 구현을 하지 않아도 된다. 
	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

public:
	void ActorDied(AActor* DeadActor);

private:
	class ATank* Tank;
	class AToonTanksPlayerController* ToonTanksPlayerController;


	float StartDelay = 3.0f;
	void HandleGameStart();

};
