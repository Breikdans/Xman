#ifndef IMPORTER_H_
#define IMPORTER_H_

#include <OGRE/Ogre.h>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <iostream>




#include "Scene.h"

class Importer : public Ogre::Singleton<Importer>
{
	public:
		// Unique public member function to parse an XML.
		void parseScene (const char * path, Scene *scn);

		// Inheritance from Ogre::Singleton.
		static Importer& getSingleton ();
		static Importer* getSingletonPtr ();
	private:

		void parseBalls(xercesc::DOMNode* nodeBalls, Scene *scn);

};
#endif /* IMPORTER_H_ */
