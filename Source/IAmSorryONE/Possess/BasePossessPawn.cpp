// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePossessPawn.h"

// Sets default values
ABasePossessPawn::ABasePossessPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set this pawn to be controlled by the lowest-numbered player
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	//Init Mesh
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("StaticMesh'/Engine/EditorMeshes/EditorSphere.EditorSphere'"));
	mesh->SetStaticMesh(MeshAsset.Object);
	mesh->SetWorldScale3D(FVector(0.5, 0.5, 0.5));
	mesh->SetSimulatePhysics(true);

	//Init Camera
	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));
	camera->SetRelativeLocation(RelativeToBall);
	camera->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
	camera->AttachTo(mesh);
	camera->SetFieldOfView(120);
	camera->SetAbsolute(false, true, false);

	//Init Collision
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collusion"));
	SphereCollision->InitSphereRadius(400.f);
	SphereCollision->AttachTo(mesh);
}

// Called when the game starts or when spawned
void ABasePossessPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABasePossessPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ABasePossessPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Respond when our "Possess" key is pressed or released.
	InputComponent->BindAction("Possess", IE_Pressed, this, &ABasePossessPawn::Possess);

	// Respond every frame to the values of our two movement axes, "MoveX" and "MoveY".
	InputComponent->BindAxis("MoveX", this, &ABasePossessPawn::Move_XAxis);
	InputComponent->BindAxis("MoveY", this, &ABasePossessPawn::Move_YAxis);
}



void ABasePossessPawn::Move_XAxis(float AxisValue)
{
	mesh->AddForce(FVector(1, 0, 0) * AxisValue * 100000.0f);
	camera->SetWorldLocation(mesh->GetComponentTransform().GetLocation() + RelativeToBall);
}

void ABasePossessPawn::Move_YAxis(float AxisValue)
{
	mesh->AddForce(FVector(0,1,0) * AxisValue* 100000.0f);
	camera->SetWorldLocation(mesh->GetComponentTransform().GetLocation() + RelativeToBall);
}

void ABasePossessPawn::Possess()
{
	UE_LOG(LogTemp, Warning, TEXT("Possed"));
	TArray<AActor*> pawnys;
	GetOverlappingActors(pawnys, APawn::StaticClass());
	if (pawnys.Num() != 0)
	{
		APawn* pawny = Cast<APawn>(pawnys[0]);
		Controller->Possess(pawny);
	}
}

