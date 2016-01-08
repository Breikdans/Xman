#ifndef IMPORTER_H_
#define IMPORTER_H_

#include <OGRE/Ogre.h>
#include <xercesc/dom/DOM.hpp>
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

		void parseBalls(DOMNode* nodeBalls, Scene *scn);

};
#endif /* IMPORTER_H_ */
