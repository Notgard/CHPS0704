/* Copyright (C) 2019 Stéphanie Prévost et Julien Gerhards- All Rights Reserved
 * This file is part of libQGLShaderViewer
 */


#ifndef ENTITY_H
#define ENTITY_H


#include <QVector3D>
#include <QMatrix4x4>
#include <QQuaternion>

#include "define.h"

// ==============================================================
//    ENTITY
// -------------
//
// Classe générique représentant une entité.
// Une entité a une position, une taille et peut être orienté suivant son centre.
// Par défaut, sa position est (0,0,0), sa taille 1 et il n'y a pas de rotation.
//

/** Classe générique représentant une entité.
 * @brief      Classe générique représentant une entité.
 *             Une entité a une position, une taille et peut être orienté suivant son centre.
 *             Par défaut, sa position est (0,0,0), sa taille 1 et il n'y a pas de rotation.
 *
 *             <h3>Usage</h3>
 *             Pour utiliser Entity, vous devez faire dériver votre classe MyEntity de Entity et
 *             surchager les méthodes virtuelles ayant un comportement différent de celui défini par défaut.
 *
 * @class Entity      Entity.h
 * @author    S. Prévost & j. Gerhards
 * @version   1.0
 * @date      Septembre 2021
 *
 **/
class DLL_SPEC Entity
{

public:
    Entity();
    virtual ~Entity() {}

/// Setters/Getters
/*! @name Setters/Getters */
//@{
    QVector3D    getPosition   () const;                        //!< Return the entity position in the world space.
    virtual void setPosition   ( const QVector3D & pos );       //!< Initialise the entity position in the world space with \c pos.

    void         setScale      ( const QVector3D & sc );        //!< Initialise the entity scale with \c sc.
    void         setScale      ( float sc );                    //!< Initialise the entity scale with \c sc (applied on the 3 dimension).

    void         setRotation   (float angle, const QVector3D &rot );    //!< Initialise the entity rotation in the world space through \c angle degrees about vector \c rot.
    void         setRotation   ( const QQuaternion & q );               //!< Initialise the entity rotation in the world space according to the specified quaternion \c q.

    QMatrix4x4   getTrans      () const;                        //!< Return the translattion matrix of the entity.
    QMatrix4x4   getScale      () const;                        //!< Return the scaling matrix of the entity.
    QMatrix4x4   getRot        () const;                        //!< Return the rotation matrix of the entity.

    /**
     * @brief Return the model matrix of the entity.
     * @return m_trans*m_rot*m_scale
     */
    QMatrix4x4   getModelMatrix() const;
    /**
     * @brief Set the model matrix of the entity with \c m. Also the matrices (m_trans, m_rot et m_scale) are modified accordingly.
     * @param m the new model matrix of the entity.
     */
    void         setModelMatrix( const QMatrix4x4 & m );        //!< Initialise the model matrix of the entity.
//@}


/// Méthodes de Manipulation
/*! @name Transformation Methods
           The transformation methods set the matrices of translation (m_trans), rotation (m_rot) and scaling (m_scale).
           @warning However, if the entity is declared frozen, then these methods will have no effect.
*/
//@{
    virtual void translate   ( const QVector3D & trans );           //!< Translate the entity of the vector \c trans.
    virtual void scale       ( const QVector3D & sc );              //!< Translate the entity of \c trans.
    virtual void scale       (float sc );                           //!< Scale the entity of \c sc on the 3 dimensions.
    virtual void rotateOnSelf( float angle, const QVector3D &rot ); //!< Rotation of the entity on itself through \c angle degrees about vector \c rot.
    virtual void rotateOnSelf( const QQuaternion & q );             //!< Rotation of the entity on itselfaccording to the specified quaternion \c q..
//@}

    virtual void print       () const;                              //!< Print on the console the entity features (position and matrices of translation, rotation and scale).


    bool getFrozen() const;                                         //!< Return the frozen indicator.
    void setFrozen(bool frozen);                                    //!< Set or unset the frozen indicator. If set, inhibits all transformation methods.

protected :
    /// Matrices de Transformation
    QMatrix4x4   m_trans;   //!< Matrice de translation
    QMatrix4x4   m_scale;   //!< Matrice de mise à l'échelle
    QMatrix4x4   m_rot;     //!< Matrice de rotation

    bool         m_frozen;  //!< Indicateur permettant de figer l'objet (if set, inhibits all transformation methods).
};

#endif // ENTITY_H


