// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WebCamReader.h"
//#include "opencv2/core.hpp"
#include "opencv2/objdetect.hpp"

#include "FaceDetectionActor.generated.h"

UCLASS()
class UNREALOPENCVTEST_API AFaceDetectionActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFaceDetectionActor();

	UFUNCTION(BlueprintCallable)
	void Initialize(AWebCamReader *WebCameraReader);

	void OnOpenCVFrameUpdated(cv::Mat* frame);

private:
	cv::CascadeClassifier FaceDetector;
	bool bModelLoaded = false;

	std::vector<cv::Rect>* Faces = nullptr;
};
