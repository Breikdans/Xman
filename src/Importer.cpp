#include "Importer.h"

typedef enum{
	EN_VE_NORMAL 	= 0,
	EN_VE_TRANSPORT	= 1,
	EN_VE_STPLATYER	= 2,
	EN_VE_STENEMY	= 3,
	EN_VE_FORBIDDEN	= 4
}EN_TYPE_VERTEX;

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

	// Procesando los nodos hijos del raíz...
	for (XMLSize_t i = 0; i < elementRoot->getChildNodes()->getLength(); i++ )
	{
		DOMNode* node = elementRoot->getChildNodes()->item(i);

		if (isNodeNamed(node,"ball")) {
			parseBalls(node, scene);
		}	else if (isNodeNamed(node,"camera")) {
			parseCamera(node, scene);
		} else if (isNodeNamed(node,"graph")) {
			parseGraph(node, scene);
		}
	}// Fin for

	delete parser;
}

void Importer::parseGraph(DOMNode* node, Scene *scn)
{
	cout << "Graph found... " << endl;
	// Recorre los nodos
	for (XMLSize_t i = 0; i < node->getChildNodes()->getLength(); i++ )
	{
		DOMNode* frameNode = node->getChildNodes()->item(i);
		if (isNodeNamed(frameNode,"vertex"))
		{
			parseVertex(frameNode,scn);
		}
		else if(isNodeNamed(frameNode,"edge"))
		{
			parseEdge(frameNode,scn);
		}
	}
}

void Importer::parseVertex(DOMNode* node, Scene *scn)
{
	// Encuentra los atributos index y fps
	int index = atoi(getAttribute(node,"index").c_str());
	string type = getAttribute(node,"type");

	XMLCh* xPos = XMLString::transcode("x");
	XMLCh* yPos = XMLString::transcode("y");
	XMLCh* zPos = XMLString::transcode("z");

	float x = getValueFromTag(node, xPos);
	float y = getValueFromTag(node, yPos);
	float z = getValueFromTag(node, zPos);

	cout << "vertex: "<< index <<", type: "<< type << "x:" << x << ",y:" << y << ",z:" << z << endl;
}

void Importer::parseEdge(DOMNode* node, Scene *scn) {}

void Importer::parseCamera(DOMNode* node, Scene *scn)
{
	// Encuentra los atributos index y fps
	int indexCamera = atoi(getAttribute(node,"index").c_str());
	string fps = getAttribute(node,"fps");

	cout << "indexCamera " << indexCamera << ", fps " << fps << endl;

	// Recorre los nodos frame.
	for (XMLSize_t i = 0; i < node->getChildNodes()->getLength(); i++ )
	{
		DOMNode* frameNode = node->getChildNodes()->item(i);
		if (isNodeNamed(frameNode,"frame"))
		{
			parseFrame(frameNode,scn);
		}
	}
}


void Importer::parseFrame(DOMNode* node, Scene *scn)
{
	// Encuentra los atributos index y fps
	int indexFrame = atoi(getAttribute(node,"index").c_str());
	cout << "frame-> " << indexFrame << endl;

	// Recorre los nodos
	for (XMLSize_t i = 0; i < node->getChildNodes()->getLength(); i++ )
	{
		DOMNode* frameNode = node->getChildNodes()->item(i);
		if (isNodeNamed(frameNode,"position"))
		{
			parsePosition(frameNode,scn);
		}
		else if(isNodeNamed(frameNode,"rotation"))
		{
			parseRotation(frameNode,scn);
		}
	}
}

void Importer::parsePosition(DOMNode* node, Scene *scn)
{
	XMLCh* xPos = XMLString::transcode("x");
	XMLCh* yPos = XMLString::transcode("y");
	XMLCh* zPos = XMLString::transcode("z");

	float x = getValueFromTag(node, xPos);
	float y = getValueFromTag(node, yPos);
	float z = getValueFromTag(node, zPos);

	cout << "x:" << x << ",y:" << y << ",z:" << z << endl;
}

void Importer::parseRotation(DOMNode* node, Scene *scn)
{
	XMLCh* xPos = XMLString::transcode("x");
	XMLCh* yPos = XMLString::transcode("y");
	XMLCh* zPos = XMLString::transcode("z");
	XMLCh* wPos = XMLString::transcode("w");

	float x = getValueFromTag(node, xPos);
	float y = getValueFromTag(node, yPos);
	float z = getValueFromTag(node, zPos);
	float w = getValueFromTag(node, wPos);

	cout << "x:" << x << ",y:" << y << ",z:" << z << ",w:"<<w << endl;
}

void Importer::parseBalls(DOMNode* node, Scene *scn)
{
	int index =  atoi(getAttribute(node,"index").c_str());
	string typeString =  getAttribute(node,"type");

	EN_TYPE_BALL type=EN_NORMAL;

	if (typeString=="up")
	{
		type =EN_POWERUP;
	}
	else if (typeString=="up")
	{
		type = EN_NORMAL;
	}

	XMLCh* xPos = XMLString::transcode("x");
	XMLCh* yPos = XMLString::transcode("y");
	XMLCh* zPos = XMLString::transcode("z");

	float x = getValueFromTag(node, xPos);
	float y = getValueFromTag(node, yPos);
	float z = getValueFromTag(node, zPos);

	// Instanciar la posición del nodo.
	Ogre::Vector3 position(x, y, z);

	// Instanciar el nodo.
	SceneBall ball(index, type, position);
	// Añadir el nodo a la estructura de grafo.
	scn->addBall(ball);

	XMLString::release(&xPos);
	XMLString::release(&yPos);
	XMLString::release(&zPos);
}

float Importer::getValueFromTag(DOMNode* node, const XMLCh *tag)
{
	for (XMLSize_t i = 0; i < node->getChildNodes()->getLength(); i++ )
	{

		DOMNode* aux = node->getChildNodes()->item(i);

		if ( aux->getNodeType() == DOMNode::ELEMENT_NODE &&
			 XMLString::equals(aux->getNodeName(), tag) )
		return atof(XMLString::transcode(aux->getFirstChild()->getNodeValue()));
	}
	return 0.0;
}


bool Importer::isNodeNamed(DOMNode* node,const char* name)
{
	bool result=false;
	if (node->getNodeType() == DOMNode::ELEMENT_NODE)
	{
		XMLCh* name_ch = XMLString::transcode(name);
		if (XMLString::equals(node->getNodeName(), name_ch))
		{
			result=true;
		}
	}
	return result;
}

string Importer::getAttribute(const DOMNode* node, const char *attr)
{
	DOMNamedNodeMap* attributes = node->getAttributes();
	DOMNode* strAttr = attributes->getNamedItem(XMLString::transcode(attr));
	string result =XMLString::transcode(strAttr->getNodeValue());
	return result;
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


