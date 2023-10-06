#ifndef myColorMaterial_H
#define myColorMaterial_H

#include "Material.h"

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QVector3D>
#include <QVector4D>
#include <QColor>

class myColorMaterial : public Material {
public:
    myColorMaterial( const QVector4D & col, const QString & shaderPath, char * colorName);

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
    char * color_name;
};

#endif // myColorMaterial_H
