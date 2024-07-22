#include <iostream>
#include <iterator>
#include <list>
#include <regex>
#include <string>
#include <vector>
#include <thread>
#include <memory>
#include "EDSDK.h"
#include "EDSDKTypes.h"
#include "FileControl.h"
#include "PreSetting.h"
#include "Property.h"
#include "CameraModel.h"
#include "utility.h"
#include "CameraEvent.h"

using namespace std::chrono_literals;

void EventLoop() {
	while(true) {
		EdsGetEvent();
		std::this_thread::sleep_for(200ms);
	}
}

int main()
{
	EdsError err = EDS_ERR_OK;
	EdsCameraListRef cameraList = NULL;
	EdsCameraRef camera;
	std::vector<CameraModel *> _detectedCameraArray;
	std::vector<CameraModel *> _openedCamerasArray;
	EdsUInt32 i = 0;
	EdsUInt32 count = 0;
	bool isSDKLoaded = false;
	std::smatch match_results;
	std::shared_ptr<std::thread> th = std::shared_ptr<std::thread>();

	err = EdsInitializeSDK();
	if (err == EDS_ERR_OK)
	{
		isSDKLoaded = true;
		std::this_thread::sleep_for(1000ms);
	}

	if (err == EDS_ERR_OK)
	{
		err = EdsGetCameraList(&cameraList);
	}

	if (err == EDS_ERR_OK)
	{
		err = EdsGetChildCount(cameraList, &count);
		if (count == 0)
		{
			std::cout << "Cannot detect any camera" << std::endl;
			pause_return();
			exit(EXIT_FAILURE);
		}
		else if (count > 30)
		{
			std::cout << "Too many cameras detected" << std::endl;
			pause_return();
			exit(EXIT_FAILURE);
		}
		std::cout << count << "cameras detected." << std::endl;
	}

	std::cout << "number\t"
						<< "Device Description" << std::endl;
	std::cout << "------+-------------------------" << std::endl;

	for (i = 0; i < count; i++)
	{
		if (err == EDS_ERR_OK)
		{
			err = EdsGetChildAtIndex(cameraList, i, &camera);
			EdsDeviceInfo deviceInfo;
			err = EdsGetDeviceInfo(camera, &deviceInfo);
			if (err == EDS_ERR_OK && camera == NULL)
			{
				std::cout << "Camera is not found." << std::endl;
				pause_return();
				exit(EXIT_FAILURE);
			}
			std::cout << "[" << i + 1 << "]\t" << deviceInfo.szDeviceDescription << std::endl;
			_detectedCameraArray.push_back(new CameraModel(camera, i + 1, kEdsSaveTo_Host)); // select direction : kEdsSaveTo_Camera / kEdsSaveTo_Host / kEdsSaveTo_Both
			_detectedCameraArray[i]->setModelName(deviceInfo.szDeviceDescription);
		}
	}

	for (i = 0; i < count; i++)
		_openedCamerasArray.push_back(_detectedCameraArray[i]);

	PreSetting(_detectedCameraArray);

	EdsUInt32 dat = 0;
	EdsSetCameraAddedHandler(handleCameraAdded, (EdsVoid *)dat);



	for (i = 0; i < _openedCamerasArray.size(); i++)
		_openedCamerasArray[i]->OpenSessionCommand();


	th = std::make_shared<std::thread>(EventLoop);
	while (true)
	{

		std::cout << "--------------------------------" << std::endl;
		std::cout << "> ";

		std::string control_number;

		std::cin >> control_number;
		std::cin.ignore();

		if (std::regex_search(control_number, match_results, std::regex("[0-9]")))
		{
			// Press halfway
			if (control_number == "4")
			{
				std::cout << "SHutter " << _openedCamerasArray.size() << std::endl;
				for (i = 0; i < _openedCamerasArray.size(); i++)
					_openedCamerasArray[i]->PressShutter(kEdsCameraCommand_ShutterButton_Halfway);
				clr_screen();
				continue;
			}
			// Press Completely
			else if (control_number == "5")
			{
				for (i = 0; i < _openedCamerasArray.size(); i++)
					_openedCamerasArray[i]->PressShutter(kEdsCameraCommand_ShutterButton_Completely);
				clr_screen();
				continue;
			}
			// Press Off
			else if (control_number == "6")
			{
				for (i = 0; i < _openedCamerasArray.size(); i++)
					_openedCamerasArray[i]->PressShutter(kEdsCameraCommand_ShutterButton_OFF);
				clr_screen();
				continue;
			}
			else
			{
				clr_screen();
				continue;
			}
		}
		// Return
		else if (std::regex_search(control_number, match_results, std::regex("r", std::regex_constants::icase)))
		{
			clr_screen();
			break;
		}
		else
		{
			clr_screen();
			continue;
		}

		EdsGetEvent();
		std::this_thread::sleep_for(200ms);
	}

	EdsUInt32 refcount = 0;
	bool berr = true;
	// Release camera list
	if (cameraList != NULL)
	{
		refcount = EdsRelease(cameraList);
	}

	// Release Camera

	for (i = 0; i < _openedCamerasArray.size(); i++)
	{
		if (_openedCamerasArray[i] != NULL)
		{
			berr = _openedCamerasArray[i]->CloseSessionCommand();
			refcount = EdsRelease(_openedCamerasArray[i]->getCameraObject());
			_openedCamerasArray[i] = NULL;
		}
	}
	// Remove elements before looping. Memory is automatically freed at the destructor of the vector when it leaves the scope.
	_openedCamerasArray.clear();
	clr_screen();

	// Termination of SDK
	if (isSDKLoaded)
	{
		EdsTerminateSDK();
	}

	return FALSE;
}