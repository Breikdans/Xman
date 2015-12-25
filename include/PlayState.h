#ifndef PlayState_H
#define PlayState_H

#include <Ogre.h>
#include <OIS/OIS.h>
#include <OgreOverlaySystem.h>
#include <OgreOverlayElement.h>
#include <OgreOverlayManager.h>

#include "GameState.h"
#include "Grid.h"

const std::string STRING_NODE_PLAYER_ = "node_player_";
const std::string STRING_NODE_CPU_ = "node_cpu_";

#ifdef _DEBUG
	#define DEBUG_TRZ(x) x
#else
	#define DEBUG_TRZ(x)
#endif

class PlayState : public Ogre::Singleton<PlayState>, public GameState
{
	public:
		PlayState () {}

		void enter ();
		void exit ();
		void pause ();
		void resume ();

		void keyPressed (const OIS::KeyEvent &e);
		void keyReleased (const OIS::KeyEvent &e);

		void mouseMoved (const OIS::MouseEvent &e);
		void mousePressed (const OIS::MouseEvent &e, OIS::MouseButtonID id);
		void mouseReleased (const OIS::MouseEvent &e, OIS::MouseButtonID id);

		bool frameStarted (const Ogre::FrameEvent& evt);
		bool frameEnded (const Ogre::FrameEvent& evt);

		// Heredados de Ogre::Singleton.
		static PlayState& getSingleton ();
		static PlayState* getSingletonPtr ();

		int getPuntosPlayer(void) const {return puntosPlayer;}
		int getPuntosCPU(void) const {return puntosCPU;}

	protected:
		Ogre::Root* _root;
		Ogre::SceneManager* _sceneMgr;
		Ogre::RenderWindow* _renderWindow;
		Ogre::Viewport* _viewport;
		Ogre::Camera* _camera;
		Ogre::OverlayManager* _overlayManager;
		Ogre::RaySceneQuery *_raySceneQuery;

		void createScene();
		void createOverlay();
		void hideOverlay();
		void updateInfoOverlay();

		Ogre::Ray setRayQuery(int posx, int posy, uint32 mask);
		void getSelectedNode(uint32 mask, int &x, int &y, std::string &nodeName);

		void ActualizaTablero(usint16, usint16);
		bool CompruebaDisparo(Grid&, usint16 posx, usint16 posy);
		bool CheckHundido(Grid& grid, usint16 posx, usint16 posy);
		void CambiarTurno(EN_TURNO turno);
		void showExitMsgCegui();
		bool BotonSi(const CEGUI::EventArgs &e);
		bool BotonNo(const CEGUI::EventArgs &e);
		CEGUI::MouseButton convertMouseButton(OIS::MouseButtonID id);


		void CalculaDisparoCPU(int &posX, int &posY);
		bool BuscarCasillaLibreDerecha(int &posX, int &posY) const;
		bool BuscarCasillaLibreIzquierda(int &posX, int &posY) const;
		bool BuscarCasillaLibreArriba(int &posX, int &posY) const;
		bool BuscarCasillaLibreAbajo(int &posX, int &posY) const;
		bool esCasillaTocada(const Grid& grid, int posX, int posY) const;
		bool hayCasillaTocada(const Grid& grid, int &posX, int &posY) const;
		void ObtenerSiguienteCasilla(int &posX, int &posY) const;
		void ObtenerCasillaAleatoria(int &posX, int &posY) const;

		bool obtenerPopaH(Grid& grid, int posXProa, int posYProa, int &posXPopa, int &posYPopa) const;
		bool obtenerProaH(Grid& grid, int posXPopa, int posYPopa, int &posXProa, int &posYProa) const;
		bool obtenerPopaV(Grid& grid, int posXProa, int posYProa, int &posXPopa, int &posYPopa) const;
		bool obtenerProaV(Grid& grid, int posXPopa, int posYPopa, int &posXProa, int &posYProa) const;
		bool checkHundidoHorizontal(Grid& grid, int posXProa, int posYProa, int posXPopa, int posYPopa) const;
		bool checkHundidoVertical(Grid& grid, int posXProa, int posYProa, int posXPopa, int posYPopa) const;

		void marcarHundidoHorizontal(Grid& grid, int posXProa, int posYProa, int posXPopa, int posYPopa);
		void marcarHundidoVertical(Grid& grid, int posXProa, int posYProa, int posXPopa, int posYPopa);
		void rodearDisparadoHorizontal(Grid& grid, int posXProa, int posYProa, int posXPopa, int posYPopa);
		void rodearDisparadoVertical(Grid& grid, int posXProa, int posYProa, int posXPopa, int posYPopa);

		void sumaPuntos();

		int puntosPlayer;
		int puntosCPU;

		EN_TURNO _turno;
		bool _exitGame;

		Grid CPUGrid;
		Grid PlayerGrid;
};

#endif
