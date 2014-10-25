/*
*  ImageProcessing.cpp
* package com.cabatuan.otsuthresholdnative;
*/
#include <jni.h>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

Mat * mOtsu = NULL;

extern "C"
jboolean
Java_com_cabatuan_otsuthresholdnative_CameraPreview_ImageProcessing(
		JNIEnv* env, jobject thiz,
		jint width, jint height,
		jbyteArray NV21FrameData, jintArray outPixels)
{
	jbyte * pNV21FrameData = env->GetByteArrayElements(NV21FrameData, 0);
	jint * poutPixels = env->GetIntArrayElements(outPixels, 0);

	if ( mOtsu == NULL )
    	{
    		mOtsu = new Mat(height, width, CV_8UC1);
    	}

	Mat mGray(height, width, CV_8UC1, (unsigned char *)pNV21FrameData);
	Mat mResult(height, width, CV_8UC4, (unsigned char *)poutPixels);
	Mat OtsuImg = *mOtsu;
    int thresh = 0;

	threshold( mGray, OtsuImg, thresh, 255, THRESH_BINARY | THRESH_OTSU );
	/// thresh = 0 is ignored

	cvtColor(OtsuImg, mResult, CV_GRAY2BGRA);

	env->ReleaseByteArrayElements(NV21FrameData, pNV21FrameData, 0);
	env->ReleaseIntArrayElements(outPixels, poutPixels, 0);
	return true;
}