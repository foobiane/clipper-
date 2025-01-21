## clipper~: A simple mono clipper in PureData 
This project is still a work-in-progress. Expect bugs, malfunctions, and generally bad code.
*Created by Ian Doherty, January 2025*

A simple digital distortion module in PureData.

## Installation
1. If you haven't already, install PureData [here](https://puredata.info/).
2. Clone this repo using `git clone` on a command line or download the source code manually.
3. In the installation folder, run `make` on a Linux command line. For Windows users, consider using [MinGW](https://osdn.net/projects/mingw/) or [WSL](https://learn.microsoft.com/en-us/windows/wsl/install). For a system-wide installation, run `make install`.
4. Open clipper~-help.pd to learn the usage for clipper~. If `make install` was used, you will be able to add clipper~ objects into any PureData instance.
  * To view this in PureData, go to Help > Browser. clipper~ should be listed.

## Credits & Libraries Used
* [PureData](https://puredata.info/): Everything!
* [pure-data/pd-lib-builder](https://github.com/pure-data/pd-lib-builder): Makefile generation
* [pure-data/externals-howto](https://github.com/pure-data/externals-howto): Helpful guide used during the creation of this external
