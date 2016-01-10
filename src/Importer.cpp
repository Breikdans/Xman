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

	XMLCh* ball_ch		= XMLString::transcode("ball");
//	XMLCh* camera_ch 	= XMLString::transcode("camera");
//	XMLCh* graph_ch 	= XMLString::transcode("graph");
	// Procesando los nodos hijos del raíz...
	for (XMLSize_t i = 0; i < elementRoot->getChildNodes()->getLength(); ++i )
	{
		DOMNode* node = elementRoot->getChildNodes()->item(i);
		if (node->getNodeType() == DOMNode::ELEMENT_NODE)
		{
			if (XMLString::equals(node->getNodeName(), ball_ch))
				parseBalls(node, scene);
//			else if (XMLString::equals(node->getNodeName(), camera_ch))	// Nodo <camera>?
//				parseCamera(node, scene);
//			else if (XMLString::equals(node->getNodeName(), graph_ch)) 	// Nodo <graph>?
//					parseGraph(node, scene);
		}
	}// Fin for

	// Liberar recursos.
	XMLString::release(&ball_ch);
//	XMLString::release(&camera_ch);
//	XMLString::release(&graph_ch);

	delete parser;
}


void Importer::parseBalls(DOMNode* nodeBall, Scene *scn)
{
  DOMNamedNodeMap* attributes = nodeBall->getAttributes();
  DOMNode* indexNode = attributes->getNamedItem(XMLString::transcode("index"));
  DOMNode* typeNode = attributes->getNamedItem(XMLString::transcode("type"));

  int ballIndex = atoi(XMLString::transcode(indexNode->getNodeValue()));
  string ballTypeString = XMLString::transcode(typeNode->getNodeValue());
  EN_TYPE_BALL ballType=EN_NORMAL;

  if (ballTypeString=="up") {
	   ballType =EN_POWERUP;
  }
  else if (ballTypeString=="up") {
  		  ballType = EN_NORMAL;
  }

  XMLCh* xPos = XMLString::transcode("x");
  XMLCh* yPos = XMLString::transcode("y");
  XMLCh* zPos = XMLString::transcode("z");

  float x = getValueFromTag(nodeBall, xPos);
  float y = getValueFromTag(nodeBall, yPos);
  float z = getValueFromTag(nodeBall, zPos);

  // Instanciar la posición del nodo.
  Ogre::Vector3 position(x, y, z);

  // Instanciar el nodo.
  SceneBall ball(ballIndex, ballType, position);
  // Añadir el nodo a la estructura de grafo.
  scn->addBall(ball);

  XMLString::release(&xPos);
  XMLString::release(&yPos);
  XMLString::release(&zPos);
}

float Importer::getValueFromTag(DOMNode* node, const XMLCh *tag)
{
  for (XMLSize_t i = 0; i < node->getChildNodes()->getLength(); ++i ) {

    DOMNode* aux = node->getChildNodes()->item(i);

    if (aux->getNodeType() == DOMNode::ELEMENT_NODE &&
	XMLString::equals(aux->getNodeName(), tag))
      return atof(XMLString::transcode(aux->getFirstChild()->getNodeValue()));

  }
  return 0.0;
}




























/*void Importer::parseBalls(DOMNode* nodeBalls, Scene *scn)
{
	DOMNode* indexNode = attributes->getNamedItem(XMLString::transcode("index"));
	DOMNode* typeNode = attributes->getNamedItem(XMLString::transcode("type"));

	int index 	= atoi(XMLString::transcode(indexNode->getNodeValue()));
//	int type 	= XMLString::transcode(fpsNode->getNodeValue());

	XMLCh* x_ch = XMLString::transcode("x");
	XMLCh* y_ch = XMLString::transcode("y");
	XMLCh* z_ch = XMLString::transcode("z");

	float x = getValueFromTag(vertexNode, x_ch);
	float y = getValueFromTag(vertexNode, y_ch);
	float z = getValueFromTag(vertexNode, z_ch);

	for (XMLSize_t i = 0; i < nodeBalls->getChildNodes()->getLength(); ++i )
	{
		// Atributos de la bola.
		DOMNamedNodeMap* attributes = nodeBalls->getAttributes();

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
}*/


