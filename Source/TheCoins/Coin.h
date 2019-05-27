// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Coin.generated.h"

class USphereComponent;
class UArrowComponent;

UCLASS()
class THECOINS_API ACoin : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACoin();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    USphereComponent* collider = nullptr;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    UStaticMeshComponent* mesh = nullptr;

    //How fast the Rotation of the coin happens
    UPROPERTY(EditAnywhere, Category = "In-Game")
    float rotationRate = 1.2;

    //Pickup direction
    UPROPERTY(EditAnywhere, Category = "Pickup")
    UArrowComponent* arrow = nullptr;

    //How accurate the detection is, -1.0f being pickup from any direction and 1.0f being precise.
    UPROPERTY(EditAnywhere, Category = "Pickup")
    float  directionAccuracy = 0.8f;



};
