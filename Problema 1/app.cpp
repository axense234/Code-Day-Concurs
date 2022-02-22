#include <iostream>
// Am implementat libraria <vector> ca sa am mai multa flexibilitate cu vectorii pe care o sa ii folosesc in viitor
#include <vector>
// Am adaugat libraria <fstrea> ca sa pot sa folosesc fisiere eficient
#include <fstream>
using namespace std;

// Fisiere
ifstream in;
ofstream out;


// 1.Functie de a gasi intersectia dintre doua intervale
// ============================
vector<int> intersectieCreatie(vector<int>interval1,vector<int>interval2){
 vector<int> intersectieVector = {0, 0};
 int num;
 // Am aflat intersectia dintre cei doi vectori prin realizarea(am desenat ca sa-mi dau seama) ca daca intre varfurile primului vector avem macar un varf din al doilea vector atunci primul varf al vectorului intersectie este acel varf din al doilea vector;asa ne gandim si pentru al doilea vector
 for(num=interval1[0];num<=interval1[1];num++){
  if(num==interval2[0]) intersectieVector[0] = interval2[0];
  if(num==interval2[1]) intersectieVector[1] = interval2[1];
 }
 for(num=interval2[0];num<=interval2[1];num++){
  if(num==interval1[0]) intersectieVector[0] = interval1[0];
  if(num==interval1[1]) intersectieVector[1] = interval1[1];
 }
 return intersectieVector;
}
// ============================

// 2.Functie de reuniune a doua intervale inchise
// ============================
vector<int> reuniuneExtinsaCreatie(vector<int>interval1,vector<int>interval2){
  vector<int> reuniuneVector = {0,0};
  // M-am gandit ca reuniunea a doua intervale inchise e mereu primul varf al primului vector cu al doilea varf din al doilea vector,dar avem si niste cazuri particulare:
  // De exemplu,cand intervalele nu au elemente in comun,dar in cazul asta programul automat rezolva deoarece este o reuniune exstinsa
  // De exemplu,cand un interval il contine pe altul:
  if(interval1[0] > interval2[0] && interval1[1] < interval2[1] ){
    reuniuneVector[0]=interval1[0];
    reuniuneVector[1]=interval1[1];
  } else if(interval2[0] > interval1[0] && interval2[0] < interval1[1]){
    reuniuneVector[0]=interval2[0];
    reuniuneVector[1]=interval1[0];
  } else{
    reuniuneVector = {interval1[0],interval2[1]};
  }
  return reuniuneVector;
}
// ============================


// 3.Functia de interogare simpla
// ============================
void interogareSimpla(vector<int>interval1,vector<int>interval2,int operatie){
 vector<int> interogareSimplaVector = {0,0};
 // M-am gandit ca in cazul in care avem operatie=1,sau operatie=2 putem folosi un if statement ca sa gasim vectorul de interogare simpla si sa adaugam itemii acestuia in fisierul de iesire "iesire.out"
 // Observatie: am mai verificat si daca vectorul interogareSimplaVector are valoarea [0,0],astfel incat scriem 0 in fisierul de iesire "iesire.out" 
 if(operatie==1){
    interogareSimplaVector = intersectieCreatie(interval1,interval2);
    if(interogareSimplaVector[0] == 0 && interogareSimplaVector[1] == 0){
      out << 0 << endl;
    } else {
      out << interogareSimplaVector[0] << " " << interogareSimplaVector[1] << endl;
    }
 } else if(operatie==2){
      interogareSimplaVector = reuniuneExtinsaCreatie(interval1,interval2);
    if(interogareSimplaVector[0] == 0 && interogareSimplaVector[1] == 0){
      out << 0 << endl;
    } else {
      out << interogareSimplaVector[0] << " " << interogareSimplaVector[1] << endl;
    }
 }
}
// ============================


