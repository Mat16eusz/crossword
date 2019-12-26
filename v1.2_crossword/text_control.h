#ifndef TEXT_CONTROL_H
#define TEXT_CONTROL_H
#include <fstream>
#include <string>
using namespace std;


class text_control
{
    public:
        string fileName;
        string data;
        string all_text;
        string a;



        text_control();//(string file_name);
        text_control(string file_name);
        ~text_control();


        int create_file(string file_name); //uzywamy w przypadku gdy nie mamy pliku (uzycie tego na istniejacym pliku usunie jego zawartosc
        int open_file(string file_name);   //uzywamy w przypadku posiadania gotowego pliku
        int save(string data);  //zapisuje do pliku wpisane przez nas dane
        int print(); //wyswietla
        int clear(); //czysci caly plik
        int convert(string var);//konwersja z string na int potrzebna w wypadku odczytywania liczb z pliku
        int zaladuj(int line);

        int load_all(); //wczytuje do zmiennej caly plik
        int load_line(int line_number); // W tym miejscu mozna zmienic zeby wczytywac tekst do zmiennych, oraz wczytaj konkretna linie tekstu






};

#endif // TEXT_CONTROL_H
