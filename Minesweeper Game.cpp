# include <SFML\Graphics.hpp>
# include <Windows.h>
# include <iostream>
# include <string>
# include<time.h>
using namespace std;
class beginner 
{
private:
	sf::RenderWindow window;
	sf::Texture tilesTexture;
	sf::Texture flagTexture;
	sf::Texture mineTexture;
	sf::Texture smileyTexture;
	sf::Texture exitTexture;
	sf::Sprite exitSprite;
	sf::Sprite tilesSprite;
	sf::Sprite flagSprite;
	sf::Sprite mineSprite;
	sf::Sprite smileySprite;
	int cell_size;
	int grid[10][10];
	int show_grid[10][10];
public:
	beginner()
	{
		srand(time(0));
		window.create(sf::VideoMode(320,320),"Minesweeper Game");
		cell_size=32;
	}
	void textures()
	{
		tilesTexture.loadFromFile("tiles.png");
		flagTexture.loadFromFile("flag.png");
		mineTexture.loadFromFile("mine.png");
		smileyTexture.loadFromFile("smiley.png");
		tilesSprite.setTexture(tilesTexture);
		flagSprite.setTexture(flagTexture);
		mineSprite.setTexture(mineTexture);
		mineSprite.setPosition(50.f,50.f);
		smileySprite.setTexture(smileyTexture);
	}
	void draw_smiley()
	{
		smileySprite.setPosition(160,0);
		smileySprite.setScale(1.25,1.25);
		window.draw(smileySprite);
	}
	void scattered_mines()
	{
	for(int i = 1; i<=9; i++)
	{
        for (int j = 1; j <=9; j++)
		{
            show_grid[i][j] = 10;

            if (rand() % 5 == 0) 
			{
				grid[i][j] = 9;
				window.draw(mineSprite);
			}
            else 
				grid[i][j] = 0;
        }
	}
	}
	void draw_grid()
	{
		for (int i=1;i<=9;i++)
		{
			for(int j=1;j<=9;j++)
			{
				int count=0;
				if(grid[i][j]==9)
					continue;
				if (grid[i+1][j]==9)
					count++;
				if(grid[i][j+1]==9)
					count++;
				if(grid[i-1][j]==9)
					count++;
				if(grid[i][j-1]==9)
					count++;
				if (grid[i+1][j+1]==9)
					count++;
				if(grid[i-1][j-1]==9)
					count++;
				if(grid[i-1][j+1]==9)
					count++;
				if(grid[i+1][j-1]==9)
					count++;
				grid[i][j]=count;
			}
		}
	}
	void gameOver_message()
	{
		sf::RenderWindow box(sf::VideoMode(300,300),"Game Over");
		sf::Texture loseTexture;
		sf::Sprite loseSprite;
		loseTexture.loadFromFile("lose.png");
		loseSprite.setTexture(loseTexture);
		loseSprite.setScale(1,1);
		loseSprite.setPosition(60,100);
		while(box.isOpen())
							 {
								 sf::Event evnt;
								 while(box.pollEvent(evnt))
								 {
									 if(evnt.type==evnt.Closed)
									 {
										 box.close();
									 }
								 }
								 box.clear(sf::Color::Yellow);
								 box.draw(loseSprite);
								 box.display();
								 window.close();
							 }
	}
	 void exit()
	 {
	exitTexture.loadFromFile("exit.png");
	exitSprite.setTexture(exitTexture);
	exitSprite.setPosition(240,0);
	exitSprite.setScale(1,1);
	window.draw(exitSprite);
}
    void Mouse_control()
{
	bool game_over=false;
    sf::Event evnt;
    while (window.pollEvent(evnt))
    {
        if (evnt.type == evnt.Closed)
        {
            window.close();
        }
        else if (evnt.type == sf::Event::MouseButtonPressed)
        {
            int x = sf::Mouse::getPosition(window).x / cell_size;
            int y = sf::Mouse::getPosition(window).y / cell_size;
                if (evnt.mouseButton.button == sf::Mouse::Left)
                {
					if(grid[y][x]==9)
					{
						game_over=true;
						for (int i = 0; i < 9; i++)
                    {
                        for (int j = 0; j < 9; j++)
                        {
							if (grid[i][j] == 9)
                            {
                                show_grid[i][j] = 9;
                            }
                        }
                    }
				gameOver_message();
					}
				else
				{
                    show_grid[y][x] = grid[y][x];
				}
				}
                else if (evnt.mouseButton.button == sf::Mouse::Right)
                {
					show_grid[y][x] = 11;
					flagSprite.setPosition(x * cell_size, y * cell_size);
					window.draw(flagSprite);
                }
	}
        else if (evnt.type == sf::Event::MouseButtonReleased)
        {
		}
    }
	exit_clicked();
	smiley_clicked();
	}
    void display()
{
    window.clear();
    for (int i = 0; i <= 9; i++)
    {
        for (int j = 0; j <= 9; j++)
        {
            if (show_grid[i][j] == 9)
            {
                show_grid[i][j] = grid[i][j];
            }
            tilesSprite.setTextureRect(sf::IntRect(show_grid[i][j] * cell_size, 0, cell_size, cell_size));
            tilesSprite.setPosition(j * cell_size, i * cell_size);
            window.draw(tilesSprite);
        }
    }
	draw_smiley();
	exit();
    window.display();
}
	void exit_clicked()
{
	sf::Event evnt;
			while(window.pollEvent(evnt))
		{
			if(evnt.type==evnt.Closed)
			{
				window.close();
			}
			else if (evnt.type==sf::Event::MouseButtonPressed)
			{
				if(evnt.mouseButton.button==sf::Mouse::Left)
				{ 
					sf::Vector2i m =sf::Mouse::getPosition(window);
					sf::FloatRect exit_bounds=exitSprite.getGlobalBounds();
					if(exit_bounds.contains(m.x,m.y))
					{
						window.close();
					}
				}
			}
			}
}
    void smiley_clicked()
{
	sf::Event evnt;
			while(window.pollEvent(evnt))
		{
			if(evnt.type==evnt.Closed)
			{
				window.close();
			}
			else if (evnt.type==sf::Event::MouseButtonPressed)
			{
				if(evnt.mouseButton.button==sf::Mouse::Left)
				{ 
					sf::Vector2i m =sf::Mouse::getPosition(window);
					sf::FloatRect smiley_bounds=smileySprite.getGlobalBounds();
					if(smiley_bounds.contains(m.x,m.y))
					{
						textures(); 
						scattered_mines();
						draw_grid();
						while(window.isOpen())
						{
							Mouse_control();
							display();
						}
					}
				}
			}
			}
}
    void game()
	{
		textures();
		scattered_mines();
		draw_grid();
		while(window.isOpen())
		{
			Mouse_control();
			display();
		}
   }
};
class expert 
{
private:
	sf::RenderWindow window;
	sf::Texture tilesTexture;
	sf::Texture flagTexture;
	sf::Texture mineTexture;
	sf::Texture smileyTexture;
	sf::Texture exitTexture;
	sf::Sprite exitSprite;
	sf::Sprite tilesSprite;
	sf::Sprite flagSprite;
	sf::Sprite mineSprite;
	sf::Sprite smileySprite;
	int cell_size;
	int grid[17][17];
	int show_grid[17][17];
public:
	expert()
	{
		srand(time(0));
		window.create(sf::VideoMode(512,512),"Minesweeper Game");
		cell_size=32;
	}
	void expert_textures()
	{
		tilesTexture.loadFromFile("tiles.png");
		flagTexture.loadFromFile("flag.png");
		mineTexture.loadFromFile("mine.png");
		smileyTexture.loadFromFile("smiley.png");
		tilesSprite.setTexture(tilesTexture);
		flagSprite.setTexture(flagTexture);
		mineSprite.setTexture(mineTexture);
		mineSprite.setPosition(50.f,50.f);
		smileySprite.setTexture(smileyTexture);
	}
	void expert_smiley()
	{
		smileySprite.setPosition(260,0);
		smileySprite.setScale(1.25,1.25);
		window.draw(smileySprite);
	}
	void scattered_mines_expert()
	{
	for(int i = 1; i<=16; i++)
	{
        for (int j = 1; j <=16; j++)
		{
            show_grid[i][j] = 10;

            if (rand() % 8 == 0) 
			{
				grid[i][j] = 9;
				window.draw(mineSprite);
			}
            else 
				grid[i][j] = 0;
        }
	}
	}
	void draw_grid_expert()
	{
		for (int i=1;i<=16;i++)
		{
			for(int j=1;j<=16;j++)
			{
				int count=0;
				if(grid[i][j]==9)
					continue;
				if (grid[i+1][j]==9)
					count++;
				if(grid[i][j+1]==9)
					count++;
				if(grid[i-1][j]==9)
					count++;
				if(grid[i][j-1]==9)
					count++;
				if (grid[i+1][j+1]==9)
					count++;
				if(grid[i-1][j-1]==9)
					count++;
				if(grid[i-1][j+1]==9)
					count++;
				if(grid[i+1][j-1]==9)
					count++;
				grid[i][j]=count;
			}
		}
	}
	void gameOver_message_expert()
	{
		sf::RenderWindow box(sf::VideoMode(300,300),"Game Over");
		sf::Texture loseTexture;
		sf::Sprite loseSprite;
		loseTexture.loadFromFile("lose.png");
		loseSprite.setTexture(loseTexture);
		loseSprite.setScale(1,1);
		loseSprite.setPosition(60,100);
		while(box.isOpen())
							 {
								 sf::Event evnt;
								 while(box.pollEvent(evnt))
								 {
									 if(evnt.type==evnt.Closed)
									 {
										 box.close();
									 }
								 }
								 box.clear(sf::Color::Yellow);
								 box.draw(loseSprite);
								 box.display();
								 window.close();
							 }
	}
	 void exit_expert()
	 {
	exitTexture.loadFromFile("exit.png");
	exitSprite.setTexture(exitTexture);
	exitSprite.setPosition(420,0);
	exitSprite.setScale(1,1);
	window.draw(exitSprite);
}
    void expert_Mouse_control()
{
	bool game_over=false;
    sf::Event evnt;
    while (window.pollEvent(evnt))
    {
        if (evnt.type == evnt.Closed)
        {
            window.close();
        }
        else if (evnt.type == sf::Event::MouseButtonPressed)
        {
            int x = sf::Mouse::getPosition(window).x / cell_size;
            int y = sf::Mouse::getPosition(window).y / cell_size;
                if (evnt.mouseButton.button == sf::Mouse::Left)
                {
					if(grid[y][x]==9)
					{
						game_over=true;
						for (int i = 0; i < 16; i++)
                    {
                        for (int j = 0; j < 16; j++)
                        {
							if (grid[i][j] == 9)
                            {
                                show_grid[i][j] = 9;
                            }
                        }
                    }
				gameOver_message_expert();
					}
				else
				{
                    show_grid[y][x] = grid[y][x];
				}
				}
                else if (evnt.mouseButton.button == sf::Mouse::Right)
                {
					show_grid[y][x] = 11;
					flagSprite.setPosition(x * cell_size, y * cell_size);
					window.draw(flagSprite);
                }
	}
        else if (evnt.type == sf::Event::MouseButtonReleased)
        {
		}
    }
	exit_clicked_expert();
	smiley_clicked_expert();
	}
    void display()
{
    window.clear();
    for (int i = 0; i <= 16; i++)
    {
        for (int j = 0; j <= 16; j++)
        {
            if (show_grid[i][j] == 9)
            {
                show_grid[i][j] = grid[i][j];
            }
            tilesSprite.setTextureRect(sf::IntRect(show_grid[i][j] * cell_size, 0, cell_size, cell_size));
            tilesSprite.setPosition(j * cell_size, i * cell_size);
            window.draw(tilesSprite);
        }
    }
	expert_smiley();
	exit_expert();
    window.display();
}
	void exit_clicked_expert()
{
	sf::Event evnt;
			while(window.pollEvent(evnt))
		{
			if(evnt.type==evnt.Closed)
			{
				window.close();
			}
			else if (evnt.type==sf::Event::MouseButtonPressed)
			{
				if(evnt.mouseButton.button==sf::Mouse::Left)
				{ 
					sf::Vector2i m =sf::Mouse::getPosition(window);
					sf::FloatRect exit_bounds=exitSprite.getGlobalBounds();
					if(exit_bounds.contains(m.x,m.y))
					{
						window.close();
					}
				}
			}
			}
}
    void smiley_clicked_expert()
{
	sf::Event evnt;
			while(window.pollEvent(evnt))
		{
			if(evnt.type==evnt.Closed)
			{
				window.close();
			}
			else if (evnt.type==sf::Event::MouseButtonPressed)
			{
				if(evnt.mouseButton.button==sf::Mouse::Left)
				{ 
					sf::Vector2i m =sf::Mouse::getPosition(window);
					sf::FloatRect smiley_bounds=smileySprite.getGlobalBounds();
					if(smiley_bounds.contains(m.x,m.y))
					{
						expert_textures(); 
						scattered_mines_expert();
						draw_grid_expert();
						while(window.isOpen())
						{
							expert_Mouse_control();
							display();
						}
					}
				}
			}
			}
}
    void expert_game()
	{
		expert_textures();
		scattered_mines_expert();
		draw_grid_expert();
		while(window.isOpen())
		{
			expert_Mouse_control();
			display();
		}
   }
};
class menu 
{
private:
	sf::RenderWindow Menu;
	sf::RenderWindow level;
	sf::Texture startTexture;
	sf::Texture titleTexture;
	sf::Texture beginnerTexture;
	sf::Texture expertTexture;
	sf::Sprite startSprite;
	sf::Sprite titleSprite;
	sf::Sprite beginnerSprite;
	sf::Sprite expertSprite;
public:
	menu()
	{
		Menu.create(sf::VideoMode(500,500),"Minesweeper Menu");
	}
	void menu_textures()
	{
		startTexture.loadFromFile("start.png");
		titleTexture.loadFromFile("title.png");
		startSprite.setTexture(startTexture);
		titleSprite.setTexture(titleTexture);
		startSprite.setPosition(175,175);
		titleSprite.setPosition(85,50);
		startSprite.setScale(0.5,0.5);
		titleSprite.setScale(1.5,1.5);
		Menu.draw(titleSprite);
		Menu.draw(startSprite);
	}
	void level_tectures()
	{
		beginnerTexture.loadFromFile("beginner.png");
		expertTexture.loadFromFile("expert.png");
		beginnerSprite.setTexture(beginnerTexture);
		expertSprite.setTexture(expertTexture);
		beginnerSprite.setPosition(160,150);
		expertSprite.setScale(1.25,1);
		expertSprite.setPosition(160,250);
		level.draw(beginnerSprite);
		level.draw(expertSprite);
	}
	void menu_mouse()
	{
		sf::Event evnt;
		while(Menu.pollEvent(evnt))
		{
			if(evnt.type==evnt.Closed)
			{
				Menu.close();
			}
			else if (evnt.type==sf::Event::MouseButtonPressed)
			{
				if(evnt.mouseButton.button==sf::Mouse::Left)
				{ 
					sf::Vector2i m =sf::Mouse::getPosition(Menu);
					sf::FloatRect bounds=startSprite.getGlobalBounds();
					if(bounds.contains(m.x,m.y))
					{
						 level.create(sf::VideoMode(500,500),"LEVELS");
						while(level.isOpen())
						{
							level.clear(sf::Color::Black);
							level_tectures();
						level.display();
						Menu.close();
						sf::Event evnt;
						while(level.pollEvent(evnt))
						{
							if(evnt.type==evnt.Closed)
							{
								level.close();
							}
							else if (evnt.type==sf::Event::MouseButtonPressed)
			{
				if(evnt.mouseButton.button==sf::Mouse::Left)
				{ 
					sf::Vector2i m =sf::Mouse::getPosition(level);
					sf::FloatRect beginner_bounds=beginnerSprite.getGlobalBounds();
					sf::FloatRect expert_bounds=expertSprite.getGlobalBounds();
					if(beginner_bounds.contains(m.x,m.y))
					{
						beginner b;
						b.game();
					}
					if(expert_bounds.contains(m.x,m.y))
					{
						expert e;
						e.expert_game();
					}
				}
							}
						}
						}
					}
						}
					}
				}
			}
	void menu_display()
	{
		while(Menu.isOpen())
		{
			Menu.clear(sf::Color::Yellow);
			menu_textures();
			Menu.display();
			menu_mouse();
		}
	}
};
int main ()
{
	system("color 6E");
	cout << "               *********************************************" << endl;
	cout << "                            MINESWEEPER GAME                " << endl;
	cout << "               *********************************************" << endl;
	menu m;
	m.menu_display();
	beginner b;
	b.game();
	expert e;
	e.expert_game();
	system ("pause");
}