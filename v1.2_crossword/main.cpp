#include <SFML/Graphics.hpp>
#include "text_control.h"
#include <sstream>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>
#include <windows.h>
#include <random>

using namespace std;
using namespace sf;

int fileLength = 3; //ABY LOSOWANIA DZIALALY DOBRZE NALEZY TO ZMIENIC NA ILOSC WERSÓW W PLIKACH

vector <int> v_numbers; //vector przechowuj¹cy losowe liczby

void shuffle(int[],int);

void shuffle(int values[], int size) {
	// Seed our random number generator.
	srand((int)time(NULL));

	// Create large number of swaps
	// This example takes the size and times it by 20 for the number of swaps
	for (int i = 0; i < (size * 20); i++) {
		// Generate random values for subscripts, not values!
		int randvalue1 = (rand() % size) + 0;
		int randvalue2 = (rand() % size) + 0;

		int temp = values[randvalue1];
		values[randvalue1] = values[randvalue2];
		values[randvalue2] = temp;
	}
}

void random(int maximum) //tworzy tablice z randomowymi cyframi od 1 do ilosc linii
{
    int min=1;
    int max=maximum;


	int range = (max - min);

	// Create our new array of size "range"
	int *values = new int[range];

	// Load some counting values into our array
	for (int i = 0; i <= range; i++) {
		values[i] = min + i;
	}

	// Now shuffle the array values randomly.
	shuffle(values,range + 1);

	// Spit out the values



	for (int i = 0; i <= range; i++) {
        v_numbers.push_back(values[i]);
		//cout << "Next random value: " << values[i] << endl;
	}
}


string title;
string def;
//vectory z definicajmi i tytulami
vector < string > v_def;
vector < string > v_title;


int control=0;
int load() // rekurencyjna funkcja ladujaca definicje i tytuly z plikow
{

    text_control f_def("def");      //tworzy obiekt klasy to w nawiasie to nazwa pliku
    text_control f_title("title");



    f_def.load_line(v_numbers[control]+1);  //laduje konkretna linie z pliku
    f_title.load_line(v_numbers[control]+1);

    def = f_def.a;
    title = f_title.a;

    /*
    cout<<v_numbers[control]<<endl;
    cout<<def<<" -> "<<title<<endl;
    //*/
    v_def.push_back(def);
    v_title.push_back(title);


    if(v_numbers.size()-1==control)
    {
        return 0;
    }
    else
    {
        control++;
        load();
    }
}
    int _x=10;
    int _y=_x;
    vector<vector<string> > v_board( _x , vector<string> (_y, "."));


vector<int> tab_pos;
vector<int> tab_xy;

void rand_xy()
{
    srand(time(NULL));
    int seed = rand();

    for(int i=0;i<10;i++)
    {
        for(int q=0;q<10;q++)
        {
            tab_xy.push_back(i);
        }
    }

    shuffle(tab_xy.begin(), tab_xy.end(), std::default_random_engine(seed));

}
void rand_pos()
{
    srand(time(NULL));
    int seed = rand();

    for(int i=0;i<25;i++)
    {
        tab_pos.push_back(1);
    }
    for(int i=0;i<25;i++)
    {
        tab_pos.push_back(2);
    }
    shuffle (tab_pos.begin(), tab_pos.end(), std::default_random_engine(seed));

}

void insert_into_board()
{

    for(int i=0;i<1/*v_title.size()*/;i++)
    {
        string title = v_title[i];
        rand_xy();
        rand_pos();
        int x_rand = tab_xy[i];
        int y_rand = tab_xy[i+1];

        int pos = tab_pos[i];
        switch(pos)
        {
        case 1:
            {
                cout<<"x: "<<x_rand<<" y: "<<y_rand<<" pos: horizontal "<<title<<": "<<title.size()<<endl;
                break;
            }
        case 2:
            {
                cout<<"x: "<<x_rand<<" y: "<<y_rand<<" pos: vertical "<<title<<": "<<title.size()<<endl;
                break;
            }
        }

        for(int i=0; i<title.size();i++)
        {
            switch(pos)
            {
            case 2: //vertical [x][0]
                {
                    //v_board[i+y_rand][x_rand] = title[i];
                    if(title.size()+y_rand>10)
                    {
                        y_rand -= title.size();
                        v_board[i+y_rand][x_rand] = title[i];
                    }
                    else
                    {
                        v_board[i+y_rand][x_rand] = title[i];
                    }
                    break;
                }
            case 1: //horizontal [0][y]
                {
                    //v_board[y_rand][i+x_rand] = title[i];

                    if(title.size()+x_rand>10)
                    {
                        x_rand -= title.size();
                        v_board[y_rand][i+x_rand] = title[i];
                    }
                    else
                    {
                        v_board[y_rand][i+x_rand] = title[i];
                    }
                    break;
                }
            }


            //v_board[i][0] = title[i];
        }
    }

}

