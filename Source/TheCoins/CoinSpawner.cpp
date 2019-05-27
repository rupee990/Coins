// Fill out your copyright notice in the Description page of Project Settings.

#include "CoinSpawner.h"
#include "Coin.h"
#include "TimerManager.h"
#include "Engine/World.h"

#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "DrawDebugHelpers.h"

// Sets default values
ACoinSpawner::ACoinSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    RootComponent = CreateDefaultSubobject<USceneComponent>("Root");

    //Arrow showing the pickup direction
    coinPickupDirection = CreateDefaultSubobject<UArrowComponent>(TEXT("PickupDirection"));
    coinPickupDirection->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ACoinSpawner::BeginPlay()
{
	Super::BeginPlay();

    if (spawnType == SpawnType::Grid)
    {
        gridSpawnPostion = GetActorLocation();
        gridSpawnPostion.X -= spawnArea.X;
        gridSpawnPostion.Y -= spawnArea.Y;
    }

    GetWorldTimerManager().SetTimer(memberTimeHandle, this, &ACoinSpawner::SpawnCoin, spawnRate, spawnRate);
	
}

// Called every frame
void ACoinSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if(bDrawDebug)
        DrawDebugBox(GetWorld(), GetActorLocation(), FVector(spawnArea, 0.0f), FColor(255, 0, 0));

}

bool ACoinSpawner::ShouldTickIfViewportsOnly() const
{
    if(bDrawDebug)
        DrawDebugBox(GetWorld(), GetActorLocation(), FVector(spawnArea, 0.0f), FColor(255, 0, 0));

    return true;
}

void ACoinSpawner::SpawnCoin()
{
    if (numberOfCoins > 0)
    {
        if (spawnType == Random)
        {

            //Get Position in a Box
            //FVector extent = spawnBox->GetScaledBoxExtent();
            float rx = GetActorLocation().X + (FMath::FRandRange(-spawnArea.X, spawnArea.X));
            float ry = GetActorLocation().Y + (FMath::FRandRange(-spawnArea.Y, spawnArea.Y));

            //Make sure that the coin doesnt spawn in each other.
            FActorSpawnParameters param;
            param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

            //Spawn actor   
            ACoin* coin = GetWorld()->SpawnActor<ACoin>(CheckForGround(FVector(rx, ry, GetActorLocation().Z)), FRotator(0.0f, 0.0f, 0.0f), param);

            if(randXDirection || randYDirection || randZDirection)
                coin->arrow->SetWorldRotation(GetRandomDirection());
            else
                coin->arrow->SetWorldRotation(coinPickupDirection->GetComponentRotation());

            numberOfCoins--;
        }
        else if (spawnType == Grid)
        {

            FActorSpawnParameters param;
            param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

            //Spawn actor   
            ACoin* coin = GetWorld()->SpawnActor<ACoin>(CheckForGround(gridSpawnPostion), FRotator(0.0f, 0.0f, 0.0f), param);

            //Check if user wants random pickup direction
            if (randXDirection || randYDirection || randZDirection)
                coin->arrow->SetWorldRotation(GetRandomDirection());
            else
                coin->arrow->SetWorldRotation(coinPickupDirection->GetComponentRotation());

            //Increment Position
            gridSpawnPostion.X += coin->collider->GetScaledSphereRadius() * 2;
            gridSpawnPostion.Z = GetActorLocation().Z;
            if (gridSpawnPostion.X > GetActorLocation().X + spawnArea.X + coin->collider->GetScaledSphereRadius())
            {
                gridSpawnPostion.X = GetActorLocation().X - spawnArea.X;
                gridSpawnPostion.Y += coin->collider->GetScaledSphereRadius() * 2;
            }

            numberOfCoins--;
        }
    }
    else
    {
        //gridSpawnPostion = FVector(0, 0, 0);
        GetWorldTimerManager().ClearTimer(memberTimeHandle);
    }
}

FVector ACoinSpawner::CheckForGround(const FVector _CoinPos)
{
    FVector rPos = _CoinPos;
    FHitResult hitresult(ForceInit);
    FCollisionQueryParams params;
    params.AddIgnoredActor(this);

    if(bDrawDebug)
        DrawDebugLine(GetWorld(), _CoinPos, _CoinPos + FVector(0.0f, 0.0f, -groundCheckDistance), FColor(255, 0, 0), true, 10000);

    GetWorld()->LineTraceSingleByChannel(hitresult, _CoinPos, _CoinPos + FVector(0.0f, 0.0f, -groundCheckDistance), ECollisionChannel::ECC_WorldStatic, params);

    if(hitresult.bBlockingHit)
    {
        rPos.Z = hitresult.ImpactPoint.Z + groundOffset;
    }

    return rPos;
}

FRotator ACoinSpawner::GetRandomDirection()
{
    FRotator rot(0.0f, 0.0f, 0.0f);

    if (randXDirection)
        rot.Roll = FMath::RandRange(0, 360);

    if (randYDirection)
        rot.Pitch = FMath::RandRange(0, 360);

    if (randZDirection)
        rot.Yaw = FMath::RandRange(0, 360);

    return rot;
}