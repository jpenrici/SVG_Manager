/*
 * Tool for building SVG images.
 *
 */
#include "svg_manager.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>

using namespace std;

const string TAB1 {char(32),char(32),char(32),char(32)};
const string TAB2 = TAB1 + char(32) + char(32);
const string TAB3 = TAB2 + char(32) + char(32);
const string TAB4 = TAB3 + char(32) + char(32);
const string SPACE {char(32)};
const string STRING_EMPTY = "";

static int index = 0;

// Class Color
//////////////
// Empty

// Class Style
//////////////
Style::Style()
{
    size_px = 0;
    font = STRING_EMPTY;
    set(Color(COLOR_BG), 1.0, Color(COLOR_DEFAULT), 1.0, 1.0);
}

Style::Style(Color fill, Color stroke) : fill(fill), stroke(stroke)
{
    size_px = 0;
    font = STRING_EMPTY;
    set(fill, 1.0, stroke, 1.0, 1.0);
}

string Style::get()
{
    string text = "";
    if (size_px > 0)
    {
        text = "font-style:normal;font-size:" + to_string(size_px) +"px";
        if (!font.empty())
        {
            text += ";font-family:" + font;
        }
        else
        {
            text += ";font-family:Arial";
        }   
    }

    return "style=\"fill:" + fill.color + ";fill-opacity:" + to_string(fill_opacity)
        + ";stroke:" + stroke.color + ";stroke-width:" + to_string(stroke_width)
        + ";stroke-opacity:" + to_string(stroke_opacity) + text + "\"";
}

void Style::setFont(string font)
{
    this->font = font;
}

void Style::setSize(float size_px)
{
    this->size_px = size_px;
}

void Style::setFill(Color fill, float fill_opacity)
{
    this->fill = fill;
    this->fill_opacity = fill_opacity;
}

void Style::setStroke(Color stroke, float stroke_opacity, float stroke_width)
{
    this->stroke = stroke;
    this->stroke_opacity = stroke_opacity;
    this->stroke_width = stroke_width;
}

void Style::set(Color fill, float fill_opacity, Color stroke, float stroke_width,
    float stroke_opacity)
{
    this->fill = fill;
    this->stroke = stroke;
    this->fill_opacity = fill_opacity;
    this->stroke_opacity = stroke_opacity;
    this->stroke_width = stroke_width; 
}

// Class Point
//////////////
Point Point::polar(float radius, int angle)
{
    if (angle < 0)
        angle += 180;

    if (angle > 360)
        angle = angle % 360;

    if (radius < 0)
        radius = 0; 

    float rad = (angle * PI) / 180.00;

    return Point(x + radius * cos(rad), y + radius * sin(rad));
}

Point Point::convert(int window_height)
{
    return Point(x, window_height - y);
}

Point Point::operator+(Point rhs)
{
    return Point(x + rhs.x, y + rhs.y);
}

Point Point::negative()
{
    return Point(-x, -y);
}

Point Point::swap()
{
    return Point(y, x);
}

// Class Polygon
////////////////
Polygon::Polygon(vector<Point> points)
{
    set(points, Style(), STRING_EMPTY);
}

Polygon::Polygon(vector<Point> points, Style style, string label)
{ 
    set(points, style, label);
}

string Polygon::get()
{
    string output = "";
    for (auto item : svg)
        output += item + '\n';

    return output;
}

vector<string> Polygon::getSvgVector()
{
    return svg;
}

void Polygon::set(vector<Point> points, Style style, string label)
{
    if (points.empty()) {
        cout << "nothing to do\n";
        return;
    }

    label = !label.empty() ? label : "Poly_" + to_string(index++);

    string coordenates = "";
    for(auto p : points)
        coordenates += to_string(p.x) + "," + to_string(p.y) + SPACE;   

    svg.clear();
    svg = {
        TAB2 + "<polygon ",
        TAB3 + "id=\"" + label + "\"",
        TAB3 + "points=\"" + coordenates + "\"",
        TAB3 +  style.get() + " />"     
    };
}

// Class Rectangle
//////////////////
Rectangle::Rectangle(Point origin, float width, float height)
{
    set(origin, width, height, 0.0, 0.0, Style(), STRING_EMPTY);
}

Rectangle::Rectangle(Point origin, float width, float height, string label)
{
    set(origin, width, height, 0.0, 0.0, Style(), label);
}

Rectangle::Rectangle(Point origin, float width, float height, float radius_x,
    float radius_y, Style style, string label)
{
    set(origin, width, height, radius_x, radius_y, style, label);
}

string Rectangle::get()
{
    string output = "";
    for (auto item : svg)
        output += item + '\n';

    return output;
}

vector<string> Rectangle::getSvgVector()
{
    return svg;
}

void Rectangle::set(Point origin, float width, float height, float radius_x,
    float radius_y, Style style, string label)
{
    label = !label.empty() ? label : "Rect_" + to_string(index++);
    
    svg.clear();
    svg = {
        TAB2 + "<rect",
        TAB3 + "id=\"" + label + "\"",
        TAB3 + "x=\"" + to_string(origin.x) + "\" y=\"" + to_string(origin.y) + "\"",
        TAB3 + "width=\"" + to_string(width) + "\" height=\"" + to_string(height) + "\"",
        TAB3 + "rx=\"" + to_string(radius_x) + "\" ry=\"" + to_string(radius_y) + "\"",
        TAB3 +  style.get() + " />" 
    };
}

