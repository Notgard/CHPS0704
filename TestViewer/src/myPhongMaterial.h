#ifndef MYPHONGMATERIAL_H
#define MYPHONGMATERIAL_H

#include "Material.h"
#include <QVector4D>
#include <QColor>

class myPhongMaterial : public Material {
public:
    myPhongMaterial( const QVector4D &ambient, const QVector4D &diffuse, const float &f );
    myPhongMaterial( const QColor    &ambient, const QColor    &diffuse, const float &f );

    QVector4D    getAmbiant() const;
    void         setAmbiant(const QVector4D &getAmbiant);

    QVector4D    getDiffuse() const;
    void         setDiffuse(const QVector4D &getDiffuse);

    float        getSpecPower() const;
    void         setSpecpower(float getSpecPower);

    void         render(const Mesh * mesh, const QGLCamera *c, const QList<PointLight> & lights ) override;

    //virtual void bindSpecific( const QGLCamera *c )  override;

private:
    QVector4D m_ambiant;
    QVector4D m_diffuse;
    float     m_specpower;
};

#endif // MYPHONGMATERIAL_H
