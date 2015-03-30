//osg osgearth 
#include <osg/ShapeDrawable>
#include <osg/Notify>
#include <osgGA/GUIEventHandler>
#include <osgGA/StateSetManipulator>
#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>

#include <osgEarth/MapNode>
#include <osgEarthUtil/ExampleResources>
#include <osgEarthUtil/EarthManipulator>
#include <osgEarthUtil/AutoClipPlaneHandler>
#include <osgEarthUtil/LogarithmicDepthBuffer>
#include <osgEarthUtil/VerticalScale>

#include <osgEarthDrivers/tms/TMSOptions>
#include <osgEarthDrivers/xyz/XYZOptions>
#include <osgEarthDrivers/feature_ogr/OGRFeatureOptions>
#include <osgEarthDrivers/model_feature_geom/FeatureGeomModelOptions>
#include <osgEarthDrivers/gdal/GDALOptions>

#include <osgEarthAnnotation/PlaceNode>
#include <osgEarthUtil/EarthManipulator>
#include <osgEarthUtil/AnnotationEvents>
#include <osgEarthUtil/AutoClipPlaneHandler>
#include <osgEarthUtil/ObjectLocator>
#include <osgEarthUtil/EarthManipulator>
#include <osgEarthUtil/Controls>
#include <osgEarthUtil/LatLongFormatter>
#include <osgEarth/ElevationQuery>
#include <osgEarth/StringUtils>

#include <osgEarthAnnotation/FeatureNode>

#include <osgModeling/Curve>
#include <osgModeling/Loft>

using namespace osgEarth;
using namespace osgUtil;
using namespace osgEarth::Util;
using namespace osgEarth::Util::Controls;
using namespace osgEarth::Features;
using namespace osgEarth::Annotation;