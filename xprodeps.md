# libgeotiff dependencies

|project|license [^_l]|description [dependencies]|version|source|diff [^_d]|
|-------|-------------|--------------------------|-------|------|----------|
|<a id='libgeotiff' />[libgeotiff](http://trac.osgeo.org/geotiff/ 'GeoTIFF trac website')|[MIT](https://github.com/OSGeo/libgeotiff/blob/master/libgeotiff/LICENSE 'MIT License or public domain')|georeferencing info embedded within TIFF file [deps: _wxWidgets_]| |[upstream](https://github.com/OSGeo/libgeotiff 'github.com/OSGeo/libgeotiff')|  [intro]|
|<a id='wxWidgets' />[wxWidgets](http://wxwidgets.org/)|[wxWindows](https://wxwidgets.org/about/licence/ 'essentially LGPL with an exception')|Cross-Platform C++ GUI Library [pvt deps: _OpenGL_]|[xpv3.1.0.9](https://github.com/externpro/wxWidgets/releases/tag/xpv3.1.0.9 'release')|[repo](https://github.com/externpro/wxWidgets 'github.com/externpro/wxWidgets') [upstream](https://github.com/wxWidgets/wxWidgets 'github.com/wxWidgets/wxWidgets')|[diff](https://github.com/externpro/wxWidgets/compare/v3.1.0...xpv3.1.0.9 'github.com/externpro/wxWidgets/compare/v3.1.0...xpv3.1.0.9') [intro[msw], native[unix]]|
|<a id='OpenGL' />[OpenGL](https://cmake.org/cmake/help/latest/module/FindOpenGL.html)|[SGI-OpenGL](https://spdx.org/licenses/SGI-OpenGL.html 'SGI OpenGL License')|Finds the OpenGL and OpenGL Utility Library (GLU)|[xpv1.0.1](https://github.com/externpro/OpenGL/releases/tag/xpv1.0.1 'release')|[repo](https://github.com/externpro/OpenGL 'github.com/externpro/OpenGL')|[diff](https://github.com/externpro/OpenGL/compare/v0...xpv1.0.1 'github.com/externpro/OpenGL/compare/v0...xpv1.0.1') [bin]|

![deps](xprodeps.svg 'dependencies')

Dependency version check: all 2 parent-manifest versions match pinned versions.

|diff  |description|
|------|-----------|
|patch |diff modifies/patches existing cmake|
|intro |diff introduces cmake|
|auto  |diff adds cmake to replace autotools/configure/make|
|native|diff adds cmake but uses existing build system|
|bin   |diff adds cmake to repackage binaries built elsewhere|
|fetch |diff adds cmake and utilizes FetchContent|

[^_l]: see [SPDX License List](https://spdx.org/licenses/ '') for a list of commonly found licenses
[^_d]: see table above with description of diff
