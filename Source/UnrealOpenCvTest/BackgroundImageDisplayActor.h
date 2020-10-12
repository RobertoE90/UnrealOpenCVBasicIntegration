// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WebCamReader.h"

#include "BackgroundImageDisplayActor.generated.h"


UCLASS()
class UNREALOPENCVTEST_API ABackgroundImageDisplayActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABackgroundImageDisplayActor();

	UFUNCTION(BlueprintCallable)
	void Initialize(AWebCamReader* WebCamReader);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	UMaterialInstanceDynamic* RenderTextureDynamicInstanceMaterial;

	UFUNCTION()
	void OnDisplayTextureInitialized(FVector2D Size, UTexture2D* Texture);
};
