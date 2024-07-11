---
# How to build

sudo apt install cmake build-essential

./build.sh
---

# How to use the sample app

1.Connect the camera to your PC with a USB cable.

2.Run MultiCamCui.exe.
The top menu lists the detected cameras.

3.Select the camera you want to connect.
ex.

- Select camera No.2 to No.5
  Enter "2-5"

- Select camera No.3
  Enter "3"

- Select all listed cameras
  Enter "a"

- Quit the app
  Enter "x"

* The camera number changes in the order you connect the camera to your PC.

  4.Control menu
  The control menu is the following:
  [ 1] Set Save To
  [ 2] Set Image Quality
  [ 3] Take Picture and download
  [ 4] Press Halfway
  [ 5] Press Completely
  [ 6] Press Off
  [ 7] TV
  [ 8] AV
  [ 9] ISO
  [10] White Balance
  [11] Drive Mode
  [12] Exposure Compensation
  [13] AE Mode (read only)
  [14] AF Mode (read only)
  [15] Aspect setting (read only)
  [16] Get Available shots (read only)
  [17] Get Battery Level (read only)
  [18] Edit Copyright
  [20] Get Live View Image
  [30] All File Download
  [31] Format Volume
  [32] Set Meta Data(EXIF) to All Image files
  [33] Set Meta Data(XMP) to All Image files

Select the item number you want to control.
The following is a description of the operation for each input number.
\*Enter "r" key to move to "Top Menu"

    	[ 1] Set Save To
    Set the destination for saving images.

    	[ 2] Set Image Quality
    Set the image Quality.

    	[ 3] Take Picture and download
    Press and release the shutter button without AF action,
    create a "cam + number" folder in the folder where MultiCamCui.exe is located
    and save the pictures taken with each camera.

    * If you can't shoot, change the mode dial to "M" and then try again.
    * The camera number changes in the order you connect the camera to your PC.

    	[ 4] Press Halfway
    Press the shutter button halfway.

    	[ 5] Press Completely
    Press the shutter button completely.
    When Drive mode is set to continuous shooting,
    Continuous shooting is performed.

    	[ 6] Press Off
    Release the shutter button.

    	[ 7] TV
    Set the Tv settings.

    	[ 8] AV
    Set the Av settings.

    	[ 9] ISO
    Set the ISO settings.

    	[10] White Balance
    Set the White Balance settings.

    	[11] Drive Mode
    Set the Drive mode settings.

    	[12] Exposure Compensation
    Set the exposure compensation settings.

    	[13] AE Mode (read only)
    Indicates the AE mode settings. (not configurable)

    	[14] AF Mode (read only)
    Indicates the AF mode settings. (not configurable)

      [15] Aspect setting (read only)
    Indicates the aspect settings. (not configurable)

      [16] Get Available shots (read only)
    Indicates the number of shots available on a camera. (not configurable)

      [17] Get Battery Level (read only)
    Indicates the camera battery level. (not configurable)

      [18] Edit Copyright
    Indicates/Set a string identifying the copyright information on the camera.

    	[20] Get Live View Image
    Get one live view image.
    In the folder where MultiCamCui.exe is located
    Automatically create a "cam number" folder and save each camera's image.

    	[30] All File Download
    Download all picture File in the camera's card to PC.
    In the folder where MultiCamCui.exe is located
    automatically create a "cam number" folder and save each camera's image.

    	[31] Format Volume
    Formats volumes of memory cards in a camera.

    [32] Set Meta Data(EXIF) to All Image files
    Writes information from "resources/gpsexifdata.txt"to the metadata of an image (Jpeg only) in the camera.

    	[33] Set Meta Data(XMP) to All Image files
    Writes information from "resources/metadata_xmp.txt"to the metadata of an image (Jpeg only) in the camera.

- Some settings may not be available depending on the mode dial of the camera.
  If you can't set, change the mode dial to "M" and then try again.
