#include "text_control.h"
#include <iostream>
#include <string>
#include <sstream>
#include <limits>
#include <algorithm>

using namespace std;

text_control::text_control(string file_name):fileName(file_name+".txt")
{

}

text_control::~text_control()
{

}


int text_control::create_file(string file_name)
{
    fstream file;


    char *cFileName = &fileName[0];//konwersja na *char => funkcja open nie przyjmuje string

    file.open( cFileName, std::ios::out);
    if(file.good()==true)
    {
        file.close();
    }
}



int text_control::print()
{
    std::fstream file;

    char *cFileName = &fileName[0];//konwersja na *char => funkcja open nie przyjmuje string


    file.open( cFileName, std::ios::in | std::ios::out );

    if( file.good() == true )
    {
        /*
        string onScreen;
        getline(file, onScreen);

        data = onScreen;

        cout << onScreen;
        */
        cout<<all_text;
        file.close();
    }

}

int text_control::load_all()
{
    std::fstream file;

    char *cFileName = &fileName[0];//konwersja na *char => funkcja open nie przyjmuje string

    file.open( cFileName, std::ios::in | std::ios::out );

    if( file.good() == true )
    {
        for( ; file.eof() == false; )
        {
            string line;

            getline( file, line );

            if( line == "" )
            {
                continue;
            }
            all_text += line;
            all_text += '\n';

        }
        file.close();
    }
}

/*
int text_control::load_line(int line_number)
{

    std::fstream file;

    char *cFileName = &fileName[0];//konwersja na *char => funkcja open nie przyjmuje string

                //cFileName
    file.open( cFileName, std::ios::in | std::ios::out | std::ios::app);

   if( file.good() == true )
    {
        for( int x=0; x<line_number; x++ )
        {
            string line;


            getline( file, line );

            if( line == "\n" && x!=0 )
            {
                file.ignore(256, '\n');
                line = "";
                continue;
            }

            //file>>a;
            std::cout<<line;

            //
            if(file.eof()==true)
            {
                return 0;
            }
        }
        file.close();
    }
}
*/
int text_control::load_line(int line_number)
{
    std::fstream file;

    char *cFileName = &fileName[0];//konwersja na *char => funkcja open nie przyjmuje string

    file.open( cFileName, std::ios::in | std::ios::out | std::ios::app);
    file.seekg(std::ios::beg);
    for(int i=0; i < line_number - 1; ++i)
    {
        file.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }
    file>>a;

    std::replace(a.begin(), a.end(), '_', ' ');

    file.close();
}

int text_control::save(string data)
{
    std::fstream file;

    char *cFileName = &fileName[0];//konwersja na *char => funkcja open nie przyjmuje string

                //cFileName
    file.open( cFileName, std::ios::in | std::ios::out | std::ios::app);
    if( file.good() == true )
    {
        file << data;
        file.close();
    }
}


int text_control::clear()
{
    std::fstream file;

    char *cFileName = &fileName[0];//konwersja na *char => funkcja open nie przyjmuje string

                //cFileName
    file.open( cFileName, std::ios::in | std::ios::out | std::ios::trunc);
    if( file.good() == true )
    {
        file.close();
    }
}

