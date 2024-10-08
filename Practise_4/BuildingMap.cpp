//
// Created by perha on 09.05.2024.
//
#include "BuildingMap.h"
#include <fstream>
#include <iostream>
#include <string>
BuildingMap::BuildingMap(const std::string buildingMapFile)
{
    init(buildingMapFile) ;
    createPaths() ;
}
BuildingMap::~BuildingMap()
{
    if (arr)
    {
        for (int i = 0 ; i < getH()*getW() ; i++)
            delete arr[i] ;
        delete[] arr ;
    }
    if (indexes)
    {
        for (int i = 0 ; i < getH() ; i++)
            delete indexes[i] ;
        delete[] indexes ;
    }
    if (visited)
    {
        for (int i = 0 ; i < getH() ; i++)
            delete visited[i] ;
        delete[] visited ;
    }
    if (went)
    {
        for (int i = 0 ; i < getH() ; i++)
            delete went[i] ;
        delete[] went ;
    }
}
void BuildingMap::displayAllCubicles()const
{
    std::cout << "The cubicles in the building are:" << std::endl ;
    for (int i = 0 ; i < getH() ; i++)
    {
        for (int j = 0 ; j < getW() ; j++)
        {
            if (j == getW() - 1)
                std::cout << "(" << i << "," << j << ")" ;
            else
                std::cout << "(" << i << "," << j << ") , " ;
        }
        std::cout << std::endl ;
    }
}
void BuildingMap::displayAdjacentCubicles(const int row,const int col)const
{
    std::cout << "The cubicles adjacent to (" << row << "," << col << ") are:" << std::endl ;
    std::string line = "(" + std::to_string(row) + "," + std::to_string(col) + ") -> " ;
    int c = 0 ;
    for (int i = 0 ; i < getW()*getH() ; i++)
    {
        if (arr[row*getW() + col][i])
        {
            line += "(" + std::to_string(i/getW()) + "," + std::to_string(i%getW()) + ") , " ;
            c++ ;
        }
    }
    if (c > 0)
        line = line.substr(0,line.size()-2) ;
    std::cout << line << std::endl ;
}
void BuildingMap::displayBuildingMap()const
{
    std::cout << "The building map is as follows:" << std::endl ;
    toString() ;
}
void BuildingMap::findPaths(const int startRow,const int startCol,const int endRow,const int endCol)
{
    int c = 0 ;
    std::cout << "Paths from (" << startRow << "," << startCol << ") to (" << endRow << "," << endCol << ") are:" << std::endl ;
    clear(getH() , getW()) ;
    int x , y , xx = startCol , yy = startCol ;
    Stack d ;
    Stack s ;
    visited[startRow][startCol] = true ;
    s.push(std::to_string(startRow) + "," + std::to_string(startCol)) ;
    int px , py ;
    x = s.getX() ;
    y = s.getY() ;
    while(!s.isEmpty())
    {
        if (x == endRow && y == endCol)
        {
            s.display() ;
            c ++ ;
            x = d.getX() ;
            y = d.getY() ;
            while(!(s.getX() == x && s.getY() == y))
            {
                px = s.getX() ;
                py = s.getY() ;
                visited[px][py] = false ;
                clearW(px,py) ;
                s.pop() ;
            }
            d.pop() ;
        }
        std::string data = getnext(x,y) ;
        xx = to_int(data , "x") ;
        yy = to_int(data , "y") ;
        if (xx == -1 && yy == -1)
        {
            clearW(x,y) ;
            visited[x][y] = false ;
            s.pop() ;
        }
        else
        {
            s.push(data) ;
            wentTo(x,y,xx,yy,true) ;//0 - pravo , 1 - levo , 2 - niz , 3 - verh
            diffPaths(x , y , d , endRow , endCol) ;
            visited[xx][yy] = true ;
        }
        if (!s.isEmpty())
        {
            x = s.getX() ;
            y = s.getY() ;
        }
    }
    if (c == 0)
        std::cout << "None" << std::endl ;
}
void BuildingMap::findPaths(const int startRow,const int startCol,const int endRow,const int endCol, const int avoidRow,const int avoidCol)
{
    int c = 0 ;
    std::cout << "Paths from (" << startRow << "," << startCol << ") to (" << endRow << "," << endCol << ") avoiding (" << avoidRow << "," << avoidCol << ") are:" << std::endl ;
    clear(getH() , getW()) ;
    visited[avoidRow][avoidCol] = true ;
    int x , y , xx = startCol , yy = startCol ;
    Stack d ;
    Stack s ;
    visited[startRow][startCol] = true ;
    s.push(std::to_string(startRow) + "," + std::to_string(startCol)) ;
    int px , py ;
    x = s.getX() ;
    y = s.getY() ;
    while(!s.isEmpty())
    {
        if (x == endRow && y == endCol)
        {
            s.display() ;
            c++ ;
            x = d.getX() ;
            y = d.getY() ;
            while(!(s.getX() == x && s.getY() == y))
            {
                px = s.getX() ;
                py = s.getY() ;
                visited[px][py] = false ;
                clearW(px,py) ;
                s.pop() ;
            }
            d.pop() ;
        }
        std::string data = getnext(x,y) ;
        xx = to_int(data , "x") ;
        yy = to_int(data , "y") ;
        if (xx == -1 && yy == -1)
        {
            clearW(x,y) ;
            visited[x][y] = false ;
            s.pop() ;
        }
        else
        {
            s.push(data) ;
            wentTo(x,y,xx,yy,true) ;//0 - pravo , 1 - levo , 2 - niz , 3 - verh
            diffPaths(x , y , d , endRow , endCol) ;
            visited[xx][yy] = true ;
        }
        if (!s.isEmpty())
        {
            x = s.getX() ;
            y = s.getY() ;
        }
    }
    if (c == 0)
        std::cout << "None" << std::endl ;
}
void BuildingMap::clearW(int x , int y)
{
    for (int i = 0 ; i < 4 ; i++)
    {
        went[x*getW()+y][i] = false ;
    }
}
void BuildingMap::wentTo(int x , int y , int xx , int yy , bool value)
{
    if (x > xx)
        went[x*getW()+y][3] = value ;
    else if (x < xx)
        went[x*getW()+y][2] = value ;
    else if (y > yy)
        went[x*getW()+y][1] = value ;
    else if (y < yy)
        went[x*getW()+y][0] = value ;
}
void BuildingMap::init(const std::string link)
{
    std::ifstream file(link) ;
    std::string line ;
    if (file.is_open())
    {
        std::getline(file, line) ;
        int i = line.find_first_of(' ') ;
        setH(std::stoi(line.substr(0 , i))) ;
        setW(std::stoi(line.substr(i + 1 , line.size() - 1))) ;
        indexes = new int*[getH()] ;
        for (i = 0 ; std::getline(file , line) ; i++)
        {
            indexes[i] = new int[getW()] ;
            for (int j = 0 ; j < getW() ; j++)
            {
                indexes[i][j] = line[j] - '0' ;
            }
        }
        arr = new bool*[getW()*getH()] ;
        for (int i = 0 ; i < getW()*getH() ; i++)
        {
            arr[i] = new bool[getW()*getH()] ;
        }
        visited = new bool*[getW()] ;
        for (int i = 0 ; i < getW() ; i++)
        {
            visited[i] = new bool[getW()] ;
        }
        went = new bool*[getW()*getH()] ;
        for (int i = 0 ; i < getW()*getH() ; i++)
        {
            went[i] = new bool[4] ;
        }
        file.close() ;
    }
    else
        std::cout << "File is not found. Please check the link again <3" << std::endl ;
}
void BuildingMap::add_edge(const int x ,const int y) const
{
    if (!arr[x][y] && !arr[y][x])
    {
        arr[x][y] = true ;
        arr[y][x] = true ;
    }
}
void BuildingMap::show()
{
    for (int i = 0 ; i < getH() ; i++)
    {
        for (int j = 0; j < getW(); j++)
            std::cout << indexes[i][j] ;
        std::cout << std::endl ;
    }
    for (int i = 0 ; i < getH()*getW() ; i++)
    {
        std::cout << i << " ";
        for (int j = 0; j < getW()*getH(); j++)
            std::cout << j << "-" << arr[i][j] << " ";
        std::cout << std::endl ;
    }
}
void BuildingMap::setH(const int h)
{
    this->h = h ;
}
void BuildingMap::setW(int w)
{
    this->w = w ;
}
int BuildingMap::getH() const
{
    return h ;
}
int BuildingMap::getW() const
{
    return w ;
}
void BuildingMap::toString() const
{
    int c = 0 ;
    std::string line ;
    for (int i = 0 ; i < getH()*getW() ; i++)
    {
        line+= "(" + std::to_string(i/getW()) + "," + std::to_string(i%6) + ") -> " ;
        for (int j = 0; j < getW() * getH(); ++j)
        {
            if (arr[i][j])
            {
                line += "(" + std::to_string(j / getW()) + "," + std::to_string(j % 6) + ") , ";
                c++ ;
            }
        }
        if (c > 0)
            line = line.substr(0,line.size()-2) ;
        std::cout << line << std::endl ;
        line = "" ;
        c = 0 ;
    }
}
void BuildingMap::createPaths() const
{
    for (int i = 0 ; i < getH() ; i++)
    {
        for (int j = 0 ; j < getW() ; j++)
        {
            switch (indexes[i][j])
            {
                case 0 :
                    if(i == 0)
                    {
                        if (i != getH() - 1)
                            add_edge(i*getW()+j , (i+1)*getW()+j) ;
                        if (j == 0)
                        {
                            if (j != getW() - 1)
                            {
                                if (indexes[i][j+1] != 1 && indexes[i][j+1] != 3)
                                    add_edge(i * getW() + j, i * getW() + j + 1);
                            }
                        }
                        else
                        {
                            if (j != getW() - 1)
                            {
                                if (indexes[i][j+1] != 1 && indexes[i][j+1] != 3)
                                    add_edge(i * getW() + j, i * getW() + j + 1);
                            }

                            add_edge(i * getW() + j , i * getW() + j - 1) ;
                        }
                    }
                    else if (i == getH() - 1)
                    {
                        if (i - 1 >= 0)
                            if (indexes[i-1][j] != 3 && indexes[i-1][j] != 2)
                                add_edge(i*getW()+j , (i-1)*getW()+j) ;
                        if (j == 0)
                        {
                            if (j != getW() - 1)
                            {
                                if (indexes[i][j+1] != 1 && indexes[i][j+1] != 3)
                                    add_edge(i * getW() + j, i * getW() + j + 1);
                            }
                        }
                        else
                        {
                            if (j != getW() - 1)
                            {
                                if (indexes[i][j+1] != 1 && indexes[i][j+1] != 3)
                                    add_edge(i * getW() + j, i * getW() + j + 1);
                            }

                            add_edge(i * getW() + j , i * getW() + j - 1) ;
                        }
                    }
                    else
                    {
                        add_edge(i*getW()+j , (i+1)*getW()+j) ;
                        if (i - 1 >= 0)
                            if (indexes[i-1][j] != 3 && indexes[i-1][j] != 2)
                                add_edge(i*getW()+j , (i-1)*getW()+j) ;
                        if (j == 0)
                        {
                            if (j != getW() - 1)
                            {
                                if (indexes[i][j+1] != 1 && indexes[i][j+1] != 3)
                                    add_edge(i * getW() + j, i * getW() + j + 1);
                            }
                        }
                        else
                        {
                            if (j != getW() - 1)
                            {
                                if (indexes[i][j+1] != 1 && indexes[i][j+1] != 3)
                                    add_edge(i * getW() + j, i * getW() + j + 1);
                            }

                            add_edge(i * getW() + j , i * getW() + j - 1) ;
                        }
                        break ;
                    }
                case 1 :
                    if(i == 0)
                    {
                        if (i != getH() - 1)
                            add_edge(i*getW()+j , (i+1)*getW()+j) ;
                        if (j == 0)
                        {
                            if (j != getW() - 1)
                            {
                                if (indexes[i][j+1] != 1 && indexes[i][j+1] != 3)
                                    add_edge(i * getW() + j, i * getW() + j + 1);
                            }
                        }
                        else
                        {
                            if (j != getW() - 1)
                            {
                                if (indexes[i][j+1] != 1 && indexes[i][j+1] != 3)
                                    add_edge(i * getW() + j, i * getW() + j + 1);
                            }
                        }
                    }
                    else if (i == getH() - 1)
                    {
                        if (i - 1 >= 0)
                            if (indexes[i-1][j] != 3 && indexes[i-1][j] != 2)
                                add_edge(i*getW()+j , (i-1)*getW()+j) ;
                        if (j == 0)
                        {
                            if (j != getW() - 1)
                            {
                                if (indexes[i][j+1] != 1 && indexes[i][j+1] != 3)
                                    add_edge(i * getW() + j, i * getW() + j + 1);
                            }
                        }
                        else
                        {
                            if (j != getW() - 1)
                            {
                                if (indexes[i][j+1] != 1 && indexes[i][j+1] != 3)
                                    add_edge(i * getW() + j, i * getW() + j + 1);
                            }
                        }
                    }
                    else
                    {
                        add_edge(i*getW()+j , (i+1)*getW()+j) ;
                        if (i - 1 >= 0)
                            if (indexes[i-1][j] != 3 && indexes[i-1][j] != 2)
                                add_edge(i*getW()+j , (i-1)*getW()+j) ;
                        if (j == 0)
                        {
                            if (j != getW() - 1)
                            {
                                if (indexes[i][j+1] != 1 && indexes[i][j+1] != 3)
                                    add_edge(i * getW() + j, i * getW() + j + 1);
                            }
                        }
                        else
                        {
                            if (j != getW() - 1)
                            {
                                if (indexes[i][j+1] != 1 && indexes[i][j+1] != 3)
                                    add_edge(i * getW() + j, i * getW() + j + 1);
                            }
                        }
                    }
                    break ;
                case 2 :
                    if(i == 0)
                    {
                        if (j == 0)
                        {
                            if (j != getW() - 1)
                            {
                                if (indexes[i][j+1] != 1 && indexes[i][j+1] != 3)
                                    add_edge(i * getW() + j, i * getW() + j + 1);
                            }
                        }
                        else
                        {
                            if (j != getW() - 1)
                            {
                                if (indexes[i][j+1] != 1 && indexes[i][j+1] != 3)
                                    add_edge(i * getW() + j, i * getW() + j + 1);
                            }

                            add_edge(i * getW() + j , i * getW() + j - 1) ;
                        }
                    }
                    else if (i == getH() - 1)
                    {
                        if (i - 1 >= 0)
                            if (indexes[i-1][j] != 3 && indexes[i-1][j] != 2)
                                add_edge(i*getW()+j , (i-1)*getW()+j) ;
                        if (j == 0)
                        {
                            if (j != getW() - 1)
                            {
                                if (indexes[i][j+1] != 1 && indexes[i][j+1] != 3)
                                    add_edge(i * getW() + j, i * getW() + j + 1);
                            }
                        }
                        else
                        {
                            if (j != getW() - 1)
                            {
                                if (indexes[i][j+1] != 1 && indexes[i][j+1] != 3)
                                    add_edge(i * getW() + j, i * getW() + j + 1);
                            }

                            add_edge(i * getW() + j , i * getW() + j - 1) ;
                        }
                    }
                    else
                    {
                        if (i - 1 >= 0)
                            if (indexes[i-1][j] != 3 && indexes[i-1][j] != 2)
                                add_edge(i*getW()+j , (i-1)*getW()+j) ;
                        if (j == 0)
                        {
                            if (j != getW() - 1)
                            {
                                if (indexes[i][j+1] != 1 && indexes[i][j+1] != 3)
                                    add_edge(i * getW() + j, i * getW() + j + 1);
                            }
                        }
                        else
                        {
                            if (j != getW() - 1)
                            {
                                if (indexes[i][j+1] != 1 && indexes[i][j+1] != 3)
                                    add_edge(i * getW() + j, i * getW() + j + 1);
                            }

                            add_edge(i * getW() + j , i * getW() + j - 1) ;
                        }
                    }
                    break ;
                case 3 :
                    if(i == 0)
                    {
                        if (j == 0)
                        {
                            if (j != getW() - 1)
                            {
                                if (indexes[i][j+1] != 1 && indexes[i][j+1] != 3)
                                    add_edge(i * getW() + j, i * getW() + j + 1);
                            }
                        }
                        else
                        {
                            if (j != getW() - 1)
                            {
                                if (indexes[i][j+1] != 1 && indexes[i][j+1] != 3)
                                    add_edge(i * getW() + j, i * getW() + j + 1);
                            }
                        }
                    }
                    else if (i == getH() - 1)
                    {
                        if (i - 1 >= 0)
                            if (indexes[i-1][j] != 3 && indexes[i-1][j] != 2)
                                add_edge(i*getW()+j , (i-1)*getW()+j) ;
                        if (j == 0)
                        {
                            if (j != getW() - 1)
                            {
                                if (indexes[i][j+1] != 1 && indexes[i][j+1] != 3)
                                    add_edge(i * getW() + j, i * getW() + j + 1);
                            }
                        }
                        else
                        {
                            if (j != getW() - 1)
                            {
                                if (indexes[i][j+1] != 1 && indexes[i][j+1] != 3)
                                    add_edge(i * getW() + j, i * getW() + j + 1);
                            }
                        }
                    }
                    else
                    {
                        if (i - 1 >= 0)
                            if (indexes[i-1][j] != 3 && indexes[i-1][j] != 2)
                                add_edge(i*getW()+j , (i-1)*getW()+j) ;
                        if (j == 0)
                        {
                            if (j != getW() - 1)
                            {
                                if (indexes[i][j+1] != 1 && indexes[i][j+1] != 3)
                                    add_edge(i * getW() + j, i * getW() + j + 1);
                            }
                        }
                        else
                        {
                            if (j != getW() - 1)
                            {
                                if (indexes[i][j+1] != 1 && indexes[i][j+1] != 3)
                                    add_edge(i * getW() + j, i * getW() + j + 1);
                            }
                        }
                    }
                    break ;
            }
        }
    }
}
bool BuildingMap::contJustOne(int x , int y , int erow , int ecol)
{
    if (x == erow && y == ecol)
        return false ;
    int c = 0 ;
    for (int i = 0 ; i < getW()*getH() ; i++)
    {
        if (arr[x*getW() + y][i])
            c++ ;
    }
    if (c == 1)
    {
        backtracked = true ;
        return  true ;
    }
    return false ;
}
void BuildingMap::rmv(std::string& str , std::string& index)
{
    std::string l ;
    int size = index.size() ;
    for (int i = str.size() ; i > 0 ; i--)
    {
        l = str.substr(i-size, size) ;
        if (l == index)
        {
            str = str.substr(0 , i+4) ;
            return ;
        }
    }
}

