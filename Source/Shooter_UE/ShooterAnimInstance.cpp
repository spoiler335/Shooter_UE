// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAnimInstance.h"
#include "ShooterCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"


void UShooterAnimInstance::NativeInitializeAnimation()
{
	if (shooterCharacter == nullptr)
	{
		shooterCharacter = Cast<AShooterCharacter>(TryGetPawnOwner());
	}

	if (shooterCharacter)
	{
		//get the lateral spped of the char from velocity
		FVector Velocity{ shooterCharacter->GetVelocity() };
		Velocity.Z = 0;
		speed = Velocity.Size();

		bIsInAir = shooterCharacter->GetCharacterMovement()->IsFalling();

		if (shooterCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0)
		{
			bIsAccelrating = true;
		}

		else
		{
			bIsAccelrating = false;
		}
	}

}

void UShooterAnimInstance::UpdateAnimationProperties(float deltaTime)
{
	shooterCharacter = Cast<AShooterCharacter>(TryGetPawnOwner());
}
