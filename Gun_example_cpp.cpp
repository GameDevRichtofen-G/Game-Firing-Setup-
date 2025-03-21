// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Engine.h"
#include <Kismet/KismetMathLibrary.h>


APlayerCharacter::APlayerCharacter()
{

	PrimaryActorTick.bCanEverTick = true;
	//Init....
}


void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	//in the start of a game....
}

void APlayer_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("LeftMouseButton", IE_Pressed, this , &APlayerCharacter::Shoot)
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//whatever after this...
	FireRateTimer()
}


void APlayerCharacter::GunShot()
{

  if(!Firing) 
    return;
  float CurrentTime = GetWorld()->GetTimeSeconds(); 
  float DeltaShot = CurrentTime - LastTime;
  if (DeltaShot > 0)
    CurrentFirerate = 1/DeltaShot;
 
  LastTime = CurrentTime;


  ShootSpeed = FMath::Clamp((CurrentFirerate/6)*4, 2, 4);  

}
//call shoot function using a bind action method that has left mouse button
void APlayerCharacter::Shoot()
{
    if(Firing)
    	return
    Firing = true;
    Time = 60/600;
    GunShoot()
}

void APlayerCharacter::FireRateTimer()
{
	if(!Firing)
    	   return
	if(Time <= 0)
	{
		Firing = false;
		return
	}
	Time -= GetWorld()->GetWorldDeltaSecond();

}











