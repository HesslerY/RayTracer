#include "Ambiente.hpp"

Ambiente::Ambiente()
{
}

Ambiente::~Ambiente()
{
	delete(this);
}

colvec3 Ambiente::iluminar(Objeto * const objeto, Raio * const raio, int indiceObj)
{

	colvec3 vetorUnitL, vetorUnitH, cor, corDifusa, corSpecular;

	corDifusa << 0 << 0 << 0;
	corSpecular << 0 << 0 << 0;

	Objeto *objetoProx = NULL;

	bool sombra = false;

	colvec3 pontoColisao;

	for (int posLuz = 0; posLuz < luzes_.size(); posLuz++) {
		pontoColisao = raio->getOrigem() + (raio->getVetorDiretor()) * (raio->getDistanciaAnterior());

		sombra = false;

		double distanciaLampPonto;
		colvec3 pLuz;
		pLuz = luzes_[posLuz]->getPosicao();

		distanciaLampPonto = sqrt(pow(pontoColisao[0] - pLuz[0], 2) + 
									pow(pontoColisao[1] - pLuz[1], 2) +
									pow(pontoColisao[2] -pLuz[2], 2));
	
		raioLuz->setOrigem(pontoColisao);
		raioLuz->setDirecao(luzes_[posLuz]->getPosicao());
		raioLuz->setDistanciaAnterior(distanciaLampPonto);
		raioLuz->setDistanciaColisao(0);

		for (int indObj = 0; indObj < objetos_.size(); indObj++) {

			if (indiceObj != indObj) {//&*objeto != &*modelos_[indObj]

				objetoProx = objetos_[indObj]->colide(raioLuz);

				if (objetoProx != NULL) {
					if (raioLuz->getDistanciaColisao() > 0.00001 && raioLuz->getDistanciaColisao() < distanciaLampPonto) {
						sombra = true;
						break;
					}
				}
			}

		}

		raio->setPontoColisao(pontoColisao);

		if (!sombra) {
			colvec3 intLumi, vecNormal;
			intLumi = luzes_[posLuz]->getIntensLuminosa();

			vecNormal = objeto->getVetorNormal(raio);

			vetorUnitL = normalise(luzes_[posLuz]->getPosicao() - pontoColisao);
			vetorUnitH = normalise((raio->getOrigem() - raio->getDirecao()) + vetorUnitL);
			corDifusa += (objeto->getCorDifusa() % intLumi) * max(0.0, dot(vecNormal, (vetorUnitL)));
			corSpecular += (objeto->getCorSpecular() % (intLumi)* pow(max(0.0, dot(vecNormal, vetorUnitH)), objeto->getCoefBrilho()));

		}
	}

	cor = (corAmbiente_%intensLuminosa_) + corDifusa + corSpecular;

	for (int i = 0;i < 3; i++) {
		if (cor[i] > 255) {
			cor[i] = 255;
		}
		else if (cor[i] < 0) {
			cor[i] = 0;
		}

	}

	return cor;
}

void Ambiente::lerAmbiente(char * const nomeArq)
{
	FILE *arqCena = fopen(nomeArq, "r");
	char linha[64];
	vector<Luz*>luzes;
	colvec3 intLumi, pos;
	colvec3 cor;

	vector<Objeto*> objetos;

	int numLampadas = 0;

	while (fgets(linha, sizeof(linha), arqCena)) {

		switch (linha[0]) {
		case 't'://Tamanho
			sscanf(linha, "%*s %d %d", &largura_, &altura_);
			cout << "Tamanho: " << largura_ << "x" << altura_ << endl;
			break;
		case 'l'://Luz
			sscanf(linha, "%*s %lf %lf %lf/%lf %lf %lf", &pos[0], &pos[1], &pos[2], &intLumi[0], &intLumi[1], &intLumi[2]);
			pos[0] *= -1;
			luzes_.push_back(new Luz(pos, intLumi));//				luzes_.push_back(new Luz(pos, intLumi));
			numLampadas++;
			break;
		case 'a'://Ambiente
			sscanf(linha, "%*s %lf %lf %lf/%lf %lf %lf", &cor[0], &cor[1], &cor[2], &intLumi[0], &intLumi[1], &intLumi[2]);
			corAmbiente_ = cor;
			intensLuminosa_ = intLumi;
			break;
		case 'c'://Camera
			sscanf(linha, "%*s %lf %lf %lf", &pos[0], &pos[1], &pos[2]);
			camera_ = pos;
			break;
		case 'o'://Arquivo Objeto
			char nomeArquivoObjetos[64], nomeArquivoMateriais[64];

			sscanf(linha, "%*s %s %s", nomeArquivoObjetos, nomeArquivoMateriais);

			cout << " [OBJ] " << nomeArquivoObjetos << " [MAT] " << nomeArquivoMateriais << endl;

			objetos = lerObjetos(nomeArquivoObjetos, nomeArquivoMateriais);

			objetos_.insert(objetos_.end(), objetos.begin(), objetos.end());

			break;
		}
	}

	fclose(arqCena);

	cout << "Lampadas: " << numLampadas << endl;
}

