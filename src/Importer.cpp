#include "Importer.h"
#include "GraphVertex.h"
#include "GraphEdge.h"

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

/**
 */
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
		if (xmlDoc==NULL) {
			std::string msg = path;
			Ogre::LogManager::getSingleton().logMessage("No se ha encontrado -> "+ msg);
		} else {
				elementRoot = xmlDoc->getDocumentElement();
				// Procesando los nodos hijos del raíz...
				for (XMLSize_t i = 0; i < elementRoot->getChildNodes()->getLength(); i++ )
				{
					DOMNode* node = elementRoot->getChildNodes()->item(i);

					if (isNodeNamed(node,"ball")) {
						parseBalls(node, scene);
					} else if (isNodeNamed(node,"camera")) {
						parseCamera(node, scene);
					} else if (isNodeNamed(node,"graph")) {
						parseGraph(node, scene);
					}
				}// Fin for


				createMasksPath(scene);

		}

	delete parser;
}

void Importer::createMasksPath(Scene* scene) {
	std::vector<GraphVertex*> v = scene->getGraph()->getVertexes();
	std::vector<GraphVertex*>::iterator it;

	for (it = v.begin(); it!=v.end(); it++ ) {
		(*it)->setMaskPaths();
	}

}

void Importer::parseGraph(DOMNode* node, Scene *scn)
{
	cout << endl<< "Graph found... " << endl;
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
	string strType = getAttribute(node,"type");

	XMLCh* xPos = XMLString::transcode("x");
	XMLCh* yPos = XMLString::transcode("y");
	XMLCh* zPos = XMLString::transcode("z");

	float x = getValueFromTag(node, xPos);
	float y = getValueFromTag(node, yPos);
	float z = getValueFromTag(node, zPos);

	EN_TYPE_VERTEX type;

	if(strType == "normal")
	{
		type = EN_VE_NORMAL;
	}
	else if(strType == "transport")
	{
		type = EN_VE_TRANSPORT;
	}
	else if(strType == "stPlayer")
	{
		type = EN_VE_STPLATYER;
	}
	else if(strType == "stEnemy")
	{
		type = EN_VE_STENEMY;
	}
	else if(strType == "forbidden")
	{
		type = EN_VE_FORBIDDEN;
	}

	cout << "vertex: "<< index <<", type: "<< type << "x:" << x << ",y:" << y << ",z:" << z << endl;

	GraphVertex *graphVertex = new GraphVertex(index, type, Ogre::Vector3(x,y,z));
	scn->getGraph()->addVertex(graphVertex);


	XMLString::release(&xPos);
	XMLString::release(&yPos);
	XMLString::release(&zPos);

}

void Importer::parseEdge(DOMNode* node, Scene *scn)
{
	cout << "edge: ";
	std::vector<int> vertexes;

	// Recorre los nodos
	for (XMLSize_t i = 0; i < node->getChildNodes()->getLength(); i++ )
	{
		DOMNode* vertexNode = node->getChildNodes()->item(i);
		if (isNodeNamed(vertexNode,"vertex"))
		{
			char *tempVal = XMLString::transcode(vertexNode->getFirstChild()->getNodeValue());
			int vertexValue = atoi(tempVal);
			cout << "vertex: "<< vertexValue << endl;

			vertexes.push_back(vertexValue);
			XMLString::release(&tempVal);
		}
	}
	GraphVertex *v1 = scn->getGraph()->getVertex(vertexes[0]);
	GraphVertex *v2 = scn->getGraph()->getVertex(vertexes[1]);

	scn->getGraph()->addEdge(v1, v2);
}

void Importer::parseCamera(DOMNode* node, Scene *scn)
{
	// Encuentra los atributos index y fps
	int indexCamera = atoi(getAttribute(node,"index").c_str());
	int fps = atoi(getAttribute(node,"fps").c_str());
	std::string name = getAttribute(node,"name");

	cout << "indexCamera " << indexCamera << ", fps " << fps << ", name " << name << endl;
	Camera* camera = new Camera(indexCamera,fps,name);

	// Recorre los nodos frame.
	for (XMLSize_t i = 0; i < node->getChildNodes()->getLength(); i++ )
	{
		DOMNode* frameNode = node->getChildNodes()->item(i);
		if (isNodeNamed(frameNode,"frame"))
		{
			parseFrame(frameNode,scn,camera);
		}
	}

	// añadimos camara a la escena
	scn->addCamera(camera);
}