void draw_2d_board()
{
    insert_into_board();
    cout<<"   ====================="<<endl;


    for (int x = 0; x < _x; x++) {
            cout<<"   |";
        for (int y = 0; y < _y; y++){
            cout<< v_board[x][y]<< "|";
        }
        cout<< "\n";
    }
    cout<<"   ====================="<<endl;

}




int g_width = 505;
int g_height = 505;


int main()
{
    //init start

    sf::RenderWindow window(sf::VideoMode(g_width, g_height), "Crossword");


    //init end

    random(fileLength);

    //load text start
    load();

    //load text end

    //font
    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        std::cout<<"Error\n";
    }


    //board start
    vector<RectangleShape> mesh_y; //0 0001101

    int x=50;
    for (int i=0; i<10; i++)
    {
            RectangleShape line;
            line.setSize(Vector2f(5, 500)); //w and h
            line.setFillColor(Color::Black);
            line.setPosition(x,0);
            mesh_y.push_back(line);
            x+=50;
    }

    vector <RectangleShape> mesh_x;
    int y=50;
    for (int i=0; i<10; i++)
    {
            RectangleShape line;
            line.setSize(Vector2f(500, 5)); //w and h
            line.setFillColor(Color::Black);
            line.setPosition(0,y);
            mesh_x.push_back(line);
            y+=50;
    }


    vector <RectangleShape> outline_x;
    vector <RectangleShape> outline_y;
    x=0;
    y=0;
    for(int i=0;i<2;i++)
    {
        RectangleShape line;
        line.setSize(Vector2f(505, 5)); //w and h
        line.setFillColor(Color::Red);
        line.setPosition(0,y);
        outline_x.push_back(line);
        y=+g_width-5;
    }
    for(int i=0;i<2;i++)
    {
        RectangleShape line;
        line.setSize(Vector2f(5, 505)); //w and h
        line.setFillColor(Color::Red);
        line.setPosition(x,0);
        outline_y.push_back(line);
        x=+g_height-5;
    }
    /*
    cout<<"MESH Y\n";
    for (int i=0; i<10; i++)
    {
        cout<<"x: "<<mesh_y[i].getPosition().x<<" y:"<<mesh_y[i].getPosition().y<<endl;
    }
    cout<<"MESH X\n";
    for (int i=0; i<10; i++)
    {
        cout<<"x: "<<mesh_x[i].getPosition().x<<" y:"<<mesh_x[i].getPosition().y<<endl;
    }
    cout<<"OUTLINE X\n";
    for (int i=0; i<2; i++)
    {
        cout<<"x: "<<outline_x[i].getPosition().x<<" y:"<<outline_x[i].getPosition().y<<endl;
    }
    cout<<"OUTLINE Y\n";
    for (int i=0; i<2; i++)
    {
        cout<<"x: "<<outline_y[i].getPosition().x<<" y:"<<outline_y[i].getPosition().y<<endl;
    }
    */
    //board end


    //game mechanics start


    // Displaying the 2D vector
    draw_2d_board();
    //game mechanics end


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if( sf::Keyboard::isKeyPressed( sf::Keyboard::Escape ) )
        {
            window.close();
        }
        if( sf::Keyboard::isKeyPressed( sf::Keyboard::Num1 ) )
        {
            draw_2d_board();
        }
        if( sf::Keyboard::isKeyPressed( sf::Keyboard::Num2 ) )
        {
        }

        window.clear(Color(128, 128, 128));

        for(int x=0;x<10;x++)
        {
           window.draw(mesh_y[x]);
        }
        for(int x=0;x<10;x++)
        {
           window.draw(mesh_x[x]);
        }

        for(int x=0;x<2;x++)
        {
           window.draw(outline_x[x]);
        }
        for(int x=0;x<2;x++)
        {
           window.draw(outline_y[x]);
        }
        window.display();
    }

    return 0;
}
