#pragma once

struct form
{
    int x;int y;int w;int h;

    inline
    void border(int b)
    {x+=b;y+=b;b<<=1;w-=b;h-=b;}

    form&&ver_div(int c,const int dist=0)
    {   
        if(c>0)
        {
            h-=(c+dist);
            return form{x,y+h+dist,w,c};
        }
        else
        {
            h-=(-c+dist);
            const int old=y;
            y=-c+dist;
            return form{x,old,w,-c-dist};
        }
    }

    form&&gor_div(int c,const int dist=0)
    {
        if(c>0)
        {
            w-=(c+dist);
            return form{x+w+dist,y,c,h};
        }
        else
        {
            w-=(-c+dist);
            const int old=x;
            x=-c+dist;
            return form{old,y,-c-dist,h};
        }
    }

    inline const int w2(){return w>>1;}
    inline const int h2(){return h>>1;}
};
#define un(s) s.x,s.y,s.w,s.h