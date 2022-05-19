// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"

#include "GameFramework/SpringArmComponent.h" 
#include "Camera/CameraComponent.h" 

// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//craete a cameraboom
	cameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	cameraBoom->SetupAttachment(RootComponent);
	cameraBoom->TargetArmLength = 300.f; // distance btw camera and character
	cameraBoom->bUsePawnControlRotation = true; // rotate the armbase on the contoller


	// craete a followCamera
	followCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	followCamera->SetupAttachment(cameraBoom, USpringArmComponent::SocketName); //atach camera to end of boom
	cameraBoom->bUsePawnControlRotation = false; //camera doesnt rotate relative to arm
}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("BeginPlay() called"));
	
}

void AShooterCharacter::moveForward(float v)
{
	if ( (Controller != nullptr) && (v!=0.0f) )
	{
		//findingout the forward way

		const FRotator Rotation{ Controller->GetControlRotation() };
		const FRotator YawRotation{ 0, Rotation.Yaw,0 };

		const FVector Direction{ FRotationMatrix{YawRotation}.GetUnitAxis(EAxis :: X) };

		AddMovementInput(Direction, v);
	}
}

void AShooterCharacter::moveRight(float s)
{
	if ((Controller != nullptr) && (s != 0.0f))
	{
		//findingout the forward way

		const FRotator Rotation{ Controller->GetControlRotation() };
		const FRotator YawRotation{ 0, Rotation.Yaw,0 };

		const FVector Direction{ FRotationMatrix{YawRotation}.GetUnitAxis(EAxis::Y) };

		AddMovementInput(Direction, s);
	}
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("moveForward", this, &AShooterCharacter::moveForward);
	PlayerInputComponent->BindAxis("moveRight", this, &AShooterCharacter::moveRight);

}

