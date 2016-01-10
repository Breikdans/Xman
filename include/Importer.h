#ifndef IMPORTER_H_
#define IMPORTER_H_

#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <OGRE/Ogre.h>
#include <OgreVector3.h>
#include <OgreVector4.h>
#include <iostream>
#include <string>
#include <Importer.h>
#include "Scene.h"

using namespace std;
using namespace xercesc;

class Importer : public Ogre::Singleton<Importer>
{
	public:
		// Unique public member function to parse an XML.
		void parseScene (const char * path, Scene *scn);
		string getAttribute(const DOMNode* node, const char* attr);

		// Inheritance from Ogre::Singleton.
		static Importer& getSingleton ();
		static Importer* getSingletonPtr ();
	private:

		void parseBalls(DOMNode* node, Scene *scn);
		void parseCamera(DOMNode* node, Scene *scn);
		void parseFrame(DOMNode* node, Scene *scn);
		void parsePosition(DOMNode* node, Scene *scn);
		void parseRotation(DOMNode* node, Scene *scn);
		void parseGraph(DOMNode* node, Scene *scn);
		void parseVertex(DOMNode* node, Scene *scn);
		void parseEdge(DOMNode* node, Scene *scn);
		float getValueFromTag(DOMNode* node, const XMLCh *tag);
		bool isNodeNamed(DOMNode* node,const char* name);
};
#endif /* IMPORTER_H_ */
