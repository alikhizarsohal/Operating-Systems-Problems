#include	<iostream>
#include	<cstdlib>
#include	<string>
#include	<fstream>
#include	<unistd.h>
#include	<stdlib.h>
#include	<sys/wait.h>
#include	<sys/types.h>
#include	<pthread.h>
#include	<fstream>
#include	<SFML/Graphics.hpp>
#include	<ctime>

using namespace std;
using namespace sf;

int players=0;
struct player{

		int position[2];
		int score;
		int p_num;
	};
player *players_Array;
int totAl_plAyers_rows;

int count_number(){
	srand(time(0));
	int rn = rand() % 90 + 10;
	rn *= 4;
	int roll_number = (514 / rn) % 25;
	if(roll_number < 10){roll_number += 15; }
	cout<<"Grid will be "<<roll_number <<" * "<<roll_number <<'\n';
//	int n=0;
//	cin>>n;
	return roll_number;
}

int random_number_generator(int n){

	return rand()% n+1;
}

char** game_board(int n){

	char** arr=new char*[n];
	for(int i=0;i<n;i++)
		{
			arr[i]=new char[n];
		}
	for(int i=0;i<n;i++)
		{
			for(int j=0;j<n;j++)
				{
					arr[i][j]='-';
				}
		}
	
	srand(time(NULL));
	int random_number=n*2;

	for(int i=0;i<random_number;)
		{
			int n1 = random_number_generator(n);
			int n2 = random_number_generator(n);
			if(n1<n && n2<n){
			arr[n1][n2]='$';
			i++;
			}	
		}

	int number_of_players=2;
	players=number_of_players;
	players_Array=new player[players];

	for(int i=0;i<number_of_players;i++)
		{
			bool f=0;
			int p1=0,p2=0;
			while(!f)
				{
					p1=random_number_generator(n);
					p2=random_number_generator(n);
					if(p1<n && p2<n && arr[p1][p2]=='-')
					f=1;
				}
					string str=to_string(i+1);
					arr[p1][p2]=str[0];

					players_Array[i].position[0]=p1;
					players_Array[i].position[1]=p2;
					players_Array[i].score=0;
					players_Array[i].p_num=i+1;
		}
		return arr;
}

void displAy_gAme_boArd(char **arr,int n){	
		
	for(int i=0;i<n;i++)
		{
			for(int j=0;j<n;j++)
				{
					cout<<arr[i][j]<<' ';
				}
					cout<<"      "<<'\n';
		}
}


sf::RenderWindow window(sf::VideoMode(1100, 900), "Lucky Dollars");




