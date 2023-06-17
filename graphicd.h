#include <darklib.h>
void col(short value){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),value);
}
struct SQU
{
    std::string txt;
    short color;
};
struct entity
{
	short x,y,color;
	std::string txt;
	bool defined;
};
struct GRID {
	int x,y,all;
	SQU items[10000];
	entity entity[10];
};
void g_setup(GRID *grid,std::string ch,short color)
{
	#define entity_x ((*grid).entity[i]).x
	#define entity_y ((*grid).entity[i]).y
	short coord;
	using namespace std;
	int i,j=1;
    for (i=0;i<(*grid).all;i++)
    {
        ((*grid).items[i]).txt=ch;
        ((*grid).items[i]).color=color;
    }
	for (i=0;i<10;i++)
	{
		if (((*grid).entity[i]).defined)
		{
			coord = entity_x+((*grid).x*entity_y);
			((*grid).items[coord]).color=((*grid).entity[i]).color;
			((*grid).items[coord]).txt=((*grid).entity[i]).txt;
		}
	}
}
void g_paint(GRID grid)
{
	using namespace std;
	int i,j=1,last_col=0;
    for (i=0;i<grid.all;i++)
    {
        if (last_col != grid.items[i].color)
		{
			col(grid.items[i].color);
		}
		last_col = grid.items[i].color; 
        cout<<grid.items[i].txt;
        if (j>=grid.x)
        {
            cout <<endl;
            j = 0;
        }
        j++;
    }
}
void g_paint2(GRID grid,GRID last_grid)
{
	bool same;
	using namespace std;
	int i,j=1,last_col=0,h=0;
	for (h=0;h<grid.all;h++)
	{
		if (last_grid.items[i].color != grid.items[i].color) {
			same = false;
			break;
		}
		if (last_grid.items[i].txt != grid.items[i].txt) {
			same = false;
			break;
		}
	}
	if (!same) {
		for (i=0;i<grid.all;i++)
		{
			if (last_col != grid.items[i].color)
			{
				col(grid.items[i].color);
			}
			last_col = grid.items[i].color; 
			cout<<grid.items[i].txt;
			if (j>=grid.x)
			{
				cout <<endl;
				j = 0;
			}
			j++;
		}
	}
}
short g_grid_all(GRID grid)
{
	return grid.x*grid.y;
}
void g_x_line (GRID *grid,short start,short end_,std::string txt,short color)
{
    #define items (*grid).items
    end_+=start;
    for (start;start<end_;start++)
    {
        (items[start]).color=color;
        (items[start]).txt=txt;
    }
} 
void g_y_line (GRID *grid,short start,short end_,std::string txt,short color)
{
    #define items (*grid).items
	short i; 
	end_++;
	for (i=0;i<end_;i++)
	{
        (items[start]).color=color;
        (items[start]).txt=txt;
		start+=(*grid).x;
	}
	
}
short true_y_value (GRID grid,short start,short x)
{
	int i=0,num=start;
	for (i=0;i<x;i++)
	{
		start+=grid.x;
	}
	return start;
}
short true_x_value (GRID grid,short start,short y)
{
	int i=0,num=start;
	for (i=0;i<y;i++)
	{
		start+=grid.y;
	}
	return start;
}
void g_square (GRID *grid,short start,short x,short y,std::string txt,short color)
{
    #define Grid &(*grid)
    g_x_line(Grid,start,x,txt,color);
    g_y_line(Grid,start,y,txt,color);
    g_x_line(Grid,true_y_value(*grid,start,y),x,txt,color);
    g_y_line(Grid,start+x,y,txt,color);
}
void g_fill (GRID *grid,short start,short x,short y,std::string txt,short color)
{
    #define Grid &(*grid)
    for (int i=0;i<y;i++)
    {
        g_x_line(Grid,(start+(i*(*grid).x)),x,txt,color);
    }
}
void g_pixel (GRID *grid,short x,short y,std::string txt,short color)
{
    short n=x;
    #define items (*grid).items
    for (int i=0;i<y;i++)
    {
        n+=(*grid).x;
    }
    (items[n]).color=color;
    (items[n]).txt=txt;
}
void g_entity (GRID *grid,short index,short x,short y,std::string txt,short color)
{
    ((*grid).entity[index]).x=x;
    ((*grid).entity[index]).y=y;
    ((*grid).entity[index]).color=color;
    ((*grid).entity[index]).txt=txt;
    ((*grid).entity[index]).defined=true;
}
short xof (GRID grid,short index)
{
	return grid.entity[index].x;
}
short yof (GRID grid,short index)
{
	return grid.entity[index].y;
}
std::string txtof (GRID grid,short index)
{
	return grid.entity[index].txt;
}
short colof (GRID grid,short index)
{
	return grid.entity[index].color;
}
void draw_entity (GRID *grid,short index)
{
	#define entity_x ((*grid).entity[index]).x
	#define entity_y ((*grid).entity[index]).y
    #define items (*grid).items
	short coord = entity_x+((*grid).x*entity_y);
	items[coord].color=((*grid).entity[index]).color;
	items[coord].txt=((*grid).entity[index]).txt;
}
void askKey(GRID *grid,short index,short minx,short miny,short maxx,short maxy)
{
	using namespace std;
    #define entity_x ((*grid).entity[index]).x
    #define entity_y ((*grid).entity[index]).y
    char ch=getch();
    if (ch=='w')
    {
        if ((entity_y-1) >= miny)
            entity_y--;
			//g_paint(*grid);
    }
    if (ch=='a')
    {
        if ((entity_x-1) >= minx)
            entity_x--;
			//g_paint(*grid);
    }
    if (ch=='s')
    {
        if ((entity_y+1) <= maxy)
            entity_y++;
			//g_paint(*grid);
    }
    if (ch=='d')
    {
        if ((entity_x+1) <= maxx)
            entity_x++;
			//g_paint(*grid);
    }
    if (ch==27)
    {
        exit(0);
    }
	if (ch=='q')
	{
		//SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE),CONSOLE_FULLSCREEN_MODE,0);
		keybd_event(VK_MENU,0x38,0,0);
		keybd_event(VK_RETURN,0x1c,0,0);
		keybd_event(VK_RETURN,0x1c,KEYEVENTF_KEYUP,0);
		keybd_event(VK_MENU,0x38,KEYEVENTF_KEYUP,0);
	}
}












