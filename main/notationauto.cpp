/* notationauto.cpp
 * BOUDJEDIR Amina - 16/10/2022
 * TP2 notation Automatique 
 * */
#include<iostream>  //pour cout, cin....
#include<fstream>   //pour les fichiers

using namespace std;    //pour les cdc

//type etudiant 
struct etudiant{
    string id;
    string reponse; //chaine de caractere qui contient les notes de l'etudiant
    char note;      //la note obtenue lors du teste
};

//type teste
struct test{
    etudiant * tab;
    int nbetudiant;
    int nbquestion;
    string bonReponce;
};

//initialisation d'un tab dynamique
void init_tab(test & t, int n, int q, string bon, string t){
    t.tab = new etudiant[n];
    t.nbetudiant = n;
    t.nbquestion = q;
    t.bonReponce = t;
}

//afficher tableau
void show_tab(test  t){
    for (int i = 0; i < t.nbetudiant; i++){
        cout << "[" <<t.tab[i].id << ","<< t.tab[i].reponse << ", "<< t.tab[i].note << "]"<<endl;
    } 
}

//calculer le nb d'etudiant le nb de ligne du fichier
int nbetudiant(string nom, test t){
    string ligne;
    fstream flux;
    int nb=0;
    flux.open(nom,ios::in); //ouverture du fichier en lecture depuis le nom
    if(flux.is_open()){ //si le fichier est ouvert
        //lit une ligne non null jusqu'a l'espace
        getline(flux, ligne);
        while(getline(flux, ligne)){
            nb++;
        }
    }else{
        cout << "Erreur impossible d'ouvrir le fichier !!!" << endl;
    }
    return nb;
}

//calculer le nb de questuion dans le fichier
int nbquestion(string nom){
    int nb = 0;
    string ligne;
    fstream flux;
    flux.open(nom,ios::in); //ouverture du fichier en lecture depuis le nom
    if(flux.is_open()){ //si le fichier est ouvert
        //lit une ligne non null
        getline(flux, ligne);
        return ligne.length();
    }else{
        cout << "Erreur impossible d'ouvrir le fichier !!!" << endl;
    }
    return nb;
}

//lire les donnees du fichier 
//on prend en entree un fichier et on retourne un tableau de note et un tableau de id
void readflux(string nom,test & t){
    fstream flux;
    string ligne;
    string mat = "";
    string reponse = "";
    int i,j, q;
    j=0;
    q=0;
    flux.open(nom,ios::in); //ouverture du fichier en lecture depuis le nom
    if(flux.is_open()){ //si le fichier est ouvert
        //lit une ligne non null jusqu'a l'espace
        while(getline(flux, ligne)){
            i=0;
            mat = "";
            while(ligne.at(i) != ' '){
                mat = mat + ligne.at(i); 
                i++;
            }//fin de l'identifiant de l'etudiant
            t.tab[j].id = mat;
            i++;
            reponse = "";
            q=0;
            while(q<t.nbquestion){ //lire les reponces
                reponse = reponse + ligne.at(i);
                q++;
                i++;
            }
            t.tab[j].reponse = reponse;
            j++;
        }
    }else
        cout << "Impossible d'ouvrir le fichier !!!!" << endl;
}

//calculer la note de l'etudiant a partir de ses reponse  
// 1 bonne repense 2 points | une mauvaise reponse - 1  
int note_of_test(string answer){
    int note =0;
    for(int i=0; i<answer.length(); i++){
        if(answer.at(i) == 'T')
            note +=2;
        else if(answer.at(i) == 'F')
            note --;
    }
    return note;
}

//transformer le note en point
char point_of_test(int note, test t){
    int p;
    p = note*100/(t.nbquestion*2);
    if(p>=90 && p<=100)
        return 'A';
    else if(p>=80 && p<=89,99)
            return 'B';
            else if(p>=70 && p<=79,99)
                    return 'C';
                 else if(p>=60 && p<=69,99)
                            return 'D';
                      else  return 'F';
}
//calculer les notes de tt les etudiants
void note_of_all_test(test & t){
    for(int i=0; i<t.nbetudiant; i++){
        t.tab[i].note = point_of_test(note_of_test(t.tab[i].reponse),t);
    }
}

//afficher les notes 
void show_note(test t, string nom){
    //variables 
    fstream flux;
    flux.open(nom,ios::out); //ouverture du fichier en ecriture depuis nom
    if (flux.is_open()){
        for(int i=0; i<t.nbetudiant; i++){
           flux << "identifiant: " << t.tab[i].id <<", réponse: " << t.tab[i].reponse << ", note:" << t.tab[i].note<<endl;   //ecriture dans le fichier de sortie
        }
         flux.close();
    }
    else 
        cout << "Impossible de ouvrir le fichier en ecriture !!!!" << endl;
}


int main(){
    test t;
    string nom = "teste.txt";
    cout << " nb ="<<nbetudiant(nom,t) << endl;

   // init_tab(t,nbetudiant(nom, t),20);
   // readflux(nom, t);
    //show_tab(t);
    
    //note_of_all_test(t);
    //show_note(t,nom);

    //delete t.tab;
return 0;
}