void Importer::parseFrame(DOMNode* node, Scene *scn, Camera *camera)
{
	// Encuentra los atributos index y fps
	int indexFrame = atoi(getAttribute(node,"index").c_str());
	cout << "frame-> " << indexFrame << endl;

	Ogre::Vector3 framePosition;
	Ogre::Vector4 frameRotation;

	// Recorre los nodos
	for (XMLSize_t i = 0; i < node->getChildNodes()->getLength(); i++ )
	{
		DOMNode* frameNode = node->getChildNodes()->item(i);
		if (isNodeNamed(frameNode,"position"))
		{
			parseFramePosition(frameNode,scn,&framePosition);
		}
		else if(isNodeNamed(frameNode,"rotation"))
		{
			parseFrameRotation(frameNode,scn,&frameRotation);
		}
	}

	// añadimos frame a la camara
	Frame* frame = new Frame(indexFrame, framePosition, frameRotation);
	camera->addFrameToPath(frame);
}

void Importer::parseFramePosition(DOMNode* node, Scene *scn, Ogre::Vector3 *position)
{
	XMLCh* xPos = XMLString::transcode("x");
	XMLCh* yPos = XMLString::transcode("y");
	XMLCh* zPos = XMLString::transcode("z");

	float x = getValueFromTag(node, xPos);
	float y = getValueFromTag(node, yPos);
	float z = getValueFromTag(node, zPos);

	position->x = x;
	position->y = y;
	position->z = z;

	cout << "x:" << x << ",y:" << y << ",z:" << z << endl;

	XMLString::release(&xPos);
	XMLString::release(&yPos);
	XMLString::release(&zPos);
}

void Importer::parseFrameRotation(DOMNode* node, Scene *scn, Ogre::Vector4 *rotation)
{
	XMLCh* xPos = XMLString::transcode("x");
	XMLCh* yPos = XMLString::transcode("y");
	XMLCh* zPos = XMLString::transcode("z");
	XMLCh* wPos = XMLString::transcode("w");

	float x = getValueFromTag(node, xPos);
	float y = getValueFromTag(node, yPos);
	float z = getValueFromTag(node, zPos);
	float w = getValueFromTag(node, wPos);

	rotation->x = x;
	rotation->y = y;
	rotation->z = z;
	rotation->w = w;

	cout << "x:" << x << ",y:" << y << ",z:" << z << ",w:"<<w << endl;


	XMLString::release(&xPos);
	XMLString::release(&yPos);
	XMLString::release(&zPos);
	XMLString::release(&wPos);
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

	cout << "ball: "<< index <<", type: "<< typeString << "x:" << x << ",y:" << y << ",z:" << z << endl;

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
	float ret = 0.0;
	for (XMLSize_t i = 0; i < node->getChildNodes()->getLength(); i++ )
	{
		DOMNode* aux = node->getChildNodes()->item(i);

		if ( aux->getNodeType() == DOMNode::ELEMENT_NODE &&
			 XMLString::equals(aux->getNodeName(), tag) )
		{
			char *tempVal = XMLString::transcode(aux->getFirstChild()->getNodeValue());
			ret = atof(tempVal);
			XMLString::release(&tempVal);
			return ret;
		}
	}
	return ret;
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
		XMLString::release(&name_ch);
	}
	return result;
}

/**
 * Dado un nodo y el atributo que queremos recoger, nos devuelve su valor en un string
 *
 * @param: const DOMNode* node 		ENTRADA. Nodo del cual queremos coger el valor de un atributo
 * @param: const char *attr			ENTRADA. Nombre del atributo a recoger su valor
 *
 * @return: string					SALIDA. Valor del Atributo
 */
string Importer::getAttribute(const DOMNode* node, const char *attr)
{
	DOMNamedNodeMap* attributes = node->getAttributes();
	XMLCh* attribute = XMLString::transcode(attr);
	DOMNode* strAttr = attributes->getNamedItem(attribute);
	char *tempVar = XMLString::transcode(strAttr->getNodeValue());
	string result = tempVar;
	
	XMLString::release(&attribute);
	XMLString::release(&tempVar);
	return result;
}

