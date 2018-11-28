/*  SPATIAL DATA HEADER
 *  ESSE ARQUIVO TERÁ TODAS AS FORMAS GEOMÉTRICAS NECESSÁRIAS NO BANCO DE DADOS
 *  OU SEJA, PONTOS, RETAS E POLIGONOS
 *  ALÉM DOS ALGORITMOS DE GEOMETRIA COMPUTACIONAL
 */
#ifndef SPATIALDATA_HPP
#define SPATIALDATA_HPP
#include <iostream>
#include <vector>
#include <list>
#include <cfloat>
#include <cmath>
#include <algorithm>
#include <QPointF>
#include "circularlist.hpp"
using namespace std;
namespace SpatialData{

/*
 * Namespace SpatialData
 * -> Contém os objetos que descrevem as formas geográficas
 */

#define PI acos(-1)
#define EPSILON2 1E-10

enum Classificadores {ESQUERDA, DIREITA, FRENTE, ATRAS, ENTRE, ORIGEM, DESTINO}; // USADO NA CLASSIFICAÇÃO
enum Rotacao {HORARIO, ANTIHORARIO}; // SENTIDO DAS ROTAÇÕES NA LISTA DUPLAMENTE ENCADEADA DE VERTICES
enum Posicao_Relativa_Retas {COLINEAR, PARALELA, CONSECUTIVO, CONSECUTIVO_CRUZADO, CONSECUTIVO_NAO_CRUZADO}; // USADA PELA POSIÇÃO RELATIVA ENTRE SEGMENTOS DE RETA (ARESTAS)
enum Posicao_Ponto_Poligono {DENTRO, FORA, FRONTEIRA};
enum Classificadores_Aresta {TOCANDO, CRUZANDO, INESSENTIAL};

class Retangulo;
class Aresta;

class Ponto{
public:
    double x, y;
    Ponto(double X = 0.0, double Y = 0.0);
    int Classificacao(Ponto&, Ponto&); // CLASSIFICA UM PONTO EM RELAÇÃO A DOIS PONTOS (RETA)
    int Classificacao(Aresta); // CLASSIFICA UM PONTO EM RELAÇÃO A UMA ARESTA
    int Orientacao(Ponto&, Ponto&, Ponto&); // RETORNA SE OS PONTOS SÃO POSITIVO, NEGATIVO OU COLINEAR
    double AnguloPolar();
    double Tamanho(); // DISTANCIA EM RELAÇÃO A ORIGEM
    double Distancia(Aresta&); // DISTANCIA EM RELAÇÃO A UMA ARESTA
    double Distancia(Ponto&); // DISTANCIA EM RELAÇÃO A OUTRO PONTO
    double GetX() const{ return x; }
    double GetY() const{ return y; }
    QPointF toQPoint();
    double operator[](int);
    friend ostream& operator<<(ostream&, const Ponto&);
};

Ponto operator+(const Ponto&, const Ponto&);
Ponto operator-(const Ponto&, const Ponto&);
Ponto operator*(double , const Ponto&);
double operator*(const Ponto&, const Ponto&);
bool operator==(const Ponto&, const Ponto&);
bool operator!=(const Ponto&, const Ponto&);
bool operator<(const Ponto&, const Ponto&);
bool operator<=(const Ponto&, const Ponto&);
bool operator>=(const Ponto&, const Ponto&);
bool operator>(const Ponto&, const Ponto&);

class Vertice: public CircularList::Node, public Ponto{
public:
    Vertice(double x, double y);
    Vertice(Ponto&);
    Vertice* Horario(); // percorre a lista em sentido horário
    Vertice* Antihorario(); // percorre a lista em sentido antihorário
    Vertice* Vizinho(int); // retorna o nó vizinho
    Ponto& GetPonto(); // RETORNA OS PONTOS DO VERTICE
    Vertice* Push(Vertice*); // COLOCA UM VERTICE NA LISTA
    Vertice* Push(Ponto);
    Vertice* Pop(); // RETIRA O VERTICE ATUAL DA LISTA
    void Splice(Vertice*); // JUNTA DUAS LISTAS
    Retangulo Envelope(); // MINIMUM BOUNDING RECTANGLE PARA A R-TREE
    Vertice* Split(Vertice*); // DIVIDE A LISTA
    pair<QPointF*, int> toQPoint(double);
    void Kai();
    double GetMin();
    friend class Poligono;
};

enum { DESCONHECIDO, P_DENTRO, Q_DENTRO };

class Poligono{
private:
    Vertice* list;
    unsigned m_size;
    void resize();
    bool fakeKai{};
public:
    Poligono(); // CONSTRUTOR PADRÃO
    Poligono(Poligono&);  // COPIA UM POLIGONO PARA ESTE OBJETO
    Poligono(Vertice*); // COPIA UMA LISTA DE VERTICES PARA ESTE OBJETO
    ~Poligono();
    Vertice* GetVertice(); // RETORNA A LISTA DE VERTICES
    unsigned GetSize(); // RETORNA O TAMANHO DA LISTA DE VERTICES
    Ponto& GetPonto(); // RETORNA O PONTO DO VERTICE ATUAL
    Aresta GetAresta(); // RETORNA A ARESTA ATUAL
    Vertice* Avancar(int); // AVANÇA NA LISTA DE VERTICE PARA O PROXIMO OU ANTERIOR
    Vertice* Horario(); // AVANÇA NA LISTA DE VERTICE
    Vertice* Antihorario(); // RETROCEDE NA LISTA DE VERTICE
    Vertice* Vizinho(int); // RETORNA O VIZINHO (ANTERIOR OU PROXIMO)
    Vertice* SetV(Vertice*); // MOVE A LISTA PARA UM DADO VERTICE
    Vertice* Push(Ponto); // COLOCA UM PONTO NA LISTA DE VERTICE POR VALOR
    //Vertice* Push(Ponto&); // COLOCA UM PONTO NA LISTA DE VERTICE POR REFERENCIA
    void Pop(); // RETIRA O VERTICE ATUAL DA LISTA
    void Resize(); // RECALCULA O TAMANHO DA LISTA (NECESSÁRIO EM TODO PUSH OU POP)
    Poligono* Split(Vertice*); // DIVIDE O POLIGONO EM RELAÇÃO A UM VERTICE
    Poligono* Interseccao(Poligono&);
    int PontoNoPoligono(Ponto&);
    double Area();
    void Apagar();
    void setFakeKai(bool);
    friend ostream& operator<<(ostream&, const Poligono&);
};

class Aresta{
private:
    Ponto origem;
    Ponto destino;
public:
    Aresta();
    Aresta(Ponto&, Ponto&);
    Aresta& Rotacao(); // ROTACIONA A RETA EM 90º NO SENTIDO HORÁRIO
    Aresta& Flip(); // ROTACIONA A RETA EM 180º NO SENTIDO HORÁRIO
    Ponto GetPonto(double&);
    Ponto GetOrigem() const;
    Ponto GetDestino() const;
    double Dist() const; // RETORNA A DISTANCIA ENTRE ORIGEM E DESTINO
    int Interseccao(Aresta&, double&); // RETORNA O PONTO DE INTERSECÇÃO ENTRE DUAS RETAS E UM F
    int Cruza(Aresta&, double&); // RETORNA SE AS RETAS SE CRUZAM
    bool isVertical();
    double Inclinacao(); // RETORNA A INCLINAÇÃO DA RETA
    double y(double); // DADO UM X, RETORNA O Y (VISTO QUE A RETA É SEMPRE INFINITA)
    int Tipo(Ponto&);
    double Angulo(Ponto&);
    double GetCoeficienteAngular();
    friend class Ponto;
    friend class Retangulo;
    friend bool operator<(const Retangulo&, const Retangulo&);
    friend bool operator>(const Retangulo&, const Retangulo&);
};

class Retangulo{
private:
    Aresta diagonal;
    double area{};
public:
    Retangulo(Ponto&, Ponto&);
    Retangulo();
    Retangulo(const Retangulo&);
    bool InterRetang(Ponto&, Ponto&, Ponto&, Ponto&); // VERIFICA SE EXISTE INTERSEÇÃO ENTREM DOIS RETANGULOS
    bool Contem(Ponto&);
    bool Contem(Retangulo&);
    double Ajusta(Retangulo&, bool&);
    double CalcularArea();
    double GetArea();
    const Aresta& GetDiagonal();
    Retangulo CresceParaConter(Retangulo&);
    bool Interseccao(Retangulo&);
    friend bool operator<(const Retangulo&, const Retangulo&);
    friend bool operator>(const Retangulo&, const Retangulo&);
    friend bool operator==(const Retangulo&, const Retangulo&);
    friend bool operator!=(const Retangulo&, const Retangulo&);
};


#pragma pack(push, 1)
class Circulo{
public:
    Ponto centro;
    double raio;
    Circulo();
    Circulo(double,Ponto);
    double Diametro();
    double Comprimento();
    double Area();
    int CirculoPoint(Ponto& ); //INTERSEÇÃO PONTO ESTA OU NÃO NO CIRCULO
    int InterCirculo( Circulo&, Circulo& );// VERIFICA SE EXISTE INTERSEÇÃO ENTRE CIRCULOS
    Vertice* PontinterCirculo( Circulo& , Circulo& ); //   PONTOS QUE INTERCEPTA DOIS CIRCULOS
    Vertice* CirculoIntRetas( Circulo& ,  Ponto& , Ponto& ); // INTERSEÇÃO CIRCULO E RETAS;
    Retangulo Envelope();

};
#pragma pack(pop)

int EsquerdaDireita(Ponto*, Ponto*);
int DireitaEsquerda(Ponto*, Ponto*);
bool aimsAt(Aresta&, Aresta&, int, int);
int crossingPoint(Aresta&, Aresta&, Ponto&);
void advance(Poligono&, Poligono&, bool);

bool operator==(const Aresta&, const Aresta&);
bool operator!=(const Aresta&, const Aresta&);
}// NAMESPACE SPATIALDATA
#endif // SPATIALDATA_HPP
