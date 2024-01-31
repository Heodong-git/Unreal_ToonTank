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

	// ��Ʈ�ѷ��� ��� BeginPlay ���� �����Ѵ�, �����ڿ����� ���� ��Ʈ�ѷ��� �������� �ʾ��� �� ����
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
	// �ʱ�ȭ
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
		// ����� ä��, 
		FHitResult HitResult;
		PlayerControllerPtr->GetHitResultUnderCursor(
			ECollisionChannel::ECC_Visibility,
			false,
			HitResult);

		// �浹�� ��ġ�� �޾ƿ� 
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 30, 12, FColor::Red, false, -1);
		RotateTurret(HitResult.ImpactPoint, DeltaTime);
	}
}

