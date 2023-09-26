#ifndef MYPHONGMATERIAL_H
#define MYPHONGMATERIAL_H

#include "Material.h"

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QVector3D>
#include <QVector4D>
#include <QColor>

#include "glTexture.h"

class myPhongMaterial : public Material {
public:
    myPhongMaterial(QVector4D const &ambient, QVector4D const &diffuse, float const &f );

    QVector4D    getAmbiant() const;
    void         setAmbiant(const QVector4D &getAmbiant);

    QVector4D    getDiffuse() const;
    void         setDiffuse(const QVector4D &getDiffuse);

    float        getSpecPower() const;
    void         setSpecpower(float getSpecPower);

    void         render(const Mesh * mesh, const QGLCamera *c, const QList<PointLight> & lights ) override;
    virtual void bindSpecific( const QGLCamera *c )  override;

private:
    QVector4D m_ambiant;
    QVector4D m_diffuse;
    float     m_specpower;
    glTexture * diff_map;
    glTexture * specexponent;
    glTexture * specstrength;
    glTexture * normal_map;
};

#endif // MYPHONGMATERIAL_H
