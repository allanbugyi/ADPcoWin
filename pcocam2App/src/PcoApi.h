/*
 * PcoApi.h
 *
 * Revamped PCO area detector driver.
 *
 * An interface to the PCO API library and hardware
 *
 * Author:  Giles Knap
 *          Jonathan Thompson
 *
 */

#ifndef PCOAPI_H_
#define PCOAPI_H_

#include <string>
#include <epicsMessageQueue.h>
#include "DllApi.h"
#include <afxwin.h>
#include <windows.h>
#include <stdio.h>
#include <winsock2.h>
#include <epicsThread.h>
class Pco;
class TraceStream;

class PcoApi: public DllApi, public epicsThreadRunable
{
// Construction
public:
    PcoApi(Pco* pco, TraceStream* trace);
    virtual ~PcoApi();

// Overrides of DllApi
protected:
    virtual int doOpenCamera(Handle* handle, unsigned short camNum);
    virtual int doCloseCamera(Handle handle);
    virtual int doGetGeneral(Handle handle);
    virtual int doGetCameraType(Handle handle, unsigned short* camType);
    virtual int doGetSensorStruct(Handle handle);
    virtual int doGetCameraDescription(Handle handle, Description* description);
    virtual int doGetStorageStruct(Handle handle, unsigned long* ramSize, unsigned int* pageSize);
    virtual int doGetRecordingStruct(Handle handle);
    virtual int doResetSettingsToDefault(Handle handle);
    virtual int doGetTransferParameters(Handle handle, Transfer* transfer);
    virtual int doSetTransferParameters(Handle handle, Transfer* transfer);
    virtual int doGetSizes(Handle handle, Sizes* sizes);
    virtual int doSetDateTime(Handle handle, struct tm* currentTime);
    virtual int doGetTemperature(Handle handle, short* ccd, short* camera, short* psu);
    virtual int doSetPixelRate(Handle handle, unsigned long pixRate);
    virtual int doGetPixelRate(Handle handle, unsigned long* pixRate);
    virtual int doGetBitAlignment(Handle handle, unsigned short* bitAlignment);
    virtual int doSetBitAlignment(Handle handle, unsigned short bitAlignment);
    virtual int doGetCameraSetup(Handle handle, unsigned short* setupType,
            unsigned long* setupData, unsigned short* setupDataLen);
    virtual int doSetBinning(Handle handle, unsigned short binHorz, unsigned short binVert);
    virtual int doGetBinning(Handle handle, unsigned short* binHorz, unsigned short* binVert);
    virtual int doSetRoi(Handle handle, unsigned short x0, unsigned short y0,
            unsigned short x1, unsigned short y1);
    virtual int doGetRoi(Handle handle, unsigned short* x0, unsigned short* y0,
            unsigned short* x1, unsigned short* y1);
    virtual int doSetTriggerMode(Handle handle, unsigned short mode);
    virtual int doGetTriggerMode(Handle handle, unsigned short* mode);
    virtual int doSetStorageMode(Handle handle, unsigned short mode);
    virtual int doGetStorageMode(Handle handle, unsigned short* mode);
    virtual int doSetTimestampMode(Handle handle, unsigned short mode);
    virtual int doGetTimestampMode(Handle handle, unsigned short* mode);
    virtual int doSetAcquireMode(Handle handle, unsigned short mode);
    virtual int doGetAcquireMode(Handle handle, unsigned short* mode);
    virtual int doSetDelayExposureTime(Handle handle, unsigned long delay,
            unsigned long exposure, unsigned short timeBaseDelay,
            unsigned short timeBaseExposure);
    virtual int doGetDelayExposureTime(Handle handle, unsigned long* delay,
            unsigned long* exposure, unsigned short* timeBaseDelay,
            unsigned short* timeBaseExposure);
    virtual int doSetConversionFactor(Handle handle, unsigned short factor);
    virtual int doSetAdcOperation(Handle handle, unsigned short mode);
    virtual int doGetAdcOperation(Handle handle, unsigned short* mode);
    virtual int doGetRecordingState(Handle handle, unsigned short* state);
    virtual int doSetRecordingState(Handle handle, unsigned short state);
    virtual int doGetRecorderSubmode(Handle handle, unsigned short* mode);
    virtual int doAllocateBuffer(Handle handle, short* bufferNumber, unsigned long size,
            unsigned short** buffer, Handle* event);
    virtual int doCancelImages(Handle handle);
    virtual int doCamlinkSetImageParameters(Handle handle, unsigned short xRes, unsigned short yRes);
    virtual int doArm(Handle handle);
    virtual int doAddBufferEx(Handle handle, unsigned long firstImage, unsigned long lastImage,
        short bufferNumber, unsigned short xRes, unsigned short yRes, unsigned short bitRes);
    virtual int doGetBufferStatus(Handle handle, short bufferNumber, unsigned long* statusDll,
        unsigned long* statusDrv);
    virtual int doForceTrigger(Handle handle, unsigned short* triggered);
    virtual int doFreeBuffer(Handle handle, short bufferNumber);
    virtual int doGetActiveRamSegment(Handle handle, unsigned short* segment);
    virtual int doGetNumberOfImagesInSegment(Handle handle, unsigned short segment,
            unsigned long* validImageCount, unsigned long* maxImageCount);

// Overrides of epicsThreadRunable
public:
    virtual void run();

// Constants
protected:
    enum {numberOfRunningEvents = DllApi::maxNumBuffers+1};
    enum {numberOfWaitingEvents = 1};
    enum {stopEventIndex=0, firstBufferEventIndex=1};


// Members
protected:
    epicsThread thread;
    struct
    {
        bool addedToDll;
        Handle eventHandle;
    } buffers[DllApi::maxNumBuffers];
    Handle stopEvent;
    Handle startEvent;
    int queueHead;
    int queueTail;
    bool buffersValid;

// Functions
protected:
};

#endif /* PCOAPI_H_ */
