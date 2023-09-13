/* Copyright (C) 2019 Stéphanie Prévost et Julien Gerhards- All Rights Reserved
 * This file is part of libQGLShaderViewer
 */


#ifndef QGLCAMERA_H
#define QGLCAMERA_H


#include "Entity.h"
#include "define.h"

#include <QMatrix4x4>
#include <QVector2D>
#include <QSizeF>


// ==============================================================
//    QGLCamera
// -------------
//
// Classe représentant une caméra.
// Sa matrice de projection est défini avec les paramètres d'une matrice de perspective, à savoir afov, ratio, near, far.
//
// Ses paramètres sont :
//  - \c w, \c h : Taille de la fenetre OpenGL (en pixel)
//

/** Classe représentant une caméra.
 * @brief      Classe représentant une caméra.
 *            Sa matrice de projection est défini avec les paramètres d'une matrice de perspective, à savoir afov, ratio, near, far.
 *	  Ses paramètres sont :
 *    - \c w, \c h : Taille de la fenêtre OpenGL (en pixel)
 *
 * @class     QGLCamera      QGLCamera.h
 * @author    S. Prévost & j. Gerhards
 * @version   1.0
 * @date      Septembre 2021
 * 
 **/
class DLL_SPEC QGLCamera : public Entity
{
public:
    static const double deg2rad;
    static const double rad2deg;

    QGLCamera();                                                                        // 4/3 45° pos(0,0,10), center(0,0,0), upY
    QGLCamera( float w, float h );
///    QGLCamera( float ratio );
    virtual ~QGLCamera() override;

    void setView( const QVector3D & pos, const QVector3D & up, const QVector3D & center );  // lookat define,

// ---- Getters / Setters
/*! @name Getters / Setters*/
//@{	
    virtual QVector2D  getViewportRatio   () const     { return QVector2D(1.0,1.0); }
    virtual QMatrix4x4 getViewMatrix      () const;
    virtual QMatrix4x4 getProjectionMatrix() const;

    QVector3D  getUpDir()    const;

    QVector3D  getLeftDir      ()  const;                //!< return the Direction from the camera : left
    QVector3D  getRightDir     ()  const;                //!< return the Direction from the camera : right
    QVector3D  getFrontDir     ()  const;                //!< return the Direction from the camera : front
    QVector3D  getviewDirection() const;                 //!< return the Direction from the camera : view

    double     getVerticalFieldOfViewAngleInRadian  () const;	//!< return the vertical FOV angle  in radian 
    double     getHorizontalFieldOfViewAngleInRadian() const;	//!< return the horizontal FOV angle  in radian 
    double     getVerticalFieldOfViewAngleInDegre   () const;	//!< return the vertical FOV angle  in degre 
    double     getHorizontalFieldOfViewAngleInDegre () const;	//!< return the horizontal FOV angle  in degre 

    void       setFocalLength  ( double val );            // inner focal length : distance between the position and the near plane
    double     getFocalLength  () const;
    QVector3D  getCenter       () const;
    float      getNear         () const;
    float      getFar          () const;
    void       setNearAndFar   ( float znear, float zfar );

    float      getRatio        () const;                  //!< return the ratio = w/h in pixel or other metric
    void       setRatio        (float value);
    void       setRatio        (float width, float height);

    void       setUpDirAndCenter       ( const QVector3D & up, const QVector3D & center  );
    void       setAFOVverticalInDegre  ( float val );
    virtual void  setAFOVverticalInRad    ( float val );
    void       setAFOVhozizontalInRad  ( double val );

    void       setPerspectiveProjection(float fovInDeg, float ratio, float znear, float zfar);
    void       setViewMatrix           ( const QVector3D & pos,  const QVector3D & center,  const QVector3D & up);

    QMatrix4x4 getSceneModelMatrix     () const;
    void       setSceneModelMatrix     (const QMatrix4x4 &sceneModelMatrix);

    QSizeF     getScreenSize           () const;
    void       setScreenSize           (const QSizeF &screenSize);

    float      getImagePlaneDistance   () const;
//@}


// ---- Méthodes de Manipulation
/*! @name Transformation Methods */
//@{
    virtual void setPosition      ( const QVector3D & pos )             override;
    virtual void translate        ( const QVector3D & trans )           override;
    virtual void rotateOnSelf     ( float angle, const QVector3D &rot ) override;
    virtual void rotateOnSelf     ( const QQuaternion & q  ) override;

    virtual void rotate           ( const QPoint & ref, const QPoint & p );
    virtual void travelling       (float speed );
    virtual void move             (float speed );
    virtual void setPositionAndKeepCenter ( const QVector3D & pos );

    float        getSceneRadius() const;
    virtual void setSceneRadius( qreal r );     //!< Appel FitSphere avec le centre courant

    void         fitSphere(const QVector3D& center, qreal radius);  //!< Bouge la position de la camera
//@}


    virtual void print() const override;




protected :
    QSizeF     m_screenSize;    // Taille de l'écran en pixel
    float      m_ratio;         // Ratio de la fenetre de rendu = W/H
    float      m_near;          // de la pyramide de vision
    float      m_far;           // de la pyramide de vision
    float      m_afov_v;        // angle du field of view vertical en degré
    float      m_viewportCoef;

    float      m_sceneRadius;   // rayon de la scene observée
//    QVector3D m_sceneCenter;    // Centre de la scene

    QMatrix4x4 m_proj;          // Matrice de projection
    QMatrix4x4 m_view;          // Matrice view
    QMatrix4x4 m_sceneModelMatrix;  // Matrice modele de la scene globale

    virtual void  updateViewMatrix();
    virtual void  updateProjectionMatrix();
    virtual void  updateSceneRadius(qreal r );


protected :
    //float      m_distance2Image;


};

#endif // QGLCAMERA_H
