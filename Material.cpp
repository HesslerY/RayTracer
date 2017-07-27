#include "Material.hpp"

Material::Material() {

}

Material::Material(colvec3 corDifusa, colvec3 corSpecular)
{
	corDifusa_ = corDifusa;
	corSpecular_ = corSpecular;
}

Material::~Material()
{
	delete(this);
}

colvec Material::getCorDifusa()
{
	return corDifusa_;
}

colvec3 Material::getCorSpecular()
{
	return corSpecular_;
}