void BuildingMap::rmv(Stack& s)
{
    bool done = false ;
    int x , y ;
    int c = 0 , cc ;
    while(!done && !s.isEmpty())
    {
        x = s.getX() ;
        y = s.getY() ;
        if (contJustOne(x,y))
        {
            s.pop() ;
        }
        else
        {
            cc = count(x*getW()+y) ;
             for (int i = 0 ; i < getW()*getH() ; i++)
             {
                 if (arr[x*getW() + y][i] && visited[i/getW()][i%getW()])
                     c++ ;
             }
             if(cc - 1 != c)
             {
                 s.pop() ;
             }
             else
             {
                 done = true ;
             }
             c = 0 ;
        }
    }
    if (s.isEmpty())
        noPath = true ;
    else
        noPath = false ;
}
int BuildingMap::count(int x)
{
    int c = 0 ;
    for (int i = 0 ; i < getW()*getH() ; i++)
    {
        if (arr[x][i])
            c++ ;
    }
    return c ;
}
bool BuildingMap::contJustOne(int x , int y)
{
    int c = 0 ;
    for (int i = 0 ; i < getW()*getH() ; i++)
    {
        bool t = arr[x*getW()+y][i] ;
        bool tt = !give(x,y,i/getW(),i%getW()) ;
        if (arr[x*getW()+y][i] && !give(x,y,i/getW(),i%getW()))
            c++ ;
    }
    if (c == 1)
    {
        return  true ;
    }
    return false ;
}

