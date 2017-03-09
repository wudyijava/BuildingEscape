// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "Grabber.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	inputComponent = 
		GetOwner()->FindComponentByClass<UInputComponent>();
	if (inputComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Input component found."));
		inputComponent->BindAction("Grab", IE_Pressed,
			this, &UGrabber::OnPressed);
		inputComponent->BindAction("Grab", IE_Released,
			this, &UGrabber::OnReleased);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing input component."));
	}
} 


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// 获取视点信息
	FVector playerViewPointLocation;
	FRotator playerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		playerViewPointLocation, playerViewPointRotation);

	//绘制射线轨迹
	FVector lineTraceEnd = playerViewPointLocation + playerViewPointRotation.Vector() * reach;
	DrawDebugLine(
		GetWorld(),
		playerViewPointLocation,
		lineTraceEnd,
		FColor::Red,
		false,
		0.0f,
		0.0f,
		10.0f
	);

	//射线检测
	FCollisionQueryParams traceParameter = 
		FCollisionQueryParams(TEXT(""), false, GetOwner());
	FHitResult hit;
	GetWorld()->LineTraceSingleByObjectType(hit, playerViewPointLocation,
		lineTraceEnd, ECollisionChannel::ECC_PhysicsBody, traceParameter);

	//test
	AActor* hitActor = hit.GetActor();
	if (hitActor)
	{
		UE_LOG(LogTemp, Warning,
			TEXT("hit actor's name is %s."), *(hitActor->GetName()));
	}
}

void UGrabber::OnPressed()
{
	UE_LOG(LogTemp, Warning, TEXT("grab pressed."));
}

void UGrabber::OnReleased()
{
	UE_LOG(LogTemp, Warning, TEXT("grab released."));
}

