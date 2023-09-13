/* Copyright (C) 2019 Stéphanie Prévost et Julien Gerhards- All Rights Reserved
 * This file is part of libQGLShaderViewer
 */


#ifndef MESH_H
#define MESH_H

#include "Entity.h"
#include "Geometry.h"
#include "Material.h"
#include "QGLCamera.h"


// ==============================================================
//    Mesh
// -------------
//
// Classe représentant une entité de type maillage associé à un matériel (rendu) et à une géométrie.
//
// Hérite de Entity
// Un mesh a donc une position, une taille et peut être orienté suivant son centre.
//
// Ses paramètres sont :
//  - g :  le pointeur d'une instance de Geometry
//  - m :  le pointeur d'une instance de Matéria
//  - visibility : indicateur pour la visibilité de l'objet
//
// Attention -  il s'agit uniquement d'emprunt de ces instances, cette classe n'a pas la responsabilité de les détruire.
//

/**  Entité de type maillage associé à un matériel (rendu) et à une géométrie.
 * @brief      Classe représentant une entité de type maillage associé à un matériel (rendu) et à une géométrie.
 *			 Hérite de Entity
 *				 Un mesh a donc une position, une taille et peut être orienté suivant son centre.
 *
 * Ses paramètres sont :
 *  - \c g :  le pointeur d'une instance de Geometry
 *  - \c m :  le pointeur d'une instance de Material
 *  - \c visibility : indicateur pour la visibilité de l'objet
 *
 * Attention -  il s'agit uniquement d'emprunt de ces instances, cette classe n'a pas la responsabilité de les détruire.
 *
 * @class     Mesh      Mesh.h
 * @author    S. Prévost & j. Gerhards
 * @version   1.0
 * @date      Septembre 2021
 *
 **/
class DLL_SPEC  Mesh : public Entity
{
public:
  // Attention -  uniquement emprunt des objets, pas de responsabilité de destructions
    /**
	  * @brief Build a mesh with the geometry \c and whose aspect will be the material \c m. By default the mesh will be visible when the scene is drawn.
	  * @param[in] g      The geometry of the new mesh.
	  * @param[in] m      The material to be used during the rendering.
	  * @param[in] visibility 	flag to enable visible or invisible in the scene.
	  * \attention the mesh  owns neither the geometry \c g nor the material \c m. Therefore their destruction is not its responsibility. 
	  **/
	Mesh(Geometry *g, Material *m,  bool visibility = true);
    virtual ~Mesh() {}

	/**
	  * @brief Draw the mesh in the scene illuminating by the \c lights from the camera's viewpoint \c c. 
      * @param[in] c       Camera of the scene
	  * @param[in] lights  Lights illuminating the scene
      * @param[in] m       material to be used for the rendering.
      * @note Following the flag \c m_visiility, call Material::render(...) on \c m if exists, otherwise on \c m_material.
	  **/
    virtual void render(const QGLCamera *c, const QList<PointLight> & lights = QList<PointLight>(), Material *m = nullptr );

    void toggleVisibility();			//!< swith the flag of visibility.


    void       setGeometry( Geometry * g );
    Geometry * getGeometry() const;


    void       setMaterial(Material *material);
    Material * getMaterial() const;


/// ATTRIBUTS
protected:
    Geometry    * m_geometry;			//!< Geometry template of the mesh. 
    Material    * m_material;			//!< Material template of the mesh.

public :
    bool         m_visibility = true;	//!< Flag to display or not the mesh when the scene is drawn.

};

#endif // MESH_H