map<string, Material*> Ambiente::lerMateriais(char * const nomeArquivoMateriais)
{
	char linha[256], tipo[16];
	colvec3 corDifusa, corSpecular;
	char nome[32];
	Material *material = NULL;
	map<string, Material*> materiais;

	FILE *arquivoMateriais;
	arquivoMateriais = fopen(nomeArquivoMateriais, "r");

	while (fgets(linha, sizeof(linha), arquivoMateriais)) {

		sscanf(linha, "%s ", tipo);

		if (strcmp(tipo, "newmtl") == 0) {
			sscanf(linha, "%*s %s", nome);
			material = new Material();
			materiais[nome] = material;
		}
		else if (strcmp(tipo, "Kd") == 0) {
			sscanf(linha, "%*s %lf %lf %lf", &corDifusa[0], &corDifusa[1], &corDifusa[2]);
			corDifusa[0] *= 255;
			corDifusa[1] *= 255;
			corDifusa[2] *= 255;
			material->getCorDifusa() = corDifusa;
		}
		else if (strcmp(tipo, "Ks") == 0) {
			sscanf(linha, "%*s %lf %lf %lf", &corSpecular[0], &corSpecular[1], &corSpecular[2]);


			corSpecular[0] *= 255;
			corSpecular[1] *= 255;
			corSpecular[2] *= 255;

			material->getCorSpecular() = corSpecular;
		}
	}
	cout << "Material para [ " << nomeArquivoMateriais << "] lido";

	fclose(arquivoMateriais);

	return materiais;
}

