#include "myPhongMaterial.h"
#include "Mesh.h"


myPhongMaterial::myPhongMaterial(QVector4D const &ambient, QVector4D const &diffuse, float const &f ) {
    this->m_ambiant = ambient;
    this->m_diffuse = diffuse;
    this->m_specpower = f;
    //créer les différentes textures contenant les coefficient du modèle phong à envoyer au fragment shader
    this->diff_map = new glTexture("./data/Textures/diffuse.jpg");
    this->specexponent = new glTexture("./data/Textures/specexponent.jpg");
    this->specstrength = new glTexture("./data/Textures/specstrength.jpg");
    this->normal_map = new glTexture("./data/Textures/normal.jpg");
    //initialiser les shaders
    initShader(QString("./data/myPhongMaterial/"));
}
 
void myPhongMaterial::render(const Mesh * mesh, const QGLCamera *c, const QList<PointLight> & lights ) {
    this->gl->glEnable(GL_DEPTH_TEST);
    this->m_program->bind();

    this->bindSpecific(c);
    this->bindMatrix(c, mesh->getModelMatrix());

    //bind diffuse texture map to channel 0
    this->gl->glActiveTexture(GL_TEXTURE0);
    this->diff_map->bind();
    this->m_program->setUniformValue("diff_map", 0);

    //bind specular exponent texture map to channel 1
    this->gl->glActiveTexture(GL_TEXTURE1);
    this->diff_map->bind();
    this->m_program->setUniformValue("specex_map", 1);

    //bind specular strength texture map to channel 2
    this->gl->glActiveTexture(GL_TEXTURE2);
    this->specstrength->bind();
    this->m_program->setUniformValue("specstr_map", 2);

    //bind the object normal texture map to channel 3
    this->gl->glActiveTexture(GL_TEXTURE3);
    this->normal_map->bind();
    this->m_program->setUniformValue("obj_normal", 3);

    //send the information about the light and phong coefficients to the fragmet shader
    this->m_program->setUniformValue("lightAmbiant", this->getAmbiant());
    this->m_program->setUniformValue("lightDiffuse", this->getDiffuse());
    this->m_program->setUniformValue("lightSpecPow", this->getSpecPower());
    //ajouter la position de la camera dans le fragment shader
    this->m_program->setUniformValue("cameraPosition", c->getPosition());

    //ajouter la couleur et la position de chaque lumière dans la scène (une par une). 
    //Le shader ne gène pour le moment que pour une seult source de lumière
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

void myPhongMaterial::bindSpecific( const QGLCamera *c )  {
    Q_UNUSED(c);
}
