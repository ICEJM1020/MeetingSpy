#pragma once

#include "FaceListener.h"

using namespace affdex;

class AFaceListener : public FaceListener
{
    void onFaceFound(float timestamp, FaceId faceId)
    {
        std::cout << "Face id " << faceId << " found at timestamp " << timestamp << std::endl;
    }
    void onFaceLost(float timestamp, FaceId faceId)
    {
        std::cout << "Face id " << faceId << " lost at timestamp " << timestamp << std::endl;
    }
};
