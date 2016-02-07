#include "Importer.h"
#include "GraphVertex.h"
#include "GraphEdge.h"
#include "PlayState.h"

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
		if (xmlDoc==NULL)
		{
			std::string msg = path;
			Ogre::LogManager::getSingleton().logMessage("No se ha encontrado -> "+ msg);
		}
		else
		{
			elementRoot = xmlDoc->getDocumentElement();
			// Procesando los nodos hijos del raíz...
			for (XMLSize_t i = 0; i < elementRoot->getChildNodes()->getLength(); i++ )
			{
				DOMNode* node = elementRoot->getChildNodes()->item(i);

				if (isNodeNamed(node,"camera"))
				{
					parseCamera(node, scene);
				}
				else if (isNodeNamed(node,"graph"))
				{
					parseGraph(node, scene);
				}
			}// Fin for

			createMasksPath(scene);
		}

	delete parser;
}

void Importer::createMasksPath(Scene* scene)
{
	std::vector<GraphVertex*> v = scene->getGraph()->getVertexes();
	std::vector<GraphVertex*>::iterator it;

	for (it = v.begin(); it!=v.end(); it++ )
	{
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
	string strBallType = getAttribute(node,"ball");

	XMLCh* xPos = XMLString::transcode("x");
	XMLCh* yPos = XMLString::transcode("y");
	XMLCh* zPos = XMLString::transcode("z");

	float x = getValueFromTag(node, xPos);
	float y = getValueFromTag(node, yPos);
	float z = getValueFromTag(node, zPos);

	int type = VE_NORMAL;

	if(strType == "scatterRed")
	{
		PlayState::getSingleton().getRed().addScatterPoint(strBallType, index);
	}
	if(strType == "scatterPink")
	{
		PlayState::getSingleton().getPink().addScatterPoint(strBallType, index);
	}
	if(strType == "scatterBlue")
	{
		PlayState::getSingleton().getBlue().addScatterPoint(strBallType, index);
	}
	if(strType == "scatterOrange")
	{
		PlayState::getSingleton().getOrange().addScatterPoint(strBallType, index);
	}

	if(strType == "transportLeft")
	{
		type |= VE_TRANSPORT_LEFT;
	}

	if(strType == "transportRight")
	{
		type |= VE_TRANSPORT_RIGHT;
	}

	if(strType == "stPlayer")
	{
		type |= VE_STPLAYER;
	}

	if(strType == "stEnemy")
	{
		type |= VE_STENEMY;
	}

	if(strType == "forbidden")
	{
		type |= VE_FORBIDDEN;
	}

	if(strBallType == "ballPower")
	{
		type |= VE_BALLPOWER;
	}
	else if(strBallType == "ballNone")
	{
		type |= VE_BALLNONE;
	}
	else
	{
		type |= VE_BALL;
	}

//DebugVertex(index,x,y,z,type);

	GraphVertex *graphVertex = new GraphVertex(index, type, Ogre::Vector3(x,y,z));
	scn->getGraph()->addVertex(graphVertex);


	XMLString::release(&xPos);
	XMLString::release(&yPos);
	XMLString::release(&zPos);

}

void Importer::parseEdge(DOMNode* node, Scene *scn)
{
//	cout << "edge: ";
	std::vector<int> vertexes;

	// Recorre los nodos
	for (XMLSize_t i = 0; i < node->getChildNodes()->getLength(); i++ )
	{
		DOMNode* vertexNode = node->getChildNodes()->item(i);
		if (isNodeNamed(vertexNode,"vertex"))
		{
			char *tempVal = XMLString::transcode(vertexNode->getFirstChild()->getNodeValue());
			int vertexValue = atoi(tempVal);
//			cout << "vertex: "<< vertexValue << endl;

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
	if(strAttr == 0)
		throw("atributo no existe");
	char *tempVar = XMLString::transcode(strAttr->getNodeValue());
	string result = tempVar;

	XMLString::release(&attribute);
	XMLString::release(&tempVar);
	return result;
}

void Importer::DebugVertex(int index, float x, float y, float z, int type)
{
	cout << "vertex: "<< index << " x:" << x << "  y:" << y << "  z:" << z << "  Balltype: ";
    cout << showbase // show the 0x prefix
         << internal // fill between the prefix and the number
         << setfill('0'); // fill with 0s
    cout << hex << setw(4) << type << dec << endl;

}
