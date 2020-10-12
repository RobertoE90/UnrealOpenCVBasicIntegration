
#include "FaceDetectionActor.h"

// Sets default values
AFaceDetectionActor::AFaceDetectionActor()
{	
	PrimaryActorTick.bCanEverTick = false;

	FString ProjectPath = FPaths::ProjectDir();
	FString ModelPath = ProjectPath.Append("Source/Models/haarcascade_frontalface_default.xml");

	std::string CString = std::string(TCHAR_TO_UTF8(*ModelPath));
	cv::String ClassifierFilePath = CString;

	bModelLoaded = FaceDetector.load(ClassifierFilePath);
}

void AFaceDetectionActor::Initialize(AWebCamReader *WebCameraReader)
{
	WebCameraReader->OnWebcamMatReady.AddUObject(this, &AFaceDetectionActor::OnOpenCVFrameUpdated);
	cv::String cad = cv::getBuildInformation();
	FString Cad = UTF8_TO_TCHAR(cad.c_str());
}

void AFaceDetectionActor::OnOpenCVFrameUpdated(cv::Mat* Frame)
{
	if (!bModelLoaded)
		return;

	Faces = new std::vector<cv::Rect>;
	FaceDetector.detectMultiScale(*Frame, *Faces);
	
	UE_LOG(LogTemp, Warning, TEXT("Amount of faces %d"), Faces->size());
}
