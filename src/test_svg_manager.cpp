/*
 *   Compile:
 *      g++ svg_manager.cpp test_svg_manager.cpp -o Test_svg_manager
 *
 *   Run:
 *      ./Test_svg_manager
*/
#include "svg_manager.h"

#include <iostream>
#include <vector>

using namespace std;

// View Vector
template<typename T>
void viewVector(vector<T> v)
{
    switch (v.size())
    {
        case 0:
            cout << "Empty\n";
            break;
        case 1:
            cout << v[0] << '\n';
            break;
        default:
            for(auto i : v)
                cout << i << '\n';
    }
}

int main()
{
    // TEST

    auto check = [](string s) {
        if (s.empty())
            s = "empty";
        return s;
    };

    // SVG
    int window_size = 500;

    string path = "../images/";
    string filename = "test_image.svg";
    SVG imageSVG(path + filename, window_size, window_size);

    // Color
    Color color;
    cout << color.color << '\n';
    cout << color.get() << '\n';
    
    color.color = "#A0B0C0";
    cout << color.color << '\n';    

    cout << Color("#AABBCC").color << '\n';

    // Style
    Style style;
    cout << style.get() << '\n';

    style.set(Color("#FF00FF"), 0.8, Color("#00FF00"), 1.0, 0.5);
    cout << style.get() << '\n';

    cout << Style(color, Color("#AABBCC")).get() << '\n';

    // Point
    Point p1;
    cout << "x:" << p1.x << " y:" << p1.y << '\n';
    cout << p1.get() << '\n';

    Point p2(10, 10);
    cout << p2.get() << '\n';

    Point p3(20, 30);
    cout << (p2 + p3).get() << '\n';
    cout << (p3 + p2).get() << '\n';
    cout << "x:" << (p3 + p2).x << '\n';
    cout << "y:" << (p3 + p2).y << '\n';

    cout << p3.swap().get() << '\n';
    cout << p3.swap().negative().get() << '\n';

    Point p4;
    for (int angle = 0; angle <= 360; angle += 45)
    {
        cout << p4.get() << " polar(radius:10, angle:" << angle << "):"
            << p4.polar(10, angle).get() << '\n';
    }

    // Styles
    Color white("#FFFFFF");
    Color black("#000000");
    Color red("#FF0000");
    Color green("#00FF00");
    Color blue("#0000FF");

    Style style_poligon(white, green);
    Style style_rectangle(Color("#FFFF00"), Color("#00FFFF"));
    Style style_circle(red, blue);
    Style style_text(blue, red);

    // Points
    vector<Point> points {Point(300, 50), Point(400, 50), Point(300, 150)};

    // Polygon()
    Polygon polygon_1;
    string svg = polygon_1.get();
    cout << check(svg) << '\n';
    viewVector(polygon_1.getSvgVector());
    cout << polygon_1.getSvgVector().size() << '\n';

    // void set(vector<Point> points, Style style, string label)
    style_poligon.setFill(Color("#FF00AA"), 0.5);   
    polygon_1.set(points, style_poligon, "triangle_1");
    cout << check(polygon_1.get()) << '\n';
    cout << polygon_1.getSvgVector().size() << '\n';

    // Polygon(vector<Point> points);
    points.push_back(Point(200, 50));
    Polygon polygon_2(points);
    viewVector(polygon_2.getSvgVector());

    // Polygon(vector<Point> points, Style style, string label);
    style_poligon.setStroke(Color("FFAAFF"), 1.0, 2.0);
    Polygon polygon_3(points, style_poligon, "triangle_2");
    cout << check(polygon_3.get()) << '\n';

    // Rectangle()
    Rectangle rectangle_1;
    cout << check(rectangle_1.get()) << '\n';

    // Rectangle(Point origin, float width, float height);
    Rectangle rectangle_2(Point(60, 150), 100, 200);
    cout << check(rectangle_2.get()) << '\n';

    // Rectangle(Point origin, float width, float height, string label);
    Rectangle rectangle_3(Point(175, 150), 100, 100, "square");
    cout << check(rectangle_3.get()) << '\n';

    // Rectangle(Point origin, float width, float height, float radius_x,
    //           float radius_y,    Style style, string label);
    Rectangle rectangle_4(Point(280, 150), 200, 100, 20.0, 30.0, 
        style_rectangle, "rectangle");
    viewVector(rectangle_4.getSvgVector());

    // Circle()
    Circle circle_1;
    cout << check(circle_1.get()) << '\n';

    // Circle(Point origin, float radius);
    Circle circle_2(Point(60, 80), 60);
    cout << check(circle_2.get()) << '\n';
    
    // Circle(Point origin, float radius, Style style, string label);
    Circle circle_3(Point(150, 80.50), 35.5, style_circle, "Circle");
    viewVector(circle_3.getSvgVector());

    // Cartesian plane
    int x = 420;
    int y = 350;
    int w = 50;
    int h = 80;

    Point A(x,y);
    Point B(x, y + h);
    Point C(x + w / 2, y + h * 1.5);
    Point D(x + w, y + h);
    Point E(x + w, y);

    Polygon ABCDE({A, B, C, D, E});

    // Convert SVG plane
    Point F(A.convert(window_size));
    Point G(B.convert(window_size));
    Point H(C.convert(window_size));
    Point I(D.convert(window_size));
    Point J(E.convert(window_size));

    Polygon FGHIJ({F, G, H, I, J});

    cout << A.get() << " => " << F.get() << '\n';
    cout << B.get() << " => " << G.get() << '\n';
    cout << C.get() << " => " << H.get() << '\n';
    cout << D.get() << " => " << I.get() << '\n';
    cout << E.get() << " => " << J.get() << '\n';

    // Text
    style_text.setFont("Courier");
    style_text.setSize(30);

    // Text(Point origin, string text, Style style, string label)
    string text = "SVG Manager";
    Text txt(Point(window_size / 2, 30), text, style_text, "Txt");

    // Add 
    imageSVG.add(polygon_1.getSvgVector());
    imageSVG.add(polygon_2.getSvgVector());
    imageSVG.add(polygon_3.getSvgVector());
    imageSVG.add(rectangle_1.getSvgVector());
    imageSVG.add(rectangle_2.getSvgVector());
    imageSVG.add(rectangle_3.getSvgVector());
    imageSVG.add(rectangle_4.getSvgVector());
    imageSVG.add(circle_1.getSvgVector());
    imageSVG.add(circle_2.getSvgVector());
    imageSVG.add(circle_3.getSvgVector());
    imageSVG.add(ABCDE.getSvgVector());
    imageSVG.add(FGHIJ.getSvgVector());
    imageSVG.add(txt.getSvgVector());

    // Finalize
    imageSVG.make();
    // imageSVG.view();
    imageSVG.save();

    // Background transparent
    imageSVG.background(false);
    imageSVG.make();

    // Copy transparent
    imageSVG.setPath(path + "copy_" + filename);
    imageSVG.save();

    return 0;
}
