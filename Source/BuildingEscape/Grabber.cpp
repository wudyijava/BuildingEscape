// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "Grabber.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	inputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	//�����������Ӧ�¼��Ļص�����
	if (inputComponent)
	{
		inputComponent->BindAction("Grab", IE_Pressed,
			this, &UGrabber::OnPressed);
		inputComponent->BindAction("Grab", IE_Released,
			this, &UGrabber::OnReleased);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing input component."), *GetOwner()->GetName());
	}

	physicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (physicsHandle == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing input component."), *GetOwner()->GetName());
	}
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (physicsHandle->GetGrabbedComponent())
	{
		//���±�ץȡ�����λ��
		physicsHandle->SetTargetLocation(GetReachLineEnd());
	}
}

void UGrabber::OnPressed()
{
	auto hitResult = GetFirstPhysicsBodyInReach();
	auto hitActor = hitResult.GetActor();
	if (hitActor)
	{
		auto componentToGrab = hitResult.GetComponent();
		//ץȡ����
		physicsHandle->GrabComponent(componentToGrab, NAME_None,
			componentToGrab->GetOwner()->GetActorLocation(), true);
	}
}

void UGrabber::OnReleased()
{
	physicsHandle->ReleaseComponent();
}

//�������߶�ָ��������������̽�⣬���̽�⵽ָ�����������򷵻ؽ��
const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	//���߼��
	FCollisionQueryParams traceParameter =
		FCollisionQueryParams(TEXT(""), false, GetOwner());
	FHitResult hitResult;
	GetWorld()->LineTraceSingleByObjectType(
		hitResult,							//�����
		GetReachLineStart(),				//�������
		GetReachLineEnd(),					//�����յ�
		ECollisionChannel::ECC_PhysicsBody,	//��������
		traceParameter						//����׷�ٲ���
	);

	return hitResult;
}

FVector UGrabber::GetReachLineStart()
{
	// ��ȡ�ӵ���Ϣ
	FVector playerViewPointLocation;
	FRotator playerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		playerViewPointLocation, playerViewPointRotation);
	return playerViewPointLocation;
}

FVector UGrabber::GetReachLineEnd() {
	FVector playerViewPointLocation;
	FRotator playerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		playerViewPointLocation, playerViewPointRotation);
	//������ǰ����һ��ʸ������
	return playerViewPointLocation + playerViewPointRotation.Vector() * reach;
}