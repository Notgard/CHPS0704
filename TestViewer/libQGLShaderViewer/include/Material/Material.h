/* Copyright (C) 2019 Stéphanie Prévost et Julien Gerhards- All Rights Reserved
 * This file is part of libQGLShaderViewer
 */


#ifndef MATERIAL_H
#define MATERIAL_H


#include "QGLCamera.h"
#include "define.h"
#include "PointLight.h"

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QVector3D>
#include <QVector4D>
#include <QString>
#include <QList>


class Mesh;

// ==============================================================
//    Material
// -------------
//
// Classe générique et virtuelle représentant un matériel,
// qui charge des shaders.
//
//


/** Classe générique et virtuelle représentant un matériel
 * @brief 	Classe générique et virtuelle représentant un matériel et qui charge des shaders.
 *
 * @class Material	Material.h
 * @author    S. Prévost & j. Gerhards
 * @version   1.0
 * @date      Septembre 2021
 *
  \nosubgrouping 
 **/
class DLL_SPEC Material
{
public:
    Material();
    virtual ~Material();

   /**
     * @brief Render the mesh object \c m avec the camera \c c and the illuminating lights \c lights.
	 The method makes the different bindings (prog, specific of camera and matrix) before running the geometry drawing with the attrib setting \c (attribPos, attribNorm, attribUvs, attribTangents) .
	  
     * @param[in] m       Mesh to apply the material to
     * @param[in] c       Camera (QGLCamera) of the scene
	 * @param[in] lights  Lights (PointLight) illuminating the scene
     * @note called by Mesh::render(...)
			 call bindSpecific() and geometry::render(...) 
     **/    
    virtual void render(const Mesh *m, const QGLCamera *c, const QList<PointLight> & lights = QList<PointLight>() );

// ----- init shader ---
/*! @name init shader 
    @brief <em>initShader(...)</em> load the shaders, initialize the program and get the location id of attribut : \c pos  \c Norm \c uvs \c tang.
	*/
//@{
    void initShader( const QString & pathname );
    void initShader( const QString & vertexName,  const QString & geometryName, const QString & fragmentName );
//@}

/*! @name bind matrixes to the shader 
    @brief <em>bindMatrix(...) bind the matrixes of projection \c proj, model \c model and view \c view to the shader.
    */
//@{
    void bindMatrix( const QGLCamera *c, const QMatrix4x4 & model );
    void bindMatrix( const QMatrix4x4 & model, const QMatrix4x4 & view, const QMatrix4x4 & proj );
    virtual void bindSpecific(const QGLCamera *c)  = 0;
//@}

protected :
/*! @name attributs */
//@{
    QString                m_name;
    QOpenGLShaderProgram * m_program = nullptr;			//!< Pointer of the shader program
    QOpenGLFunctions      *gl = nullptr;				//!< access to OpenGL function
    GLuint                 attribPos, 					//!< id of attribut \c pos  in the shader
						   attribNorm, 					//!< id of attribut \c norm  in the shader
						   attribUvs, 					//!< id of attribut \c uvs  in the shader
						   attribTangents;				//!< id of attribut \c tang  in the shader
//@}
};

#endif // MATERIAL_H
