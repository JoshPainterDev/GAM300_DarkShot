// Fill out your copyright notice in the Description page of Project Settings.

#include "DarkShotVR.h"
#include "VR_PlayerChaperone.h"

#define MAXGRABDISTANCE 20
#define TENSIONSCALE 20
#define MAXTENSION	50

// Sets default values
AVR_PlayerChaperone::AVR_PlayerChaperone()
{
	// Setup Capsule Component

	// End of Capsule Component Setup
	//GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	//GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Ignore);
	// Create and Setup Dummy Scene Components
	//SteamVRChaperoneScene = CreateDefaultSubobject<USceneComponent>(TEXT("SteamVRChaperoneScene"));
	L_MotionControllerScene = CreateDefaultSubobject<USceneComponent>(TEXT("L_MotionControllerScene"));
	L_MotionControllerScene->SetupAttachment(RootComponent);
	R_MotionControllerScene = CreateDefaultSubobject<USceneComponent>(TEXT("R_MotionControllerScene"));
	R_MotionControllerScene->SetupAttachment(RootComponent);
	// End of Dummy Scene Creation

	// Create VR Chaperone
	SteamVRChaperone = CreateDefaultSubobject<USteamVRChaperoneComponent>(TEXT("SteamVRChaperone"));
	// End of VR Chaperone Creation

	// Create First Person Camera
	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCamera->RelativeLocation = FVector(0, 0, 0);
	// End of First Person Camera Creation

	// Create VR Controllers
	R_MotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("R_MotionController"));
	R_MotionController->Hand = EControllerHand::Right;
	R_MotionController->SetupAttachment(R_MotionControllerScene);
	L_MotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("L_MotionController"));
	L_MotionController->Hand = EControllerHand::Left;
	L_MotionController->SetupAttachment(L_MotionControllerScene);
	// End of VR Controller Creation

	// Create and Setup Static Mesh (VR_RightHand) For R_MotionController
	VR_RightHand = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VR_RightHand"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("StaticMesh'/Game/BasicModelShapes/sphere.sphere'"));
	VR_RightHand->SetStaticMesh(SphereVisualAsset.Object);
	VR_RightHand->SetupAttachment(R_MotionControllerScene);
	// End of Mesh Setup

	// Create and Setup Skeletal Mesh(VR_Bow) For L_MotionController
	VR_Bow = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("VR_Bow"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> BowVisualAsset(TEXT("SkeletalMesh'/Game/Bow/PlayerBow.PlayerBow'"));
	VR_Bow->SetSkeletalMesh(BowVisualAsset.Object);
	VR_Bow->SetWorldScale3D(FVector(0.5, 0.5, 0.5));
	VR_Bow->SetupAttachment(L_MotionControllerScene);
	VR_Bow->SetRelativeRotation(FRotator(90, 180, -180));
	const ConstructorHelpers::FObjectFinder<UAnimBlueprint> AnimObj(TEXT("AnimBlueprint'/Game/Bow/ABP_Bow.ABP_Bow'"));
	VR_Bow->SetAnimInstanceClass(AnimObj.Object->GeneratedClass);
	// End of Mesh Setups

	_arrowManager = CreateDefaultSubobject<UArrowManager>(TEXT("ArrowManager"));

	_triggerPressed = false;
}

// Called when the game starts or when spawned
void AVR_PlayerChaperone::BeginPlay()
{
	// tells the packaged build to use a head mounted display
	GetWorld()->Exec(GetWorld(), TEXT("stereo on"));
	Super::BeginPlay();
}

void AVR_PlayerChaperone::UpdateChaperone()
{
	// Get the Chaperone Location and Rotation if there is an active controller
	if (USteamVRFunctionLibrary::GetTrackedDevicePositionAndOrientation(0, _vive.Chaperone_Location, _vive.Chaperone_Rotation))
	{
		// Update both the camera and the base actor location and orientation
		SetActorLocationAndRotation(_vive.Chaperone_Location, _vive.Chaperone_Rotation);
		FirstPersonCamera->SetRelativeLocationAndRotation(_vive.Chaperone_Location, _vive.Chaperone_Rotation);
	}
}

void AVR_PlayerChaperone::UpdateLeftMotionController()
{
	// Get the Left Controller's Locationg and Rotation if there is an active controller
	if (USteamVRFunctionLibrary::GetHandPositionAndOrientation(0, EControllerHand::Left, _vive.Left_Location, _vive.Left_Rotation))
	{
		// Set the dummy scene component of the left motion controller
		L_MotionControllerScene->SetWorldLocationAndRotation(_vive.Left_Location, _vive.Left_Rotation);
	}
}