void* plAy_gAme(void* pr){
Font font;
		  	  if (!font.loadFromFile("Diskontented.ttf"))
				{
		   	     		return 0;
		   	 	}
	
	player* p=(player*)pr;
	int key=0;
			char c=0;
			cout<<"Player-" << p->p_num << ':';
//			cin>>c;

	sf::Text text("", font, 20);
     text.setFillColor(sf::Color::White);
     text.setPosition(10, 10);
	  sf::Event event;
	bool b=0;
	while(window.isOpen() && !b)
		{
		        while (window.pollEvent(event))
		        {
				  bool f=0;
		            if (event.type == sf::Event::Closed)
		                window.close();
		
		            if (event.type == sf::Event::KeyPressed)
		            {
		                int k = event.key.code;
		                std::cout << "Key code: " << k<< std::endl;
		                text.setString(std::to_string(k));
					 b=1;
		          




			if(k == 71 || k == 0)
//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
					{ 
						if(k == 0)
						{
							if(p->p_num==1)
								{
			
									int i = p->position[0];
									int j=-1;
									if(p->position[1] != 0){
									    j = p->position[1] - 1;}
									if(j!=-1 && p->position[1] < totAl_plAyers_rows && j < totAl_plAyers_rows)
										{
											p->position[1]=j;
											f=1;
										}
								
								}
							else 
								{
		//							b=0;	
								}
						}
						else if(k == 71)
						{
							if( p->p_num == 2)
								{					
									int i = p->position[0];
									int j=-1;
									if(p->position[1] != 0){
									    j = p->position[1] - 1;}
									if(j!=-1 && p->position[1] < totAl_plAyers_rows && j < totAl_plAyers_rows)
										{
											p->position[1]=j;
											f=1;
										}
								}
							else 
								{
		//							b=0;
								}
						}
					}
				else if(k == 74 || k == 18) 
//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))   
					{
						if(k == 18)
						{
							if(p->p_num==1)
								{
									int i = p->position[0] + 1;
									int j = p->position[1];
									if(p->position[0]<totAl_plAyers_rows && i<totAl_plAyers_rows)
										{
											p->position[0] = i;
											f = 1;
										}
								
								}
							else 
								{
		//							b=0;	
								}
						}
						else if(k == 74)
						{
							if( p->p_num == 2)
								{					
									int i = p->position[0] + 1;
									int j = p->position[1];
									if(p->position[0]<totAl_plAyers_rows && i<totAl_plAyers_rows)
										{
											p->position[0] = i;
											f = 1;
										}
								}
							else 
								{
		//							b=0;
								}
						}
									
					}
				else if(k == 72 || k == 3)
// if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
					{
						if(k == 3)
						{
							if(p->p_num==1)
								{
									int i = p->position[0];
									int j = p->position[1] + 1;
									if(p->position[1]<totAl_plAyers_rows && j<totAl_plAyers_rows) 
										{
											p->position[1]=j;
											f=1;
										}
								
								}
							else 
								{
		//							b=0;	
								}
						}
						else if(k == 72)
						{
							if( p->p_num == 2)
								{	
									int i = p->position[0];
									int j = p->position[1] + 1;
									if(p->position[1]<totAl_plAyers_rows && j<totAl_plAyers_rows) 
										{
											p->position[1]=j;
											f=1;
										}
								}
							else 
								{
		//							b=0;
								}
						}
					}
				else if(k == 73 || k == 22)
//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) 
					{
						if(k == 22)
						{
							if(p->p_num==1)
								{
									int i=-1;
									if(p->position[0] != 0){
									    i = p->position[0] - 1;}
									int j = p->position[1];
									if(i!=-1 && p->position[0] < totAl_plAyers_rows && i < totAl_plAyers_rows)
										{
											p->position[0] = i;
											f = 1;
										}
								
								}
							else 
								{
		//							b=0;	
								}
						}
						else if(k == 73)
						{
							if( p->p_num == 2)
								{	
									int i=-1;
									if(p->position[0] != 0){
									    i = p->position[0] - 1;}
									int j = p->position[1];
									if(i!=-1 && p->position[0] < totAl_plAyers_rows && i < totAl_plAyers_rows)
										{
											p->position[0] = i;
											f = 1;
										}
								}
							else 
								{
		//							b=0;
								}
						}
									
					}
				else
					{
						cout<<"Invalid choice\n";
					}	
  				}
		        }
//		        window.clear(sf::Color::Black);
//		        window.draw(text);
//		        window.display();
		}



	player* retpr=new player;
	retpr=p;
	return (void*)retpr;
}
int score_checker(char** arr,int n){
	
	int count=0;
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++)
				{
					if(arr[i][j] == '$')
						++count;
				}
		}
	return count;
}

void drAw_A(sf::Font& fontt,char**arr,int n,player pr,int pnumber) {
    sf::Text t;
    t.setFont(fontt);
    t.setCharacterSize(50);
    t.setFillColor(sf::Color::White);
    t.setStyle(sf::Text::Bold);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
if(arr[i][j] == '$')
{
   sf::Color gold(255, 215, 0); t.setFillColor(gold);
}
else if(arr[i][j] == '1')
{
    t.setFillColor(sf::Color::Red);
}
else if(arr[i][j] == '2')
{
    t.setFillColor(sf::Color::Blue);
}
else
{
	t.setFillColor(sf::Color::White);
}
            t.setString(arr[i][j]);
            t.setPosition((j) * 36, (i) * 36);
            window.draw(t);
        }
    }
}





