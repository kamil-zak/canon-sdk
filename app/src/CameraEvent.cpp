#include <iostream>
#include <string>
#include <vector>
#include "EDSDK.h"
#include "EDSDKTypes.h"

EdsError downloadImage(EdsDirectoryItemRef directoryItem, EdsVoid *context);

EdsError EDSCALLBACK handleObjectEvent(EdsObjectEvent event, EdsBaseRef object, EdsVoid *context)
{
	EdsError err = EDS_ERR_OK;
	// std::cout << "ObjectEvent" << std::hex << event << std::endl;
	switch (event)
	{
	case kEdsObjectEvent_DirItemRequestTransfer:
		std::cout << "object event is caught." << std::endl;
		downloadImage(object, context);
		break;
	default:
		break;
	}
	// Object must be released if(object)
	{
		EdsRelease(object);
	}
	//_syncObject->unlock();
	return err;
}

EdsError EDSCALLBACK handlePropertyEvent(
	EdsUInt32 inEvent,
	EdsUInt32 inPropertyID,
	EdsUInt32 inParam,
	EdsVoid *inContext)
{
	// std::cout << "PropertyEvent" << std::hex << inEvent << std::endl;
	EdsError err = EDS_ERR_OK;
	// do something
	return err;
}

EdsError EDSCALLBACK handleSateEvent(EdsStateEvent event, EdsUInt32 parameter, EdsVoid *context)
{
	// std::cout << "StateEvent" << std::hex << event << std::endl;
	EdsError err = EDS_ERR_OK;
	// do something
	return err;
}


EdsError  EDSCALLBACK handleCameraAdded(EdsVoid *inContext ) {
	// std::cout << "CameraAdded" << std::endl;
	return EDS_ERR_OK;
};