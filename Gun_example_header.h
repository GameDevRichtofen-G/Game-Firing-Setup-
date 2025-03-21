#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class RADAR_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	AAI_Character();

protected:

	virtual void BeginPlay() override;

public:
	
	virtual void Tick(float DeltaTime) override;


protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Variables")
		float ShootSpeed;
        UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Variables")
		bool Firing;
private:
	float LastTime;
	float CurrentFirerate;

	void GunShoot();
        void FireRateTimer();
        void Shoot();


};












