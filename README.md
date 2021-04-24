# SVG_Manager

SVG Manager is a C++ library for creating SVG files.<br>

## Details

```cpp
/*
 * Classes and Methods
*/

class Color

    Color();
    Color(string color);
    string get();

class Style

    Style();
    Style(Color fill, Color stroke); 

    string get();
    void setFill(Color fill, float fill_opacity);
    void setStroke(Color stroke, float stroke_opacity, float stroke_width);
    void setFont(string font);
    void setSize(float size_px);    // pixel
    void set(Color fill, float fill_opacity, Color stroke, float stroke_width, float stroke_opacity);  

class Point

    Point();
    Point(float x, float y);

    Point polar(float radius, int angle);
    Point convert(int window_height);
    Point operator+(Point rhs);
    Point negative();
    Point swap();
    string get();

class Polygon

    Polygon();
    Polygon(vector<Point> points);
    Polygon(vector<Point> points, Style style, string label);

    string get();
    vector<string> getSvgVector();
    void set(vector<Point> points, Style style, string label);

class Rectangle

    Rectangle();
    Rectangle(Point origin, float width, float height);
    Rectangle(Point origin, float width, float height, string label);
    Rectangle(Point origin, float width, float height, float radius_x, float radius_y, Style style, string label);

    string get();
    vector<string> getSvgVector();
    void set(Point origin, float width, float height, float radius_x, float radius_y, Style style, string label); 

class Circle

    Circle();
    Circle(Point origin, float radius);
    Circle(Point origin, float radius, Style style, string label);

    string get();
    vector<string> getSvgVector();
    void set(Point origin, float radius, Style style, string label);

class Text

    Text() {}
    Text(Point origin, string text);
    Text(Point origin, string text, Style style, string label); 

    string get();
    vector<string> getSvgVector();
    void set(Point origin, string text, Style style, string label);

class SVG

    SVG(string path); 
    SVG(string path, int window_width, int window_height);

    void add(vector<string> content);
    void make();
    void clear();
    void save();
    void view();

    void setPath(string path);
    void background(bool enable);
```

## Example

**Compile and run:**<br>
```
    g++ svg_manager.cpp example.cpp -o CreateSVG

    ./CreateSVG
```

**Code:** [example.cpp](https://github.com/jpenrici/SVG_Manager/blob/main/src/example.cpp)

**Result:**<br>

![Example](https://github.com/jpenrici/SVG_Manager/blob/main/images/example.png)
