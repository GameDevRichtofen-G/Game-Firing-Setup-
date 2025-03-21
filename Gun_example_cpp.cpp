// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
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



void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//whatever after this...

}


void APlayerCharacter::Calculate_rotation_speed(float deltaTime)
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












