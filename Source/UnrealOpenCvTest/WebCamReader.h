// A simple webcam reader using the OpenCV library
// Author: The UE4 community

#pragma once

#include "opencv2/core.hpp"
//#include "opencv2/highgui.hpp"    
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Engine/Texture2D.h"
#include "WebCamReader.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnOpenCVWebcamFrameReady, cv::Mat*);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnTextureInitialized, FVector2D, UTexture2D*);//Broadcast the textureSize and a pointer to the texture

UCLASS()
class AWebCamReader : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AWebCamReader();
   
    // Called every frame
    virtual void Tick(float DeltaSeconds) override;

    // The device ID opened by the Video Stream
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Webcam)
    int32 CameraID;

    // If the webcam images should be resized every frame
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Webcam)
    bool ShouldResize;

    // The targeted resize width and height (width, height)
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Webcam)
    FVector2D ResizeDeminsions;

    // The rate at which the color data array and video texture is updated (in frames per second)
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Webcam)
    float RefreshRate;

    // The refresh timer
    UPROPERTY(BlueprintReadWrite, Category = Webcam)
    float RefreshTimer;
    
    // OpenCV fields
    cv::Mat frame;
    cv::VideoCapture stream;
    cv::Size size;

    // OpenCV prototypes
    void UpdateFrame();
    void UpdateTexture();

    // If the stream has succesfully opened yet
    UPROPERTY(BlueprintReadOnly, Category = Webcam)
    bool isStreamOpen;

    // The videos width and height (width, height)
    UPROPERTY(BlueprintReadWrite, Category = Webcam)
    FVector2D VideoSize;

    // The current video frame's corresponding texture
    UPROPERTY(BlueprintReadOnly, Category = Webcam)
    UTexture2D* VideoTexture;

    // The current data array
    UPROPERTY(BlueprintReadOnly, Category = Webcam)
    TArray<FColor> Data;

    UFUNCTION(BlueprintCallable)
    void BeginCameraReading();

    FOnOpenCVWebcamFrameReady OnWebcamMatReady;
    FOnTextureInitialized OnTextureInitialized;
protected:

    // Use this function to update the texture rects you want to change:
    // NOTE: There is a method called UpdateTextureRegions in UTexture2D but it is compiled WITH_EDITOR and is not marked as ENGINE_API so it cannot be linked
    // from plugins.
    // FROM: https://wiki.unrealengine.com/Dynamic_Textures
    void UpdateTextureRegions(UTexture2D* Texture, int32 MipIndex, uint32 NumRegions, FUpdateTextureRegion2D* Regions, uint32 SrcPitch, uint32 SrcBpp, uint8* SrcData, bool bFreeData);

    // Pointer to update texture region 2D struct
    FUpdateTextureRegion2D* VideoUpdateTextureRegion;
};