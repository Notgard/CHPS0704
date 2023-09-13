/* Copyright (C) 2019 Stéphanie Prévost et Julien Gerhards- All Rights Reserved
 * This file is part of libQGLShaderViewer
 * Last modification : 16/09/2021 by S. Prévost
 */

#ifndef WINDOW_H
#define WINDOW_H

#include <QOpenGLWindow>
#include <QOpenGLFunctions>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QWheelEvent>
#include <QTimer>
#include <QList>
#include <QMap>
#include <QString>
#include <QFont>
#include <QColor>
#include <QElapsedTimer>
#include <QOpenGLFramebufferObject>
#include <QOpenGLExtraFunctions>
#include <QWidget>

#include "define.h"



#include "QGLCamera.h"

#include "Mesh.h"

#include "TextureMaterial.h"
#include "GridMaterial.h"
#include "FBO.h"

class MouseManager;				   


// ==============================================================
//    QGLShaderViewer
// ---------------------
//
// Classe représentant une fenêtre OpenGL,
// Classe centrale du projet libQGLShaderViewer.
//
// Hérite de QOpenGLWindow
// Elle facilite le développement d'application de visu 3D, exploitant les shaders, les FBO de OpenGL 3.
// L'activation d'une vision en relief quadBuffer est possible.
//



/**    Classe centrale du projet représentant une fenêtre OpenGL.
 * @brief      Classe représentant une fenêtre OpenGL
 *             Classe centrale du projet libQGLShaderViewer.
 *			   Hérite de QOpenGLWindow
 *             Elle facilite le développement d'application de visu 3D, exploitant les shaders, les FBO de OpenGL 3.
 *             L'activation d'une vision en relief quadBuffer est possible.
 *
 *             <h3>Usage</h3>
 *             Pour utiliser QGLShaderViewer, vous devez faire dériver votre class Viewer de QGLShaderViewer et
 *             surchager les méthodes virtuelles init(), draw(), animate(), etc. L'exemple TestViewer illustre ce principe.
 *
 * @class QGLShaderViewer
 * @file      QGLShaderViewer.h
 * @author    S. Prévost & j. Gerhards 
 * @version   1.0
 * @date      Septembre 2021
 *
 \nosubgrouping 
 */
class DLL_SPEC QGLShaderViewer : public QOpenGLWindow, protected QOpenGLFunctions
{
   Q_OBJECT

public:
    QGLShaderViewer(QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags());
    ~QGLShaderViewer() override;


// ----- P O O L S   A C T I O N S   ---
/*! @name Pools actions */
//@{	
    /**
     * @brief Add the object <em>entity</em> in the scene under the name <em>name</em>.
     * @param[in] name          Reference name of the entity to add.
     * @param entity        Entity to add.
     */
    void addEntityInScene     ( const QString & name, Mesh * entity );      // Add a entity in the scene
    /**
     * @brief remove the Entity called <em>name</em> from the scene
     * @param[in] name
     */
    void removeEntityFromScene( const QString & name );                     // Remove and delete the entity named "name"
    /**
      * @brief add the geometry <em>entity</em> in the pool of available geometries.
      * @param[in] name         Reference name of the geometry to add.
      * @param entity       Geometry to add to the pool of available geometries.
      */
    void addGeometry          ( const QString & name, Geometry * entity );  // Add a geometry in the pool
    /**
     * @brief Remove and delete the geometry called <em>name</em> of the pool
     * @param[in] name          Name of the geometry to delete.
     */
    void removeGeometry       ( const QString & name );                     // Remove and delete the geometry named "name" of the pool
    /**
     * @brief Add a material <em>material</em> in the pool of the available Material under the name <em>name</em>.
     * @param[in] name          Reference name of the Material to add.
     * @param material      Material to add to the pool
     */
    void addMaterial          (const QString & name, Material * material ); // Add a material in the pool
    /**
     * @brief Remove and delete the material named "name" of the pool of the available material.
     * @param[in] name           Reference name of the Material to delete.
     */
    void removeMaterial       ( const QString & name );                     // Remove and delete the material named "name" of the pool

    /**
     * @brief Return the entity called <em>name</em> in the pool of the available entities.
     * @param[in] name          Name of the searched entity
     * @return
     */
    Mesh     *    getEntityInScene    (const QString & name ) const;
    /**
     * @brief Return the list of the entities available in the scene pool.
     * @return
     */
    QList<Mesh *> getListEntityInScene();
    /**
     * @brief Return the geometry called <em>name</em> in the pool of the available geometries.
     * @param[in] name          Name of the searched geometry
     * @return a pointer on the geometry
     */
    Geometry *    getGeometry         (const QString & name ) const;
    /**
     * @brief Return the material called <em>name</em> in the pool of the available materials.
     * @param[in] name          Name of the searched material
     * @return
     */
    Material *    getMaterial         (const QString & name ) const;
//@}	

// ----- A N I M A T I O N  ---
/*! @name Animation */
//@{
    bool   isAnimated          () const;           //!< return true if the animation is started
    void   setAnimationPeriod  (int period);       //!< set the period of the animation loop
    void   startAnimation      ();                 //!< Enable  the animation loop
    void   stopAnimation       ();                 //!< Disable the animation loop
    qint64 getLastTimeAnimation    () const;	   //!< return the start time of the last animation loop
    qint64 getCurrentTimeAnimation () const;	   //!< return the current time of the animation loop
    qint64 getEllapsedTimeAnimation() const;	   //!< return the ellapsed time between the last and the current time of the animation loop 
//@}

protected:
// ----- W i d g e t   C o n t a i n e r
    QWidget * getThisWidget() const;				//!< return the application pointer conveted in widget type 
    bool      event(QEvent *event) override;

// ----- E v e n t  m a n a g e r
/*! @name Event manager : keyboard and mouse */
//@{
    virtual void mousePressEvent  (QMouseEvent * event)   override;		//!< management of mouse events of type press 
    virtual void mouseMoveEvent   (QMouseEvent * event)   override;		//!< management of mouse events of type move 
    virtual void mouseReleaseEvent(QMouseEvent * event)   override;		//!< management of mouse events of type release 
    virtual void mouseDoubleClickEvent (QMouseEvent * ev ) override;	//!< management of mouse events of type double clic 
    virtual void wheelEvent       (QWheelEvent * event)   override;		//!< management of mouse wheel events  
    virtual void keyPressEvent    (QKeyEvent   * event)   override;		//!< management of key press events 
//@}

// ----- A n i m a t i o n    and   d r a w i n g     L O O P
/*! @name Animation and drawing loop */
//@{
	/**
	@brief  This method must be overloaded to customize the behavior of OpenGL and initialize the application.
	**/
    virtual void  init           () {}		
    virtual void  resizeGL(int width, int height) override;				//!< management of OpenGL resize 
    /**
	@brief This method must be overloaded to customize the animation loop. Inside it, you must put all the instructions to be run during an iteration of the animation loop. 
	It is called at each time step of the animation.
	**/	
	virtual void  animate        ();
	/**
	@brief This method must contains the instruction to display in 2D on the OpenGL screen. 
	It is called in /c paintGL(), a private method in charge of the drawing loop. 
	
	An example of how to use it is provided in TestViewer.cpp	
	*/
    virtual void  drawInformation();
	
