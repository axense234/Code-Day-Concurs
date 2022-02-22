// Librariile folosite
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

// Fisierele
ifstream in;
ofstream out;

// Functia calculeazaSuma
// ============================
// Argumente:
// 1.int cateNr are mereu valoare lui i3
// 2.vector<int> capacitate este doar vectorul toateNumerele doar cu un nume diferit
// 3.int sumaNoua este suma precedata pe care o adaugam cu urmatorul element din vector
int CalculeazaSuma(int cateNr,vector<int> capacitate,int sumaNoua){
 int sum;
 sum = sumaNoua + capacitate[cateNr-1]; 
 return sum;
}
// ============================

// Functia sortare grupa(care sorteaza grupe in mod dinamic)
// ============================
 int sortareGrupa(vector<int> grupa){
 vector <int> numereDistincte;
 int numarElementeDistincte = 0;
 // Presupunem ca nr e distinct din start
 int nrDistinct = 0;
  for(int i = 1;i<=grupa.size();i++){
   // Am luat valoare elementului vectorului de pozitie [i-1] si i-am atribuito variabilei element
   int element = grupa[i - 1];
   nrDistinct = 0;
   // Daca elementul e in intervalul [0,100] atunci putem lucra cu el
   if(element >= 0 && element <=100){
    for(int i2 = 1;i2<=grupa.size();i2++){
     if(grupa[i2-1] == element){
      nrDistinct++;
     }
    }
    // Daca elementul nu a avut nici o replica atunci il adaugam in vectorul numereDistincte
    if(nrDistinct == 1){
     numereDistincte.reserve(i);
     numereDistincte.resize(i);
     numereDistincte[i - 1] = element;
    }
   }
  }
  // Numara elementele vectorului care nu sunt egal cu zero si nu exista copii
  int cifraElement;
  for(int i = 1;i<=numereDistincte.size();i++){
    if(numereDistincte[i-1] == 0){
      continue;
    } else {
      cout << numereDistincte[i-1] << endl;
      numarElementeDistincte++;
    }
  }
  return numarElementeDistincte;
}
// ============================

int main(){
 // Variabilele folosite de program:
 // min_s = minimum sumei
 // max_c1,max_c2,max_c3 = numeraul de iteratii,variabila care tine nr max al unei iteratii,variabila care contine rezultatul
 // cifra,element,i si suma sunt variabile ajutatoare
 int min_s,max_c1=0,max_c2=0,max_c3=0,cifra,element,i=1,suma;
 vector<int> toateNumerele;

 in.open("intrare.in");
 out.open("iesire.out");

 // Aici am deschis documentul,am citit fiecare element din fisierul de intrare "intrare.in",am initializat suma minima la cel mai mic element din elementele fisierului
 while(!in.eof()){
  in >> element;
  if(min_s > element){
   min_s = element;
  }
  //                 1.PRIMA CERINTA
  // ====================================================
  // Aici am inceput sa creez vectorul cu toate numerele pe care le-am citit din fisierul de intrare "intrare.in".In primul rand am rezervat loc in vector (1) ca sa-l modific,folosing reserve(i) si resize(i) (2) unde i creste de fiecare data cand se citeste un element din fisierul de intrare.Am adaugat elementele fisierului in vector folosind acest i.(3)
  toateNumerele.reserve(i); // 1
  toateNumerele.resize(i); // 2
  toateNumerele[i-1] = element; // 3
  i++;
 }
 // Aici am inceput sa parcurg vectorul toateNumerele ca sa gasesc suma minima din toate posibilitatile de suma din vector.
 for(int i2 = 1;i2 <= toateNumerele.size();i2++){
   // Aici am inceput sa parcurg sumele posibile ale adunarilor elementelor din vectorul toateNumerele,incepand cu pozitia elementului egala cu valoarea i3
   for(int i3 = i2;i3 <= toateNumerele.size();i3++){
    suma = CalculeazaSuma(i3,toateNumerele,suma);
    // Daca suma calculata este mai mica decat suma minima,aceea suma devine noua suma minima
    if(suma < min_s){
     min_s = suma;
    }
   }
   // Aici de fiecare data cand am schimbat pozitia initiala de calculare a posibilitatilor sumelor vectorului am resetat suma
   suma = 0;
 }
  // ====================================================
  //                 2.A DOUA CERINTA
  // ====================================================
 for(int p=1;p<=toateNumerele.size();p++){
  max_c1 = 0;
  if(toateNumerele[p-1] >=0 && toateNumerele[p-1] <=9){
   cifra = toateNumerele[p-1];
   for(int p2 = p;p2<=toateNumerele.size();p2++){
    if(toateNumerele[p2-1] >=0 && toateNumerele[p2-1] <=9){
     if(toateNumerele[p2 - 1] == cifra){
      max_c1++;
     } else {
     }
     max_c2 = max_c1;
    }
   }
   max_c2 = max_c1;
   if(max_c2 > max_c3) max_c3 = max_c2;
  }
 }
 // ====================================================
 //             3.A TREIA CERINTA
 // ====================================================
 //  Aici impartim vectorul "mama" toateNumerele daca capacitatea lui este mai mare decat 100(daca nu vectorul "mama" devine vectorul grupa pt functia sortareGrupa)
 int numarElementeDistincteMAX1 = 0;
 int numarElementeDistincteMAX2 = 0;
 if(toateNumerele.size() < 100){
   numarElementeDistincteMAX2 = sortareGrupa(toateNumerele);
 } else if(toateNumerele.size() > 100){
   for(int i = 1;i <=floor(toateNumerele.size()/100) + 1;i++){
    // Am creat un vector care o sa contina primele 100 numere din vectorul mama toateNumerele
    // O variabila care ne ajuta sa ne dam seama de la cat sa inceapa i ca sa scrie elemente in vectorul grupaSmechera
    int numarator = 1;
    int numarator2 = 100;
    int ultimaGrupaCapacitate = floor(toateNumerele.size()%100);
    // cout << ultimaGrupaCapacitate << endl;
    vector<int> grupaSmechera;
    // Vectorul o sa aiba capacitatea maxima de 100 de numere
    grupaSmechera.reserve(100);
    grupaSmechera.resize(100);
    // Am adaugat elementele vectorului grupaSmechera
    int iGrupa = 1;
    for(int i = numarator;i <= numarator2;i++){
      grupaSmechera[iGrupa - 1] = toateNumerele[i - 1];
      iGrupa ++ ;
      numarElementeDistincteMAX1= sortareGrupa(grupaSmechera);
      if(numarElementeDistincteMAX1 >= numarElementeDistincteMAX2){
        numarElementeDistincteMAX2 = numarElementeDistincteMAX1;
      }
    }
    // In functie de marimea vectorului,am schimbat dinamic valoarea variabilei numarator si numarator2 astfel incat de fiecare data vectorul grupaSmechera reprezinta o grupa
    if(grupaSmechera.size() > 100){
        numarator2 = numarator2 + 100;
        if(numarator < 100){
          numarator = numarator + 99;
        } else if(numarator > 100){
          numarator = numarator + 100;
        }
    } else if(grupaSmechera.size() < 100){
        numarator2 = ultimaGrupaCapacitate;
    }
   }
 }
 // Aici afisez min_s,max_c3 si numarElementeDistince,rezultatul la primul subpunct,al doilea subpunt si al treilea subpunct
 out << min_s << " ";
 out << max_c3 << " ";
 out << numarElementeDistincteMAX2 << endl;

 
}