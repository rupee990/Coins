// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Coin.h"
#include "GameFramework/Actor.h"
#include "CoinSpawner.generated.h"

class UBoxComponent;
class UArrowComponent;

UENUM(BlueprintType)
enum SpawnType
{
    Random = 0, //Spawn coins at random location
    Grid,       //Spawns coins in grid fashion
};

UCLASS()
class THECOINS_API ACoinSpawner : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ACoinSpawner();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    virtual void Tick(float DeltaTime) override;

    virtual bool ShouldTickIfViewportsOnly() const override;

    void SpawnCoin();

    //Checks for ground and adjust passed Vector.
    FVector CheckForGround(const FVector _CoinPos);

    //Get a random Pickup direction
    FRotator GetRandomDirection();

public:
    //////////////////////Debug Options/////////////////////////////

    UPROPERTY(editAnywhere, Category = "Debug Options", meta = (DisplayName="Draw Spawner Debug"))
    bool bDrawDebug = true;

    UPROPERTY(editAnywhere, Category = "Debug Options", meta = (DisplayName = "Draw Coin Debug"))
    bool bCoinDebug = false;

    //////////////////////Spawner Properties/////////////////////////////

    //Number of coins to spawn.
    UPROPERTY(EditAnywhere, Category = "Spawner Properties")
    int32 numberOfCoins = 10;

    //How fast the Coins will Spawn
    UPROPERTY(EditAnywhere, Category = "Spawner Properties")
    float spawnRate = 1.0f;

    UPROPERTY(EditAnywhere, Category = "Spawner Properties")
    TEnumAsByte<SpawnType> spawnType = Random;

    //Coins will spawn within that box
    UPROPERTY(EditAnywhere, Category = "Spawner Properties")
    FVector2D spawnArea = FVector2D(128,128);

    //////////////////////Spawn Check Properties/////////////////////////////

    //How far should the spawner check for the ground.
    UPROPERTY(EditAnywhere, Category = "Spawn Checks Properties")
    float groundCheckDistance = 5000.0f;

    //How far off the ground to offset the coin
    UPROPERTY(EditAnywhere, Category = "Spawn Checks Properties")
    float groundOffset = 64.0f;

    //////////////////////Coin Properties/////////////////////////////

    //Pickup direction the coin should inherit
    UPROPERTY(EditAnywhere, Category = "Coin Properties")
    UArrowComponent* coinPickupDirection;

    //if true, a random direction will be given for the X axis
    UPROPERTY(EditAnywhere, Category = "Coin Properties")
    bool randXDirection;

    //if true, a random direction will be given for the Y axis
    UPROPERTY(EditAnywhere, Category = "Coin Properties")
    bool randYDirection;

    //if true, a random direction will be given for the Z axis
    UPROPERTY(EditAnywhere, Category = "Coin Properties")
    bool randZDirection;

    //Radius of the coin's collider
    UPROPERTY(EditAnywhere, Category = "Coin Radius")
    float coinRadius = 64.0f;

    FVector gridSpawnPostion;

private:
    FTimerHandle memberTimeHandle;

};
