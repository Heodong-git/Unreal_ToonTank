// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

ATank::ATank()
{
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm Component"));
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	CameraComp->SetupAttachment(SpringArmComp);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

	// 컨트롤러의 경우 BeginPlay 에서 참조한다, 생성자에서는 아직 컨트롤러가 생성되지 않았을 수 있음
	PlayerControllerPtr = Cast<APlayerController>(GetController());
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
}

void ATank::Move(float Value)
{
	//UE_LOG(LogTemp, Display, TEXT("Value : %f"), Value);

	FVector Location = FVector::ZeroVector;
	Location.X = Value;
	double DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalOffset(Location * DeltaTime * Speed, true);
}

void ATank::Turn(float Value)
{
	// 초기화
	FRotator DeltaRotation = FRotator::ZeroRotator;
	DeltaRotation.Yaw = Value;
	double DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalRotation(DeltaRotation * DeltaTime * TurnRate, true);
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (nullptr != PlayerControllerPtr)
	{
		// 사용할 채널, 
		FHitResult HitResult;
		PlayerControllerPtr->GetHitResultUnderCursor(
			ECollisionChannel::ECC_Visibility,
			false,
			HitResult);

		// 충돌한 위치를 받아옴 
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 30, 12, FColor::Red, false, -1);
		RotateTurret(HitResult.ImpactPoint, DeltaTime);
	}
}

