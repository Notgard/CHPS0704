/* Copyright (C) 2019 Stéphanie Prévost et Julien Gerhards- All Rights Reserved
 * This file is part of libQGLShaderViewer
 */


#ifndef COLORMATERIAL_H
#define COLORMATERIAL_H

#include "Material.h"

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QVector3D>
#include <QVector4D>
#include <QColor>


// ==============================================================
//    ColorMaterial
// -------------------
//
// Classe représentant un matériel basé sur une couleur.
// hérite de Material
//

/**  Classe représentant un matériel basé sur une couleur.
 * @brief      Classe représentant un matériel basé sur une couleur.
 *             hérite de Matérial
 *
 * @class ColorMaterial      ColorMaterial.h
 * @author    S. Prévost & j. Gerhards 
 * @version   1.0
 * @date      Septembre 2021
 *
 **/
class DLL_SPEC ColorMaterial : public Material
{
public:
    ColorMaterial( const QColor    & col);
    ColorMaterial( const QVector4D & col);
    ColorMaterial( const QColor    & col, const QString & shaderPath );
    ColorMaterial( const QVector4D & col, const QString & shaderPath );
    virtual ~ColorMaterial() override;

//    void render(Mesh *mesh, QGLCamera *c, GLenum mode = GL_TRIANGLES ) override;
	
	/**
	 * @copydoc Material::bindSpecific( const QGLCamera *c )
	 * bind the color in the shader
	**/
    virtual void bindSpecific( const QGLCamera *c )  override;

    void      setColor( const QColor & col);
    void      setColor( const QVector3D & col);
    void      setColor( const QVector4D &col);
    QVector4D getColor() const ;

protected:
    QVector4D    m_color;
};

#endif