bool initiAl_gAme()
{


				sf::Font font;
		  	  if (!font.loadFromFile("Diskontented.ttf"))
				{
		   	     		return 1;
		   	 	}
 
	int n=count_number();
	char** arr=game_board(n);
	displAy_gAme_boArd(arr,n);
	int count = score_checker(arr,n) , temp_count=0;
	totAl_plAyers_rows=n;
	bool finishh=0;
	while(window.isOpen() && !finishh){
	do{
		for(int i=0;i<2;i++)
			{
				if(temp_count == count)
					break;
				void* status;
				player temp=players_Array[i];
				player* pr=new player;
				pr = &players_Array[i];
				pthread_t id1;



						window.clear(sf::Color::Black);
						drAw_A(font,arr,n,players_Array[i],i+1);
						window.display();


					pthread_create(&id1,NULL,plAy_gAme,(void*)pr);
					pthread_join(id1,&status);
					player* retdt=new player;
					retdt=(player*)status;
					char ch=arr[retdt->position[0]][retdt->position[1]];
					bool copy=0;
					for(int k=0;k<2;k++)
					{
						if(retdt->p_num != players_Array[k].p_num)
							{
								if(retdt->position[0] == players_Array[k].position[0]
					 			&&	retdt->position[1] == players_Array[k].position[1])
									{cout<<"\n------\n";	copy=1;break;}
							}
					}//cout<<copy
					if(ch == '$')
					{
						players_Array[i].score += 5;
						++temp_count;
					} 
					if(		(ch) 
					  )
						{
							if(!copy)
								{
									arr[temp.position[0]][temp.position[1]]='-';
									players_Array[i].position[0]=retdt->position[0];
									players_Array[i].position[1]=retdt->position[1];
									string st=to_string(retdt->p_num);
									arr[retdt->position[0]][retdt->position[1]] = st[0];
								}
							else
								{
									players_Array[i].score-=5;
									players_Array[i].position[0]=temp.position[0];
									players_Array[i].position[1]=temp.position[1];
								}
							system("clear");
								for(int cs=0;cs<2;cs++)
									{
										cout<<"Player-"<<cs+1<<"_Score="<<players_Array[cs].score<<'\n';
									}
						int prev=i;
							displAy_gAme_boArd(arr,n);
							cout<<'\n';
						}
			}
	}while(temp_count!=count);
	finishh=1;
}
	int size = 2;
	int* Arr=new int[size];	
		for(int i=0;i<size;i++)
			{
				Arr[i]=players_Array[i].score;
			}
	int max = Arr[0];
	int index = 0;
    		for (int i = 1; i < size; i++) 
			{
       			 if (Arr[i] > max) 
				  	{
            					max = Arr[i];
							index=i;
        			  	}
    			}
	
	cout<<"			Winner is Player-"<<index+1<<"		\n\n";
	return 1;
}


Text write_text(string st,int s,sf::Color clr, sf::Vector2f pos,sf::Font& fn)
{
	sf::Text n1(st, fn, s);
    	n1.setFillColor(clr);
    	n1.setPosition(pos);
	return n1;
}

void addText(sf::RenderWindow& w, sf::Font& font, std::string text, int size, sf::Color color, sf::Vector2f position) {
   



    // Check if mouse cursor is over the text object
    
}
bool textr(Texture& t)
{
	 if (!t.loadFromFile("g.jpg")) {
		        return 1;		}return 0;
}

bool stArt_menu()
{
		
		    Font ft;
		    if (!ft.loadFromFile("Diskontented.ttf")) {
		        return 1;
		    }
		RenderWindow w(sf::VideoMode(1100, 900), "Lucky Dollars");
		Texture t;
		textr(t);
		Sprite s(t);
		    s.setOrigin(0,0);
		    s.setPosition(250,110);
		
		    while (w.isOpen()) {
		        sf::Event event;
		        while (w.pollEvent(event)) {
		            if (event.type == sf::Event::Closed) {
		                w.close();
		            }
		        }
		
		        w.clear();
		        w.draw(s);



			    Vector2i ms = sf::Mouse::getPosition(w);
			Text t1 = write_text("New Game",50,Color::White,Vector2f(472,110),ft);
			    w.draw(t1);
//			Text t2 = write_text("Features",34,Color::White,Vector2f(514,180),ft);
//    			    w.draw(t2);
			bool textt=0;
			FloatRect tb = t1.getGlobalBounds();
			    if (tb.contains(ms.x, ms.y)) {
			        // Check if left mouse button is clicked
			        if (Mouse::isButtonPressed(Mouse::Left)) {
			            w.close();
					initiAl_gAme();textt=1;
			            w.close();
			        }
			    }
/*		if(!textt){
					tb = t2.getGlobalBounds();
			    if (tb.contains(ms.x, ms.y)) {
			        // Check if left mouse button is clicked
			        if (Mouse::isButtonPressed(Mouse::Left)) {
			            w.close();
						RenderWindow wn(sf::VideoMode(1100, 900), "Features");
						Text t2 = write_text("Features",34,Color::White,Vector2f(514,180),ft);
				//		wn.close();
    				    			wn.draw(t2);
							wn.display();
						
			            w.close();
			        }
			    }     //      sf::Vector2f(11, 11));
			}

*/





		        w.display();
		    }
			return 1;
		
}


int main(){

	stArt_menu();
//	initiAl_gAme();
	return 0;
}