// Class Circle
///////////////
Circle::Circle(Point origin, float radius)
{
    set(origin, radius, Style(), STRING_EMPTY);
}

Circle::Circle(Point origin, float radius, Style style, string label)
{
    set(origin, radius, style, label);
}

string Circle::get()
{
    string output = "";
    for (auto item : svg)
        output += item + '\n';

    return output;
}

vector<string> Circle::getSvgVector()
{
    return svg;
}

void Circle::set(Point origin, float radius, Style style, string label)
{
    label = !label.empty() ? label : "Circle_" + to_string(index++);
    
    svg.clear();
    svg = {
        TAB2 + "<circle",
        TAB3 + "id=\"" + label + "\"",
        TAB3 + "cx=\"" +  to_string(origin.x) + "\" cy=\"" +  to_string(origin.y) + "\"",
        TAB3 + "r=\"" + to_string(radius) + "\"",
        TAB3 +  style.get() + " />"
    };
}

// Class Text
/////////////
Text::Text(Point origin, string text)
{
    Style style_text;
    style_text.setFont("Arial");
    style_text.setSize(12);
    set(origin, text, style_text, STRING_EMPTY);
}

Text::Text(Point origin, string text, Style style, string label)
{
    set(origin, text, style, label);
}

string Text::get()
{
    string output = "";
    for (auto item : svg)
        output += item + '\n';

    return output;
}

vector<string> Text::getSvgVector()
{
    return svg;
}

void Text::set(Point origin, string text, Style style, string label)
{
    label = !label.empty() ? label : "Text_" + to_string(index++);
    
    svg.clear();
    svg = {
        TAB2 + "<text",
        TAB3 + "id=\"" + label + "\"",
        TAB3 + "x=\"" +  to_string(origin.x) + "\" y=\"" +  to_string(origin.y) + "\"",
        TAB3 +  style.get() + ">" + text + "</text>"
    };

}

// Class SVG
//////////////
SVG::SVG(string path)
{
    this->path = path;
    vbx = VBX;
    vby = VBY;
    
    bg_enabled = true;

    cout << vbx << "x" << vby << " SVG image, initialized ...\n";
    clear();
}

SVG::SVG(string path, int window_width, int window_height)
{
    this->path = path;
    vbx = window_width;
    vby = window_height;
    
    bg_enabled = true;
    
    cout << vbx << "x" << vby << " SVG image, initialized ...\n";
    clear();
}

void SVG::make()
{
    const string INFO = "Created in C++ algorithm";
    const vector<string> HEADER {
        "<?xml version=\"1.0\" standalone=\"no\"?>",
        "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\"",
        "\"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">",
        "<svg width=\"" + to_string(vbx) + "px\" height=\"" + to_string(vby)
         + "px\" viewBox=\"0 0 " + to_string(vbx) + " " + to_string(vby) + "\"",
        TAB1 + "xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">",
        TAB1 + "<title>Example</title>",
        TAB1 + "<!--" + INFO + "-->"
    };
    const vector<string> FOOTER {"</svg>"};

    // layer
    vector<string> layer;
    string label = "Layer_CppSVG";
    layer.push_back(TAB1 + "<g");
    layer.push_back(TAB2 + "inkscape:label=\"" + label + "\"");
    layer.push_back(TAB2 + "inkscape:groupmode=\"layer\"");
    layer.push_back(TAB2 + "id=\"" + label + "\">");

    // background
    if (bg_enabled)
    {
        Style style;
        vector<string> bg = Rectangle(Point(0, 0), vbx, vby, 0, 0, style,
            "background").getSvgVector();
        layer.reserve(layer.size() + bg.size());
        layer.insert(layer.end(), bg.begin(), bg.end()); 
    }

    // content
    layer.reserve(layer.size() + content.size());
    layer.insert(layer.end(), content.begin(), content.end());
    layer.push_back(TAB1 + "</g>");

    // output
    svg.clear();
    svg.reserve( HEADER.size() + layer.size() + FOOTER.size());
    svg.insert( svg.end(), HEADER.begin(), HEADER.end());
    svg.insert( svg.end(), layer.begin(), layer.end());
    svg.insert( svg.end(), FOOTER.begin(), FOOTER.end());

    if (path == "")
        path = "outSVG";

    cout << "svg: ready\n";
}

void SVG::add(vector<string> content)
{
    if (content.empty()) {
        cout << "nothing to do\n";
        return;
    }

    this->content.reserve(this->content.size() + content.size());
    this->content.insert(this->content.end(), content.begin(), content.end());
    cout << "content: stored\n";
}

void SVG::clear()
{
    content.clear();
    cout << "content: deleted\n";
}

void SVG::save()
{
    ofstream svgOut(path);

    for (string str : svg)
        svgOut << str << '\n';

    svgOut.close();
    cout << "svg: saved\nfile: " <<  path << '\n';
}

void SVG::view()
{
    for (string str : svg)
        cout << str << '\n';
}

void SVG::setPath(string path)
{
    this->path = path;
}

void SVG::background(bool enable)
{
    bg_enabled = enable;
}