void BuildingMap::clear(int x , int y)
{
    for (int i = 0 ; i < x; i++)
        for (int j = 0 ; j < y ; j++)
            visited[i][j] = false ;
}

bool BuildingMap::diffPaths(int x , int y , Stack& s , int erow , int ecol)
{
    if (x == erow && y == ecol)
        return false ;
    int index = x*getW() + y ;
    int c = 0 ;
    for (int i = 0 ; i < getW()*getH() ; i++)
    {
        bool t = arr[index][i] ;
        bool tt = visited[(i)/getW()][(i)%getW()] ;
        bool ttt = !give(x,y,i/getW(),i%getW()) ;
        if (arr[index][i] && !visited[(i)/getW()][(i)%getW()])
        {
            if (!give(x,y,i/getW(),i%getW()))
                c++;
        }
    }
    if (c >= 1)
    {
        s.push(std::to_string(x) + "," + std::to_string(y)) ;
        return  true ;
    }
    return  false ;
}
std::string BuildingMap::getnext(int x , int y)
{
    std::string data = "" ;
    bool s = false ;
    int c = 0 ;
    int pos ;
    for (int i = 0 ; i < getW()*getH() && !s; i++)
    {
        bool t = arr[x*getW()+y][i] ;
        bool tt = !visited[i/getW()][i%getW()] ;
        bool ttt = !give(x,y,i/getW(),i%getW()) ;
        if(arr[x*getW()+y][i] && !visited[i/getW()][i%getW()] && !give(x,y,i/getW(),i%getW()))
        {
            data = std::to_string(i/getW()) + "," + std::to_string(i%getW()) ;
            s = true ;
        }
    }
    return data ;
}
bool BuildingMap::give(int x , int y ,int xx , int yy)
{
    if (x > xx)
        return went[x*getW()+y][3] ;
    else if (x < xx)
        return went[x*getW()+y][2] ;
    else if (y > yy)
        return went[x*getW()+y][1] ;
    else if (y < yy)
        return went[x*getW()+y][0] ;
}

int BuildingMap::to_int(std::string data , std::string index)
{
    if (data == "")
        return -1 ;
    if (index == "x")
    {
        int size = data.find_first_of(',') ;
        std::string xx = data.substr(0,size) ;
        int x = std::stoi(xx) ;
        return x ;
    }
    else
    {
        int size = data.find_first_of(',') ;
        int size1 = data.size() ;
        std::string yy = data.substr(size+1,size1) ;
        int y = std::stoi(yy) ;
        return y ;
    }
}