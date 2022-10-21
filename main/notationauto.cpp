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

//afficher tableau
void show_tab(test  t){
    for (int i = 0; i < t.nbetudiant; i++){
        cout << "[" <<t.tab[i].id << ","<< t.tab[i].reponse << ", "<< t.tab[i].note << "]"<<endl;
    } 
}

//calculer le nb d'etudiant le nb de ligne du fichier
int nbetudiant(string nom){
    string ligne;
    fstream flux;
    int nb=0;
    flux.open(nom,ios::in); //ouverture du fichier en lecture depuis le nom
    if(flux.is_open()){ //si le fichier est ouvert
        //lit une ligne non null jusqu'a l'espace
        getline(flux, ligne);   //premier ligne c les reponces du teste
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
        getline(flux, ligne);   //premier ligne c les reponses juste 
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
    string mat;
    string reponse;
    int i,j, q;
    j=0;
    q=0;
    flux.open(nom,ios::in); //ouverture du fichier en lecture depuis le nom
    if(flux.is_open()){ //si le fichier est ouvert
        //lit une ligne non null jusqu'a l'espace
        getline(flux, ligne); //premiere ligne des les reponces juste du teste
        t.nbquestion = ligne.length();
        t.bonReponce = ligne;
        t.nbetudiant = nbetudiant(nom);
        t.tab = new etudiant[t.nbetudiant];
        while(getline(flux, ligne)){    //les etudiants et leurs reponses
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

//transformer le note en point
char point_of_test(int note, int nbquestion){
    int p;
    p = note*100/(nbquestion*2);
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

//calculer la note de l'etudiant a partir de ses reponse  
// 1 bonne repense 2 points | une mauvaise reponse - 1  
void note_of_all_test(test t){
    int note;
    for(int j=0; j<t.nbetudiant; j++){ //pour chaque etudiant
        note = 0;
        for(int i=0; i<t.nbquestion; i++){
            if(t.tab[j].reponse.at(i) == t.bonReponce.at(i))
                note +=2;
            else if(note>0)
                    note --;
        }
        cout << note << endl;
        t.tab[j].note = point_of_test(note, t.nbquestion);  
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

    cout << "le nombre de Question du teste est : " << nbquestion(nom)<< endl;
    cout << "le nombre d'etudiant qu'on fais le teste est : "<< nbetudiant(nom) << endl;
    readflux(nom, t);
    cout <<endl;
    cout << "affichage du tableau d'etudiant qu'on passer le teste avec leur reponse sans note " << endl;
    show_tab(t);
    
    note_of_all_test(t);
    show_note(t,nom);

    //delete t.tab;
return 0;
}