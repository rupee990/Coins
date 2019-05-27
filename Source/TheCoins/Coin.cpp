// Fill out your copyright notice in the Description page of Project Settings.

#include "Coin.h"
#include "Utilities.h"
#include "TheCoinsCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/PrimitiveComponent.h"
#include "ConstructorHelpers.h"

// Sets default values
ACoin::ACoin()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    //Setup the Collider
    collider = CreateDefaultSubobject<USphereComponent>(TEXT("RootCollider"));
    this->SetRootComponent(collider);
    collider->SetSphereRadius(64.0f);
    collider->SetCollisionProfileName(TEXT("BlockAll"));
    collider->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
    collider->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Ignore);
    collider->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Ignore);
    collider->OnComponentHit.AddDynamic(this, &ACoin::OnHit);
    collider->SetCanEverAffectNavigation(false);

    //Setup the Mesh with the default coin mesh
    static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("StaticMesh'/Game/Meshes/Coin.Coin'"));
    mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    mesh->SetupAttachment(collider);
    mesh->SetStaticMesh(MeshAsset.Object);
    mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    //Arrow showing the pickup direction
    arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("PickupDirection"));
    arrow->SetupAttachment(collider);
}

// Called when the game starts or when spawned
void ACoin::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ACoin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    //Make Coin Rotate
    mesh->AddLocalRotation(FRotator(0.0f, rotationRate, 0.0f));
}

void ACoin::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
    if (OtherActor->ActorHasTag("Player"))
    {
        //Get the Forward of the Arrow
        FVector collectDirection = -arrow->GetForwardVector();

        //Get direction of the player
        FVector dir = Util::GetDirection(OtherActor->GetActorLocation(), GetActorLocation());

        float pickUpValue = dir.DotProduct(collectDirection, dir);

        if (pickUpValue > directionAccuracy)
        {
            Cast<ATheCoinsCharacter>(OtherActor)->coins++;
            Destroy(this);
        }
    }
}

