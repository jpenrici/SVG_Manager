/*
 * Tool for building SVG images.
 *
 */
#ifndef __SVG_Manager_H__
#define __SVG_Manager_H__

#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>

using namespace std;

#define VBX 640
#define VBY 480
#define PI 3.14159265

#define WHITE         "#FFFFFF"
#define BLACK         "#000000"
#define RED           "#FF0000"
#define GREEN         "#00FF00"
#define BLUE          "#0000FF"
#define COLOR_BG      WHITE
#define COLOR_DEFAULT BLACK

class Color
{
public:

    Color() : color(COLOR_DEFAULT) {}
    Color(string color) : color(color) {}
    ~Color() {}

    string get() { return color; }

    string color;
};

class Style
{
public:

    Style();
    Style(Color fill, Color stroke); 
    ~Style() {}

    string get();
    void setFill(Color fill, float fill_opacity);
    void setStroke(Color stroke, float stroke_opacity, float stroke_width);
    void setFont(string font);
    void setSize(float size_px);    // pixel
    void set(Color fill, float fill_opacity, Color stroke, float stroke_width,
        float stroke_opacity);  

private:
    Color fill;
    Color stroke;
    float fill_opacity;
    float stroke_opacity;
    float stroke_width;

    // Text
    string font;
    float size_px;
};

class Point
{
public:

    Point() : x(0), y(0) {}                     // Cartesian coordinate system
    Point(float x, float y) : x(x), y(y) {}
    ~Point() {}

    Point polar(float radius, int angle);
    Point convert(int window_height);           // SVG coordinate system
    Point operator+(Point rhs);
    Point negative();
    Point swap();

    string get() { return "(" + to_string(x) + ", " + to_string(y) + ")"; }

    float x;
    float y;
};

class Polygon
{
public:

    Polygon() {}
    Polygon(vector<Point> points);
    Polygon(vector<Point> points, Style style, string label);
    ~Polygon() {}

    string get();
    vector<string> getSvgVector();
    void set(vector<Point> points, Style style, string label);

private:
    vector<string> svg;
};

class Rectangle
{
public:

    Rectangle() {}
    Rectangle(Point origin, float width, float height);
    Rectangle(Point origin, float width, float height, string label);
    Rectangle(Point origin, float width, float height, float radius_x,
        float radius_y, Style style, string label);
    ~Rectangle() {}

    string get();
    vector<string> getSvgVector();
    void set(Point origin, float width, float height, float radius_x,
        float radius_y, Style style, string label); 

private:
    vector<string> svg;
};

class Circle
{
public:
    Circle() {}
    Circle(Point origin, float radius);
    Circle(Point origin, float radius, Style style, string label);
    ~Circle() {}

    string get();
    vector<string> getSvgVector();
    void set(Point origin, float radius, Style style, string label);

private:
    vector<string> svg;
};

class Text
{
public:
    Text() {}
    Text(Point origin, string text);
    Text(Point origin, string text, Style style, string label); 
    ~Text() {}

    string get();
    vector<string> getSvgVector();
    void set(Point origin, string text, Style style, string label);

private:
    vector<string> svg;
    
};

class SVG
{

public:

    SVG(string path); 
    SVG(string path, int window_width, int window_height);
    ~SVG() {}

    void add(vector<string> content);
    void make();
    void clear();
    void save();
    void view();

    void setPath(string path);
    void background(bool enable);

private:
    int vbx;
    int vby;    
    string path;
    bool bg_enabled;
    vector<string> svg;
    vector<string> content;
};

#endif // __SVG_Manager_H__