// 4.Functia de interogare compusa
// ============================
void interogareCompusa(int operatii){
 // Asta a fost cea mai grea functie de implementat deoarece a trebuit sa ma gandesc foarte mult ca sa fie dinamica(ca sa mearga in functie de cate operatii)
 int num3;
 // Aici am initializat vectorii pt folosire in viitor
 vector<int> intervalVector1 = {0,0};
 vector<int> intervalVector2 = {0,0};
 vector<int> operatiiVector;
 operatiiVector.reserve(operatii);
 operatiiVector.resize(operatii);
 // Aici am folost functia din libraria <vector> "reserve(n)".Aceasta functie cate iteme poate contine vectorul,in functie de n,unde n este numarul de iteme minime pt acest vector,in cazul asta n este nr de operatii deoarece vrem ca vectorul operatii sa fie dinamic
 vector<int> varSpeciala = {0,0};
 // Aici am gasit tipurile de operatii(1 sau 2) si le-am adaugat in vectorul operatii
 for(num3=1;num3<=operatii;num3++){
  in >> operatiiVector[num3-1];
 }
 // Aici am luat primii 2 vectorii
  in >> intervalVector1[0];
  in >> intervalVector1[1];
  in >> intervalVector2[0];
  in >> intervalVector2[1];
 // Aici am gasit prima operatie dintre ei si am setat acel vector rezultat la "varSpeciala" ca sa pot sa adaug un fel de sistem dinamic unde nu conteaza cati vectori am de "operat"
  if(operatiiVector[0] == 1){
    varSpeciala = intersectieCreatie(intervalVector1,intervalVector2);
  } else if(operatiiVector[0] == 2){
    varSpeciala = reuniuneExtinsaCreatie(intervalVector1,intervalVector2);
  }
  // Aici am implementat sistemul dinamic,folosing primul vector ca place holder pt fiecare vector dupa primii 2 vectori,deoarece oricum nu mai aveam ce face cu primul vector,deci ca sa salvez putina memorie si eficienta l-am folosit
  cout << operatiiVector.size() << endl;
  for(num3=2;num3<=operatiiVector.size();num3++){
    in >> intervalVector1[0];
    in >> intervalVector1[1];
    if(operatiiVector[num3-1] == 1){
     varSpeciala = intersectieCreatie(varSpeciala,intervalVector1);
    } else if(operatiiVector[num3-1] == 2){
     varSpeciala = reuniuneExtinsaCreatie(varSpeciala,intervalVector1);
    }
   }
  // Aici am adaugat vectorul final in fisierul de iesire "iesire.out" in functie daca are valoare [0,0] sau alta
  if(varSpeciala[0] == 0 && varSpeciala[1] == 0){
    out << 0 << endl;
  } else {
    out << varSpeciala[0] << " " <<  varSpeciala[1] << endl;
  }
}
// ============================


// Functia principala main,unde programul foloseste functiile de mai sus pentru a afisa in fisierul de iesire "iesire.out" cerintele cu ajutorul fisierului"intrare.in"

int main(){
    // Aici am initializat variabila tipInterogare(1 sau 2,1 pt interogare simpla si 2 pt interogare compusa ca sa imi dau seama cu ce interogare o sa lucrez in viitor)
    int tipInterogare;
    int num2;
    // Aici am initializat variabila n,unde n este numarul de interogari
    int n;
    // Am deschis fisierele(fisierul de intrare "intrare.in" si fisierul de iesire "iesire.out")
    in.open("intrare.in");
    out.open("iesire.out");
    // Din fisierul de intrare "intrare.in" am luat prima valoare
    in >> n;
    cout << n << " nr interogari" << endl;
    for(num2=1;num2<=n;num2++){
      tipInterogare = 0;
      in >> tipInterogare;
      cout << num2 << " numar loop" << endl;
      cout << tipInterogare << " tip interogare" << endl;
      // In functie de tipul de interogare,aici am folosit un if else statement ca sa pot sa folosesc functia interogareSimpla sau interogareCompusa
      if(tipInterogare == 1){
        int tipInterogare2;
        vector<int> interval_1 = {0,0};
        vector<int> interval_2 = {0,0};
        in >> tipInterogare2;
        in >> interval_1[0];
        in >> interval_1[1];
        in >> interval_2[0];
        in >> interval_2[1];
        cout << interval_1[0] << " " << interval_1[1] << endl;
        cout << interval_2[0] << " " << interval_2[1] << endl;
        interogareSimpla(interval_1,interval_2,tipInterogare2);
     }else if(tipInterogare == 2){
        int numarOperatii;
        in >> numarOperatii;
        cout << numarOperatii << " numar operatii" << endl;
        interogareCompusa(numarOperatii);
    }
   }
   // Aici am inchis fisierele(fisierul de intare "intrare.in" si fisierul de iesire "iesire.out")
   in.close();
   out.close();
}


