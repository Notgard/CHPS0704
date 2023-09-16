#include "myPhongMaterial.h"
#include "Mesh.h"

myPhongMaterial::myPhongMaterial( const QVector4D &ambient, const QVector4D &diffuse, const float &f ) {
    this->m_ambiant = ambient;
    this->m_diffuse = diffuse;
    this->m_specpower = f;
}
 
void myPhongMaterial::render(const Mesh * mesh, const QGLCamera *c, const QList<PointLight> & lights ) {
    this->gl->glEnable(GL_DEPTH_TEST);
    this->m_program->bind();

    this->bindSpecific(c);
    this->bindMatrix(c, mesh->getModelMatrix());

    this->m_program->setUniformValue("lightAmbiant", this->getAmbiant());
    this->m_program->setUniformValue("lightDiffuse", this->getDiffuse());
    this->m_program->setUniformValue("lightSpecPow", this->getSpecPower());

    this->m_program->setUniformValue("cameraPosition", c->getPosition());

    for(const PointLight &light : lights) {
        this->m_program->setUniformValue("lightColor", light.getColor());
        this->m_program->setUniformValue("lightPos", light.getPosition());
    }

    mesh->getGeometry()->binds(this->attribPos, this->attribNorm, this->attribUvs, this->attribTangents);
    mesh->getGeometry()->draw();
    this->m_program->release();
}

QVector4D    myPhongMaterial::getAmbiant() const {
    return this->m_ambiant;
}

void         myPhongMaterial::setAmbiant(const QVector4D &getAmbiant) {
    this->m_ambiant = getAmbiant;
}

QVector4D    myPhongMaterial::getDiffuse() const {
    return this->m_diffuse;
}

void         myPhongMaterial::setDiffuse(const QVector4D &getDiffuse) {
    this->m_diffuse = getDiffuse;
}

float        myPhongMaterial::getSpecPower() const {
    return this->m_specpower;
}

void         myPhongMaterial::setSpecpower(float getSpecPower) {
    this->m_specpower = getSpecPower;
}
