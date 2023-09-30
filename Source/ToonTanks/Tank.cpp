// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"


ATank::ATank()
{
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    SpringArm->SetupAttachment(RootComponent);

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);
    
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);

    PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
    
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

    PlayerControllerRef = Cast<APlayerController>(GetController());
	
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	if (PlayerControllerRef) 
    {
        FHitResult HitResult;
        PlayerControllerRef->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility,
        false, HitResult);
        RotateTurret(HitResult.ImpactPoint);
    }
    

}



void ATank::Move(float Value)
{
    FVector DeltaLocation = FVector::ZeroVector;
    
    
    //jerry
    DeltaLocation.X = Value * Speed * UGameplayStatics::GetWorldDeltaSeconds(this);
     if (DeltaLocation.X > 0) 
    {
        Moving = true;
    }
    else {
        Moving = false;
    }

    AddActorLocalOffset(DeltaLocation, true);
}

void ATank::Turn(float Value) 
{
    FRotator DeltaRotation = FRotator::ZeroRotator;
    
    DeltaRotation.Yaw = Value * TurnRate * UGameplayStatics::GetWorldDeltaSeconds(this);
    if (!Moving && DeltaRotation.Yaw != 0) {
        
        DeltaRotation.Yaw *= TurnMultiplier;
        
    }
    
    AddActorLocalRotation(DeltaRotation, true);
    



}