	/**
	@brief This method must contains the instruction to display in 3D on the OpenGL screen. 
	It is called in /c paintGL(), a private method in charge of the drawing loop. 
	
	An example of how to use it is provided in TestViewer.cpp	
	*/	
    virtual void  drawScene();
	
	/**
	@brief Moves the camera along the axis \c dir and at the \c speed.	
	*/
            void  moveCamera( const QVector3D & dir, float speed );
     
			double getCameraSpeed() const;		//<! Return the speed of movement of the camera

	/**
	@brief This method must contains the instruction to create the diffrents object of your scene at displayed in 3D on the OpenGL screen. Inside it, you populate the pools of the application
	It is called in /c initializeGL(), a private method in charge of the drawing loop. 
	
	An example of how to use it is provided in TestViewer.cpp	
	*/	
    virtual void  createSceneEntities();
//@}

// ----- C a m e r a
/*! @name Camera */
//@{
    void        setCamera( QGLCamera * cam );       //!< Takes ownership of the cam instance to use as a camera
    QGLCamera * getCamera() const;                  //!< Return the camera of renderer
    void        setCameraRatio();                   //!< Set the ratio of the camera with the value in m of the display
//@}

// ----- G r i d   -   A x i s
/*! @name Grid and axis of world */
//@{
    void setCoordinateSystemSize( float val );		//!< Set the size of coordinate systeme at \c val.
    void drawAxis();								//!< Draw the world axis
    void drawGrid();								//!< Draw the grid
    void drawFPS();									//!< Display the fps in text on the 2D OpenGL screen.
//@}

// ----- D r a w    t e x t
/*! @name draw text */
//@{	
	/**
	@brief
	*/
   void drawText(int x, int y, const QString& text, const QColor &color, const QFont& fnt=QFont());
//@}

// ----- Key Event description
/*! @name Key Event description */
//@{
	/** 
	@brief Add the  behaviour description  \c desc associated with the shortcut \c k.
	Theses description could be display in the console. see also displayHelp().
	*/
   void addKeyEventDesc( const QString & k, const QString & desc );
   
   void displayHelp  () const;	//!< Displays the registered shortcuts on the console. To register a shortcut desciption, see also addKeyEventDesc()

	// Gestion des evenements souris
		float m_precisionStep = 1;			//!< Précision du pas de déplacement de la souris, initialisé à 1 */
//@}	


// A virer et à integrer dans le resize de la camera
    float m_ratioStereo = 1.0;

protected slots:
    void setKeyBoardGrabbingEvent(int val);

private slots:
    void _animate();
    void release ();


private :
    //   W i d g e t   C o n t a i n e r
    QWidget * m_thisWidget;
    bool      m_withKeyboardGrabEnabled = false;
    void defaultConstructor(QWidget *parent, Qt::WindowFlags flags);

    QGLCamera     *  m_camera;
    MouseManager  *  m_mouseManager;
    double           m_moveCamera = 0;

	// gestion fps
		QElapsedTimer    m_fpsTimer;
		uint             m_frameCount;
		qreal            m_fps;
		QString          m_fpsString;
		
	// Gestion animation
    QTimer           m_animationTimer;
    QElapsedTimer    m_appliTimer;
    qint64           m_lastAnimTime = 0;
    qint64           m_currentTime  = 0;

	// Gestion des dessins des axes et grille
		bool             m_drawingAxis  = true;
		bool             m_drawingGrid  = true;
		bool             m_drawingFps   = true;
		Mesh          *  m_axis         = nullptr;
		Mesh          *  m_grid         = nullptr;


	// Gestion des pools d'éléments
		QMap < QString, Geometry * >       m_geometries;
		QMap < QString, Material * >       m_materials;
		QMap < QString, Mesh     * >       m_sceneEntities;
		QMap < QString, QString>           m_keyEventDesc;

	// méthodes privées pour aider à l'encapsulation de savoir faire
		void initializeGL()                  override;
		void paintGL()                       override;

		void _drawInformation();
		void fpsCompute();

		void initKeyEvents();


    friend MouseManager;

};

#endif //WINDOW_H
