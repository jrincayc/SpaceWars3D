

#ifndef __UTILITY__
#define __UTILITY__

#include <string>
#include "Vector3D.h"
#include <xercesc/dom/DOM.hpp>
#include "GLHeaders.h"

using namespace std;
using namespace xercesc;

/*!
 @function strInsensitiveCompare
 @abstract Compares two strings with out regard to the case
 @param str1 The string to compare to
 @param str2 The string to compare with
 @result 0 if equal, -1 if str1 < str2, 1 if str1 > str2
 */
int strInsensitiveCompare(string str1, string str2);

/*!
 @function pathHasExtension
 @abstract Checks to see if the path has an extension. The compare is case insensitive.
 @param path The path of the file
 @param extension The extension to check for
 @result true if the path has the extension, false otherwise
 */
bool pathHasExtension(const string &path, const string &extension);

/*!
 @function vectorFromXML
 @abstract Takes an XMLNode that contains a vector, and constructs a vector out of it
 @param The XMLNode containing a vector
 @result The vector
 */
Vector3D vectorFromXML(DOMElement* node);

/*!
 @function xmlToFloat
 @abstract Takes a XMLCh string and converts it to a float
 @param The XMLCh string
 @result The value of the string as a float
 */
float xmlToFloat(const XMLCh *string);

/*!
 @function drawSphere
 @abstract draws a sphere with opengl
 @param radius The radius of the sphere
 @param pres The precession of the sphere
 */
void drawSphere(float radius, int pres);

/*!
 @function colorFromXML
 @abstract Converts a xml element to a color
 @param node The XML DOMElement
 @param color The color array to store the result in must be 4 elements in length
 */
void colorFromXML(DOMElement *node, GLfloat color[]);

/*!
 @function randomFloat
 @abstract returns a random number between 0 and 1
 @result A random float between 0 and 1
 */
float randomFloat();

#endif
