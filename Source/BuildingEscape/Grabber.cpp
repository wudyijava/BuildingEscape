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
	//绑定输入隐射对应事件的回调方法
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
		//更新被抓取物体的位置
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
		//抓取物体
		physicsHandle->GrabComponent(componentToGrab, NAME_None,
			componentToGrab->GetOwner()->GetActorLocation(), true);
	}
}

void UGrabber::OnReleased()
{
	physicsHandle->ReleaseComponent();
}

//产生射线对指定距离的物体进行探测，如果探测到指定类型物体则返回结果
const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	//射线检测
	FCollisionQueryParams traceParameter =
		FCollisionQueryParams(TEXT(""), false, GetOwner());
	FHitResult hitResult;
	GetWorld()->LineTraceSingleByObjectType(
		hitResult,							//检测结果
		GetReachLineStart(),				//射线起点
		GetReachLineEnd(),					//射线终点
		ECollisionChannel::ECC_PhysicsBody,	//过滤类型
		traceParameter						//附加追踪参数
	);

	return hitResult;
}

FVector UGrabber::GetReachLineStart()
{
	// 获取视点信息
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
	//增加正前方的一个矢量倍数
	return playerViewPointLocation + playerViewPointRotation.Vector() * reach;
}