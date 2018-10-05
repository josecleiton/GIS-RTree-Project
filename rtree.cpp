#include "rtree.hpp"
#include "insertwindow.hpp"
using namespace SpatialIndex;

Chave::Chave(Retangulo& _mbr, size_t _dado): MBR(_mbr), Dado(_dado){
}

Chave::Chave(Retangulo& _mbr, Node* ptr): MBR(_mbr), ChildPointer(ptr){

}

Node::Node(int nivel, int count): m_Nivel(nivel), m_Count(count){

}

RTree::RTree(): raiz(nullptr){
}

void RTree::Push(){
}