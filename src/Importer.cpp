#include "Importer.h"

using namespace std;

template<> Importer* Ogre::Singleton<Importer>::msSingleton = 0;

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

void Importer::parseBalls(DOMNode* nodeBalls, Scene *scn)
{
	// Atributos de la bola.
	DOMNamedNodeMap* attributes = nodeBalls->getAttributes();

	DOMNode* indexNode = attributes->getNamedItem(XMLString::transcode("index"));
	DOMNode* typeNode = attributes->getNamedItem(XMLString::transcode("type"));

	int index 	= atoi(XMLString::transcode(indexNode->getNodeValue()));
	int type 	= XMLString::transcode(fpsNode->getNodeValue());

	XMLCh* x_ch = XMLString::transcode("x");
	XMLCh* y_ch = XMLString::transcode("y");
	XMLCh* z_ch = XMLString::transcode("z");

	float x = getValueFromTag(vertexNode, x_ch);
	float y = getValueFromTag(vertexNode, y_ch);
	float z = getValueFromTag(vertexNode, z_ch);

	for (XMLSize_t i = 0; i < nodeBalls->getChildNodes()->getLength(); ++i )
	{
		DOMNode* node = nodeBalls->getChildNodes()->item(i);

		if (node->getNodeType() == DOMNode::ELEMENT_NODE)
		{
			if (XMLString::equals(node->getNodeName(), vertex_ch))		// Nodo <vertex>?
				addVertexToScene(node, scene);
			else if (XMLString::equals(node->getNodeName(), edge_ch))	// Nodo <edge>?
				addEdgeToScene(node, scene);
		}
	}

	XMLString::release(&x_ch);
	XMLString::release(&y_ch);
	XMLString::release(&z_ch);
}

