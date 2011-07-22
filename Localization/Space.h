/* 
 * File:   Space.h
 * Author: Ivo
 *
 * Created on 12 de Julho de 2011, 13:57
 */

#ifndef SPACE_H
#define	SPACE_H

struct point
{
    double x, y;

    point& operator += (const point &p2)
    {
        this->x += p2.x;
        this->y += p2.y;
        return *this;
    }
};

struct vector
{
    double x, y;

    vector& operator += (const vector &v2)
    {
	this->x += v2.x;
        this->y += v2.y;
        return *this;
    }

    vector& operator /= (double c)
    {
        this->x /= c;
        this->y /= c;
        return *this;
    }
};

inline point operator * (double t, const point &p)
{
    point p2 = {p.x * t, p.y * t};
    return p2;
}

inline double operator * (const point &p, const point &p2)
{
    double t = p.x * p2.x + p.y * p2.y;
    return t;
}

inline vector operator - (const point &p1, const point &p2)
{
    vector v = {p1.x - p2.x, p1.y - p2.y};
    return v;
}



inline point operator + (const point &p, const vector &v)
{
    point p2 = {p.x + v.x, p.y + v.y};
    return p2;
}

inline point operator - (const point &p, const vector &v)
{
    point p2 = {p.x - v.x, p.y - v.y};
    return p2;
}



inline vector operator + (const vector &v1, const vector &v2)
{
    vector v = {v1.x + v2.x, v1.y + v2.y};
    return v;
}

inline vector operator * (double c, const vector &v)
{
    vector v2 = {v.x *c, v.y * c};
    return v2;
}

inline double operator * (const point &c, const vector &v)
{
    double d = v.x *c.x + v.y * c.y;
    return d;
}

inline vector operator / (double c, const vector &v)
{
    vector v2 = {v.x / c, v.y / c};
    return v2;
}

inline vector operator - (const vector &v1, const vector &v2)
{
    vector v = {v1.x - v2.x, v1.y - v2.y};
    return v;
}

inline double operator * (const vector &v1, const vector &v2 )
{
    return v1.x * v2.x + v1.y * v2.y;
}


#endif	/* SPACE_H */