vector<Objeto*> Ambiente::lerObjetos(char * const nomeArquivoObjetos, char * const nomeArquivoMateriais)
{
	char linha[256], tipo[16];

	vector<Objeto*> objetos;
	colvec3 vertice, vertA, vertB, vertC, kd, ks;
	mat vertices;
	Objeto *objeto;
	Triangulo *face;

	FILE *arquivoObjetos, *arquivoMateriais;

	arquivoObjetos = fopen(nomeArquivoObjetos, "r");

	kd << 0.0 << 0.366 * 255 << 0.113 * 255;
	ks << 0.131 * 255 << 1.0 * 255 << 0.474 * 255;

	int qtdVertices = 0;
	int vert1, vert2, vert3, vetNorm;

	map<string, Material*> materiais;
	map<string, Material*>::iterator itMateriais;

	//materiais = lerMateriais(nomeArquivoMateriais);

	Material* material;

	char nomeMaterial[32];
	int numFaces = 0;

	double raio;
	colvec3 centro;

	while (fgets(linha, sizeof(linha), arquivoObjetos)) {

		sscanf(linha, "%s ", tipo);

		if (strcmp(tipo, "o") == 0) {
			objeto = new Modelo();
			objetos.push_back(objeto);
		}
		else if (strcmp(tipo, "esf") == 0) {
			sscanf(linha, "%*s %lf/%lf %lf %lf", &raio, &centro[0], &centro[1], &centro[2]);
			//objeto = new Esfera();
			//objeto->material_ = material;

			//Esfera *esfera = static_cast<Esfera*>(objeto);

			//centro[0] *= -1;

			//centro << -3  << - 1 << 10;

			//Esfera *esfera = new Esfera(2, centro);
			//esfera->coefBrilho_ = 5;

			//esfera->corDifusa_ = material->corDifusa_;
			//esfera->corSpecular_ = material->corSpecular_;

			//esfera->corDifusa_ << 59 << 86 << 125;
			//esfera->corSpecular_ << 98 << 115 << 84;


			default_random_engine gerador;
			uniform_int_distribution<int> distY(-8, 8);
			uniform_int_distribution<int> distX(-8, 8);
			uniform_int_distribution<int> distZ(3, 8);
			uniform_int_distribution<int> distRaio(0.5, 1);
			uniform_int_distribution<int> distCor(0, 255);

			colvec3 kd, ks;

			for (uint32_t i = 0; i < 300; ++i) {
				centro[0] = distX(gerador);
				centro[1] = distY(gerador);
				centro[2] = distZ(gerador);
				raio = distRaio(gerador);

				Esfera *esf;
				esf = new Esfera(raio, centro);

				esf->setCoefBrilho(1000);


				kd << distRaio(gerador) << distCor(gerador) << distCor(gerador);

				ks << distRaio(gerador) << distCor(gerador) << distCor(gerador);

				esf->setCorDifusa(kd);
				esf->setCorSpecular(ks);

				objetos.push_back(esf);

			}

			cout << "Esfera Lida\n";

		}
		else if (strcmp(tipo, "tri") == 0) {

			Triangulo * triangulo;

			if (qtdVertices == 3) {
				vertA = vertices.col(qtdVertices - 3);
				vertB = vertices.col(qtdVertices - 2);
				vertC = vertices.col(qtdVertices - 1);

				cout << vertA << endl;
				cout << vertB << endl;
				cout << vertC << endl;

				triangulo = new Triangulo(vertA, vertB, vertC);

				/*
				triangulo->corDifusa_ = material->corDifusa_;
				triangulo->corSpecular_ = material->corSpecular_;*/

				triangulo->setCorDifusa(kd);
				triangulo->setCorSpecular(ks);

				triangulo->setCoefBrilho(10000);

				qtdVertices = 0;

				objetos.push_back(triangulo);

				cout << "Triangulo Lido";

			}
			//objeto->material_ = material;

			//objetos.push_back(objeto);
		}
		else if (strcmp(tipo, "v") == 0) {
			sscanf(linha, "%*s %lf %lf %lf", &vertice[0], &vertice[1], &vertice[2]);
			vertices.insert_cols(qtdVertices, vertice);
			qtdVertices++;

		}
		else if (strcmp(tipo, "usemtl") == 0) {
			/*
			sscanf(linha, "%*s %s", nomeMaterial);
			itMateriais = materiais.find(nomeMaterial);

			if ((itMateriais != materiais.end())) {
			material = itMateriais->second;
			}
			material = new Material();

			material->corDifusa_ = kd;
			material->corSpecular_ = ks;
			*/
		}
		else if (strcmp(tipo, "f") == 0) {
			sscanf(linha, "%*s %d//%d %d//%d %d//%d", &vert1, &vetNorm, &vert2, &vetNorm, &vert3, &vetNorm);

			vertA = vertices.col(vert1 - 1);
			vertB = vertices.col(vert2 - 1);
			vertC = vertices.col(vert3 - 1);

			face = new Triangulo(vertA, vertB, vertC);

			/*																		   //face->material_ = material;
			face->corDifusa_ = material->corDifusa_;
			face->corSpecular_ = material->corSpecular_;*/


			face->setCorDifusa(kd);
			face->setCorSpecular(ks);
			face->setCoefBrilho(10);

			//modelo = (Modelo) 

			Modelo *modelo = static_cast<Modelo*> (objeto);

			modelo->addFace(face);

			numFaces++;
		}

	}

	//fclose(arquivoMateriais);
	//fclose(arquivoObjetos);

	cout << "Objetos: " << objetos.size() << endl;
	cout << "Faces: " << numFaces << endl;

	return objetos;
}

int Ambiente::getAltura()
{
	return altura_;
}

int Ambiente::getLargura()
{
	return largura_;
}

colvec3 Ambiente::getCorAmbiente()
{
	return corAmbiente_;
}

colvec3 Ambiente::getCamera()
{
	return camera_;
}

Objeto * Ambiente::getObjeto(int pos)
{
	return objetos_.at(pos);
}

int Ambiente::getNumObjetos()
{
	return objetos_.size();
}
