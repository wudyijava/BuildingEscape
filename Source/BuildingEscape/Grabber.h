// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	float reach = 100.0f;	//射线延伸比例
	UInputComponent* inputComponent = nullptr;	//输入组件
	UPhysicsHandleComponent* physicsHandle = nullptr;	//物理处理组件

	void OnPressed();
	void OnReleased();

	//获取射线检测到的符合要求的物体
	const FHitResult GetFirstPhysicsBodyInReach();

	//获取射线的起止端点坐标
	FVector GetReachLineStart();
	FVector GetReachLineEnd();
};
