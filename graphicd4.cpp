// B A S I C    E L E M E N T S

struct grphd::generic::Coords
{
    unsigned char x, y;
    Coords& operator+=(const Coords&);
};

grphd::generic::Coords& grphd::generic::Coords::operator+=(const Coords& o)
{
    x += o.x;
    y += o.y;
    return *this;
}

struct grphd::graphic::Pixel
{
    unsigned char clr, txt;
};

// C O N S O L E

void grphd::console::clearScr()
{
    system("cls");
}

void grphd::console::gotoXY(grphd::generic::Coords coord)
{
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
                              {
                                  coord.x, coord.y
                              });
}

void grphd::console::setOutptClr(char clr)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), clr);
}

void grphd::console::stop()
{
    system("pause>nul");
}

void grphd::console::resetColor()
{
    grphd::console::setOutptClr(grphd::console::stdColor);
}

// E N T I T Y

class grphd::graphic::Entity
{
    generic::Coords coords;
    graphic::Pixel texture;

    public:

    Entity(generic::Coords coords = {0, 0}, graphic::Pixel texture = {0, ' '});

    unsigned char incrsX(unsigned char v = 1) {coords.x += v; return coords.x;} // return *this;
    unsigned char incrsY(unsigned char v = 1) {coords.y += v; return coords.y;}
    unsigned char decrsX(unsigned char v = 1) {coords.x -= v; return coords.x;}
    unsigned char decrsY(unsigned char v = 1) {coords.y -= v; return coords.y;}
    generic::Coords& relativeXY(generic::Coords);
    generic::Coords& absoluteXY(generic::Coords);

    graphic::Pixel& setTexture(graphic::Pixel);
    graphic::Pixel& getTexture();
    generic::Coords& setCoords(generic::Coords);
    generic::Coords& getCoords();
};

// G R I D

class grphd::graphic::Grid
{
    DynamicArray<Entity, 1> entities;
    Pixel **pixels;
    Pixel dfltClrTxt;
    generic::Coords maxXY;
    void freePixels();
    void allocatePixels();

    public :

    Grid(generic::Coords mXY = {1, 1}, graphic::Pixel = {0, ' '});

    ~Grid();

    void paint();
    void specificPaint(generic::Coords, generic::Coords, bool gt = false);
    void reset(generic::Coords mXY = {1, 1}, graphic::Pixel = {0, ' '});

    void defaultRefill();
    void refill(graphic::Pixel = {0, ' '});
    void moveSect(generic::Coords, generic::Coords, generic::Coords);
    generic::Coords getMaxXY();
    graphic::Pixel getDfltClrTxt();

    graphic::Entity& addEntity(const graphic::Entity &e);
    bool removeEntity(unsigned char n);

    void update();
};

void grphd::graphic::Grid::update()
{
    for(unsigned char i = 0; i < entities.getLength(); i++)
    {
        //pixels
    }
}

grphd::graphic::Entity& grphd::graphic::Grid::addEntity(const graphic::Entity &e)
{
    return entities.append(e);
}

bool grphd::graphic::Grid::removeEntity(unsigned char n)
{
    return entities.remove(n);
}

void grphd::graphic::Grid::allocatePixels()
{
    try
    {
        pixels = new Pixel*[maxXY.y];

        for(char i = 0; i < maxXY.y; i++)
        {
            pixels[i] = new Pixel[maxXY.x];
            for(char j = 0; j < maxXY.x;
                pixels[i][j] = dfltClrTxt,
                j++
               );
        }
    } catch(std::exception &e)
    {
        std::cout << "Exception on allocatePixels: ";
        std::cout << e.what() << '\n';
    }
}

void grphd::graphic::Grid::freePixels()
{
    try
    {
        for(char i = 0; i < maxXY.y; delete [] pixels[i], i++);
        delete [] pixels;
        pixels = nullptr;
    } catch(std::exception &e)
    {
        std::cout << "Exception on freePixels: ";
        std::cout << e.what() << '\n';
    }
}

inline grphd::generic::Coords grphd::graphic::Grid::getMaxXY()
{
    return maxXY;
}

inline grphd::graphic::Pixel grphd::graphic::Grid::getDfltClrTxt()
{
    return dfltClrTxt;
}

grphd::graphic::Grid::Grid(generic::Coords xY, graphic::Pixel clrTxt):
    maxXY(xY), dfltClrTxt(clrTxt), pixels(new grphd::graphic::Pixel* [maxXY.y])/*,
    entities(graphic::Entity())*/
{
    allocatePixels();
}

grphd::graphic::Grid::~Grid()
{
    freePixels();
}

void grphd::graphic::Grid::paint()
{




    for(char i = 0; i < maxXY.y; i++, std::cout << '\n')
        for(char j = 0; j < maxXY.x;
                            grphd::console::setOutptClr(pixels[i][j].clr),
                            std::cout << pixels[i][j].txt,
                            j++
                            );

    grphd::console::resetColor();
}

void grphd::graphic::Grid::specificPaint(generic::Coords c1, generic::Coords c2, bool gt)
{
    if(gt == 0)
    {
        for(char i = c1.y; i < c2.y; i++, std::cout << '\n')
            for(char j = c1.x; j < c2.x;
                                grphd::console::setOutptClr(pixels[i][j].clr),
                                std::cout << pixels[i][j].txt,
                                j++
                                );
    } else
    {
        grphd::console::gotoXY(c1);

        for(char i = c1.y; i < c2.y; i++, grphd::console::gotoXY({c1.x, i}))
            for(char j = c1.x; j < c2.x;
                                grphd::console::setOutptClr(pixels[i][j].clr),
                                std::cout << pixels[i][j].txt,
                                j++
                                );
    }

    grphd::console::resetColor();
}

void grphd::graphic::Grid::reset(generic::Coords mXY, graphic::Pixel clrTxt)
{
    freePixels();
    dfltClrTxt = clrTxt, maxXY = mXY;
    allocatePixels();
}

void grphd::graphic::Grid::defaultRefill()
{
    for(char i = 0; i < maxXY.y; i++)
        for(char j = 0; j < maxXY.x;
            pixels[i][j] = dfltClrTxt,
            j++
           );
}

void grphd::graphic::Grid::refill(graphic::Pixel clrTxt)
{
    for(char i = 0; i < maxXY.y; i++)
        for(char j = 0; j < maxXY.x;
            pixels[i][j] = clrTxt,
            j++
           );
}

// E N T I T Y

grphd::generic::Coords& grphd::graphic::Entity::setCoords(generic::Coords newCoords)
{
    return coords = newCoords;
}

grphd::generic::Coords& grphd::graphic::Entity::getCoords()
{
    return coords;
}

grphd::graphic::Pixel& grphd::graphic::Entity::setTexture(graphic::Pixel newTexture)
{
    return texture = newTexture;
}

grphd::graphic::Pixel& grphd::graphic::Entity::getTexture()
{
    return texture;
}

inline grphd::generic::Coords& grphd::graphic::Entity::relativeXY(generic::Coords addCoords)
{
    coords += addCoords; return coords;
}

inline grphd::generic::Coords& grphd::graphic::Entity::absoluteXY(generic::Coords newCoords)
{
    coords = newCoords; return coords;
}

grphd::graphic::Entity::Entity(grphd::generic::Coords coords, grphd::graphic::Pixel texture):
    coords(coords), texture(texture)
{
}