void AVR_PlayerChaperone::UpdateRightMotionController()
{
	// Get the Right Controller's Locationg and Rotation if there is an active controller
	if (USteamVRFunctionLibrary::GetHandPositionAndOrientation(0, EControllerHand::Right, _vive.Right_Location, _vive.Right_Rotation))
	{
		// Set the dummy scene component of the right motion controller
		R_MotionControllerScene->SetWorldLocationAndRotation(_vive.Right_Location, _vive.Right_Rotation);
	}
}
void AVR_PlayerChaperone::GrabArrow()
{
}
void AVR_PlayerChaperone::ShootArrow()
{
		if (_arrowManager->_isArrowAttachedToBow == true)
			_arrowManager->ShootArrow();
}
void AVR_PlayerChaperone::SpawnArrow()
{
	if (_arrowManager->_isArrowAttachedToBow == false && _arrowManager->_isArrowAttachedToHand == false)
		if (DistanceBetweenRHandAndHMD() < MAXGRABDISTANCE)
		{
			_arrowManager->SpawnAndAttachArrow(R_MotionControllerScene);
		}
}

void AVR_PlayerChaperone::ToggleEquipment()
{
	_arrowManager->ToggleEquipment(L_MotionControllerScene);
}
void AVR_PlayerChaperone::SpawnAndAttachArrowToRightHand()
{
}
void AVR_PlayerChaperone::UpdateTension(float DeltaTime)
{
	float c = DeltaTime;
	++c;
	if (_arrowManager->_isArrowAttachedToBow == true)
		_arrowManager->_bowTension = FMath::Clamp(FMath::Abs( DistanceBetweenHands() - 20.0), 0.0, 50.0);

	// TODO: keep track of how long we are at max tension
}
float AVR_PlayerChaperone::DistanceBetweenHands()
{
	FVector length = _vive.Left_Location - _vive.Right_Location;
	float distance = length.Size();;
	return distance;
}

float AVR_PlayerChaperone::DistanceBetweenRHandAndHMD()
{
	FVector location = _vive.Chaperone_Location;
	location.Z -= 10;
	FVector dir = _vive.Chaperone_Rotation.Vector();
	FVector length = location - _vive.Right_Location - 30 * dir;
	float distance = length.Size();
	/*for (auto i = 0; i < 20; i++)
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::White, FString::SanitizeFloat(distance));*/
	return distance;
}
void AVR_PlayerChaperone::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
}

bool AVR_PlayerChaperone::AttachToBowOrNot()
{
	float distance = 0;
	if (_arrowManager->_isArrowAttachedToHand)
	{
		if (DistanceBetweenHands() <= MAXGRABDISTANCE)
		{
			_arrowManager->_isArrowAttachedToBow = true;
			_arrowManager->_isArrowAttachedToHand = false;
			return true;
		}

	}
	return false;
}
// Called every frame
void AVR_PlayerChaperone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// update the chaperone position
	UpdateChaperone();
	// update L_MotionController position
	UpdateLeftMotionController();
	// update R_MotionController position
	UpdateRightMotionController();

	UpdateTension(DeltaTime);
	
	if (_arrowManager->_isArrowAttachedToHand && _triggerPressed)
		AttachArrow();

	if (_arrowManager->_isArrowAttachedToBow)
		_arrowManager->UpdateArrowPos();
	// On Trigger IE_Pressed
	// get distance between hands
	// if appropriate value
	// attach the arrow to the bow

	// On Trigger IE_Released
	// if arrow is attached to bow
	// shoot the arrow

}

void AVR_PlayerChaperone::TriggerPressed()
{
	_triggerPressed = true;
	SpawnArrow();
}

void AVR_PlayerChaperone::TriggerReleased()
{
	_triggerPressed = false;
	ShootArrow();
}

void AVR_PlayerChaperone::AttachArrow()
{
	if (DistanceBetweenHands() < 20)
		_arrowManager->AttachToBow(L_MotionControllerScene, 1u);
}

// Called to bind functionality to input
void AVR_PlayerChaperone::SetupPlayerInputComponent(UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
	InputComponent->BindAction("GrabArrow", IE_Pressed, this, &AVR_PlayerChaperone::TriggerPressed);
	InputComponent->BindAction("GrabArrow", IE_Released, this, &AVR_PlayerChaperone::TriggerReleased);
	InputComponent->BindAction("ToggleEquipment", IE_Pressed, this, &AVR_PlayerChaperone::ToggleEquipment);
}

