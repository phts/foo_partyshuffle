# Party Shuffle

A component for [foobar2000](http://www.foobar2000.org/) player.
Adds a Party Shuffle mode, a similar feature like iTunes or Android Music Player have.

## Usage

There is a menu item *Playback* → *Party Shuffle* which turns on/off the feature.

If this feature is turned on then random tracks will be added to the current playlist when the last track has just finished playing so the next track will continue playing.

If *Stop after current* is on in this case then only new tracks will be added and a playback will be stopped.

## Development

### Preparing Visual Studio

1. Upgrade VirtualBox to [the latest version (5.20)](https://www.virtualbox.org/wiki/Downloads)

2. Download [VM with Windows 7](https://developer.microsoft.com/en-us/microsoft-edge/tools/vms/) and run in VirtualBox.

3. Install [Visual Studio Community 2017](https://www.visualstudio.com/thank-you-downloading-visual-studio/?sku=Community&rel=15).

4. Select _Desktop development with C++_ and ensure these components are selected:

    - Platform Toolset v141
    - Windows 10 SDK
    - Visual C++ MFC for x86 and x64
    - Visual C++ ATL for x86 and x64
    - Windows XP support for C++

### Preparing project

1. Download [foobar2000 SDK 2018-03-06](https://www.foobar2000.org/SDK) and unzip file.

2. Clone [foo_partyshuffle](https://github.com/phts/foo_partyshuffle) repo into `<sdk root>/foobar2000` folder.

3. Download [WTL for VS2017](https://github.com/allenk/WTL-Wizard-VS2017) and unzip.

4. Open `foo_partyshuffle.sln` and add `WTL/Include` folder into _Include Directories_ for `foo_partyshuffle` and `foobar2000_ATL_helpers` projects: mouse right button on the project → Properties → VC++ Directories → Include Directories.

5. Update project's SDK version to actual: mouse right button on _foo\_partyshuffle_ project → Properties → General → Windows SDK Version.

## Useful links

* [Download Visual Studio 2017 Web Installer](https://developerinsider.co/download-visual-studio-2017-web-installer-iso-community-professional-enterprise/)
* [Mismatch Detected for 'RuntimeLibrary'](https://stackoverflow.com/questions/14714877/mismatch-detected-for-runtimelibrary)
