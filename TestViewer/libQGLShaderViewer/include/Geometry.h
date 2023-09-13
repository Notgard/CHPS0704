/* Copyright (C) 2019 Stéphanie Prévost et Julien Gerhards- All Rights Reserved
 * This file is part of libQGLShaderViewer
 */


#ifndef GEOMETRY_H
#define GEOMETRY_H


#include "glm/glm.hpp"

#include <vector>
#include <QOpenGLBuffer>
#include <QString>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLContext>
#include <QOpenGLFunctions>

#include <QVector3D>

#include "define.h"



struct Face
{
    unsigned int s1,s2,s3;
};

// ==============================================================
//    Geometry
// -------------
//
// Classe représentant la description géométrique d'un maillage triangulaire (sans information de texture ou de couleur).
//
// Ses paramètres sont :
//  - modelpath        : nom du fichier contenant le mesh
//  - withShift2Center : recentre le mesh en son centre.
//  * @file      Geometry.h
/** Description géométrique d'un maillage triangulaire.
 * @brief      Classe représentant la description géométrique d'un maillage triangulaire (sans information de texture ou de couleur).
 *             Ses paramètres sont :
                - \c modelPath        : nom du fichier contenant le mesh
                - \c withShift2Center : recentre le mesh en son centre.
 *
 *             <h3>Usage</h3>
 *             Pour utiliser Geometry, vous devez faire dériver votre classe MyGeometry de Geometry et
 *             surcharger les méthodes virtuelles ayant un comportement différent de celui défini par défaut.
 * 
 * @class     Geometry 		Geometry.h
 * @author    S. Prévost & j. Gerhards
 * @version   1.0
 * @date      Septembre 2021
 */
class DLL_SPEC Geometry
{
public:
    Geometry  (const QString & modelpath ="" , bool withShift2Center = true);
    ~Geometry ();


/*! @name Getters/Setters of the descriptive QOpenGLBuffer */
//@{
    QOpenGLBuffer * vertexbuffer() const;
    void            setVertexbuffer(QOpenGLBuffer *vertexbuffer);

    QOpenGLBuffer * normal() const;
    void            setNormal(QOpenGLBuffer *normal);

    QOpenGLBuffer * uv() const;
    void            setUv(QOpenGLBuffer *uv);

    QOpenGLBuffer *indicebuffer() const;
    void           setIndicebuffer(QOpenGLBuffer *indicebuffer);

    QOpenGLBuffer *tangentesbuffer() const;
    void           setTangentesbuffer(QOpenGLBuffer *tangentesbuffer);

    QOpenGLBuffer *colorbuffer() const;
    void           setColorbuffer(QOpenGLBuffer *colorbuffer);
//@}


/*! @name Binding of the descriptive QOpenGLBuffer */
//@{
    /**
     * @brief Binds the shader attributes passed as parameters.
     * @param[in] attribPos          Id of the attribut <em>pos</em>.
     * @param[in] attribNorm         Id of the attribut <em>norm</em>.
     * @param[in] attribUvs          Id of the attribut <em>uvs</em>.
     * @param[in] attribTang         Id of the attribut <em>tang</em>.
     * @note call bindVertices( attribPos ), bindNormals ( attribNorm ), bindTextures( attribUvs ) and bindTangents( attribTang );
     */    
	void binds        ( GLuint attribPos, GLuint attribNorm, GLuint attribUvs , GLuint attribTang);
	
   /**
     * @brief Binds the Vertex Array.
     * @param[in] attrib             Id of the attribut <em>pos</em>.
     * @note called by binds( attribPos, attribNorm, attribUvs, attribTang );
     */    
    void bindVertices ( GLuint attrib );
   /**
     * @brief Binds the Normals Array.
     * @param[in] attrib             Id of the attribut <em>norm</em>.
     * @note called by binds( attribPos, attribNorm, attribUvs, attribTang );
     */    
    void bindNormals  ( GLuint attrib );
    /**
     * @brief Binds the texture Array.
     * @param[in] attrib             Id of the attribut <em>uvs</em>.
     * @note called by binds( attribPos, attribNorm, attribUvs, attribTang );
     */    
    void bindTextures ( GLuint attrib );
   /**
     * @brief Binds the Tangent Array.
     * @param[in] attrib             Id of the attribut <em>norm</em>.
     * @note called by binds( attribPos, attribNorm, attribUvs, attribTang );
     */    
    void bindTangents ( GLuint attrib );
   /**
     * @brief Binds the Color Array.
     * @param[in] attrib             Id of the attribut <em></em>.
     */    
    void bindColors   ( GLuint attrib );
//@}


/*! @name ??? */
//@{
    void draw         ();                   //!< Draw the geometry in OpenGL with m_drawingMode, the drawing mode.

    QVector3D  getCenter     () const;      //!< Return the center of the geometry (a 3D point)
    /**
     * @brief Search the extrema 3D points of the geometry bounding box. The result is set in the params.
     * @param leftBottomCorner      3D point at the bottom left corner of the bounding box.
     * @param rightUpCorner         3D point at the up right corner of the bounding box.
     */
    void       getBoundingBox( QVector3D & leftBottomCorner, QVector3D & rightUpCorner ) const;
    void       shift2Center  ();					//!< Realignment and recentering of the geometry
//@}

/*! @name Structural variables (differentes lists) */
//@{
    std::vector < glm::vec3 >  listVertex;          //!< Liste des points
    std::vector < Face      >  listFaces;           //!< Liste des faces (regroupant de 3 sommets)
    std::vector < Face      >  listCoordFaces;      //!< Liste des coord textures des faces
    std::vector < glm::vec3 >  listNormals;         //!< Liste des normales
    std::vector < glm::vec3 >  listCoords;          //!< Liste des coords
    std::vector < glm::vec4 >  listTangents;        //!< Liste des tangentes
    std::vector < glm::vec4 >  listColors;          //!< Liste des couleurs (rgba)
    int                        nb_vertex;           //!< Nombre de sommets
    int                        nb_faces;            //!< Nombre de faces
//@}

    QOpenGLBuffer * main() const;                   //!< Buffer grouping the others descrptive buffers.


protected :
    void createOpenGLBuffers(bool withShift2Center = true);	//!< Create the OpenGL buffers to the shader (vertex, normal, texture, indice, tangente and color)

    GLenum m_drawingMode = GL_TRIANGLES;                    //!< Drawing mode of the geometry used in draw().

private:
    QOpenGLBuffer   *  m_main            = nullptr;
    QOpenGLBuffer   *  m_vertexbuffer    = nullptr;
    QOpenGLBuffer   *  m_normal          = nullptr;
    QOpenGLBuffer   *  m_uv              = nullptr;
    QOpenGLBuffer   *  m_indicebuffer    = nullptr;
    QOpenGLBuffer   *  m_tangentesbuffer = nullptr;
    QOpenGLBuffer   *  m_colorBuffer     = nullptr;
//    bool               isUV;
//    bool               isNormal;

    QOpenGLFunctions * gl;

};
#endif // GEOMETRY_H
