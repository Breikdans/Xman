#include "Importer.h"

template<> Importer* Ogre::Singleton<Importer>::msSingleton = 0;

using namespace std;
using namespace xercesc;

Importer* Importer::getSingletonPtr ()
{
	return msSingleton;
}

Importer& Importer::getSingleton ()
{
	assert(msSingleton);
	return *msSingleton;
}

void Importer::parseScene (const char * path, Scene *scene)
{
	// Inicialización.
	XMLPlatformUtils::Initialize();

	XercesDOMParser* parser = new XercesDOMParser();
	parser->setValidationScheme(XercesDOMParser::Val_Always);

	parser->parse(path);	// indicamos el camino del fichero a parsear

	DOMDocument* xmlDoc;
	DOMElement* elementRoot;

	// Obtener el elemento raíz del documento.
	xmlDoc = parser->getDocument();
	elementRoot = xmlDoc->getDocumentElement();

	XMLCh* balls_ch		= XMLString::transcode("balls");
//	XMLCh* camera_ch 	= XMLString::transcode("camera");
//	XMLCh* graph_ch 	= XMLString::transcode("graph");
	// Procesando los nodos hijos del raíz...
	for (XMLSize_t i = 0; i < elementRoot->getChildNodes()->getLength(); ++i )
	{
		DOMNode* node = elementRoot->getChildNodes()->item(i);
		if (node->getNodeType() == DOMNode::ELEMENT_NODE)
		{
			if (XMLString::equals(node->getNodeName(), balls_ch))
				parseBalls(node, scene);
//			else if (XMLString::equals(node->getNodeName(), camera_ch))	// Nodo <camera>?
//				parseCamera(node, scene);
//			else if (XMLString::equals(node->getNodeName(), graph_ch)) 	// Nodo <graph>?
//					parseGraph(node, scene);
		}
	}// Fin for

	// Liberar recursos.
	XMLString::release(&balls_ch);
//	XMLString::release(&camera_ch);
//	XMLString::release(&graph_ch);

	delete parser;
}

