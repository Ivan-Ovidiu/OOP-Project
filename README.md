# Arcade -  OOP C++ Project

Acest proiect reprezinta un spatiu interactiv pentru jucatori unde acestia pot sa se joace jocuri si sa obtina bani virtuali cu care pot cumpara premii virtuale.

![joccc-ezgif com-video-to-gif-converter](https://github.com/user-attachments/assets/5a567b97-9992-494e-bdc8-7cdfee17896b)



# Concepte de programare orientata pe obiecte:
* Conceptul de Is-A  / Has-A aplicat pe clasele folosite ( mostenirile au sens )
* Mostenire (multipla si in diamant)
* Polimorfism
* Incapsulare
* Clase template
* Clase abstracte, interfete(singleton)
* Tratarea exceptiilor pentru validarea datelor de intrare si gestionarea erorilor
* Functii si clase virtuale
# Functionalitati principale
* Administratori:<br />
Adaugarea si stergerea salilor de jocuri<br />
Vizualizarea informatiilor confidentiale despre fiecare sala (venituri, statistici)
* Pentru Jucatori:<br />
  Jocuri de Masa:<br />
  <span>&emsp;</span>Spanzuratoarea (joc de ghicit cuvinte)<br />
  <span>&emsp;</span>X si 0 (contra calculatorului)<br />
  Jocuri de Noroc:<br />
 <span>&emsp;</span>Posibilitatea de a castiga bani virtuali<br />
 <span>&emsp;</span>Sistem de achizitionare premii (mouse, tastatura, televizor)<br />
 <span>&emsp;</span>Gestionarea balantei si a premiilor castigate<br />
# Clasa Joc
Reprezinta o baza abstracta pentru jocurile existente. Aceasta gestioneaza atribute esentiale precum numele locatiei, numarul total de locuri si locurile rezervate. Implementeaza doua interfete importante: IOInterface pentru operatii de citire/afisare si Calcule( o clasa abstracta) pentru metode de calcul.
# Clasa Jucator 
Se ocupa de administrarea informatiilor despre jucatori, incluzand:
* Balanta financiara
* Numele jucatorului
* Scorurile obtinute la diferite jocuri
* Premiile castigate
* Aceasta clasa permite jucatorilor sa-si actualizeze balanta si sa-si gestioneze premiile, avand un numar limitat de incercari (rotiri).
# Clasa TipJocDeMasa 
Este o clasa template care ofera flexibilitate pentru implementarea diferitelor tipuri de jocuri de masa. Folosind tipuri generice, aceasta clasa poate gestiona diverse elemente de joc si sisteme de scor.<br />
Programul include doua jocuri:<br />

Spanzuratoarea:<br />

* Jucatorii incearca sa ghiceasca un cuvant litera cu litera<br />
* Include reprezentari ASCII pentru desenul spanzuratorii<br />
* Gestioneaza logica jocului, inclusiv numarul de incercari si validarea cuvintelor<br />

XSi0 (X si 0): <br />

* Tabla de joc cu dimensiune dinamica<br />
* Functionalitate pentru jucarea impotriva calculatorului<br />
* Verificare automata a conditiilor de victorie<br />


# Clasele JocDeMasa si JocDeNoroc 
Extind clasa de baza Joc si implementeaza experiente diferite de joc:<br />

* Jocurile de masa se concentreaza pe abilitati si strategie<br />
* Jocurile de noroc implica pariuri si rezultate bazate pe probabilitati<br />

# Clasa SalaDeJocuri 
Integreaza toate elementele ( existand o mostenire tip diamant intre clasele Joc - JocDeMasa si JocDeNoroc - SalaDeJocuri si gestioneaza:<br />

* Contine premii disponibile si costurile acestora
* Urmarirea veniturilor
* Inregistrarile castigatorilor
* Multiple tipuri de jocuri sub acelasi label( sala de jocuri)

# Clasa MeniuInteractiv 
Este tip Singleton si ofera o interfata pentru:<br />
* Crearea si administrarea salilor de jocuri
* Accesarea diferitelor jocuri
* Gestionarea premiilor
* Vizualizarea informatiilor confidentiale despre sali
* Procesarea tranzactiilor si cumparare premii
![image](https://github.com/user-attachments/assets/b2b29812-2148-4b7d-ab33-502cb66c828b)
