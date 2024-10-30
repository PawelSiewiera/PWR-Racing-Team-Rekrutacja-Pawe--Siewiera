#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <string>

// Struktura reprezentująca punkt (x, y)
struct Point {
    double x; // współrzędna x
    double y; // współrzędna y
};

// Funkcja obliczająca iloczyn wektorowy trzech punktów
double pointCrossProduct(Point p1, Point p2, Point p3) {
    return (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
}

// Funkcja obliczająca kąt między punktem a punktem odniesienia
double pointAngle(Point point1, Point point2) {
    return atan2(point2.y - point1.y, point2.x - point1.x);
}

// Funkcja obliczająca dlugość wektora 2 punktów
double pointLength(Point point1, Point point2) {
    return sqrt(pow(point2.x - point1.x, 2) + pow(point2.y - point1.y, 2));
}

// Funkcja znajdująca podzbiór punktów tworzących otoczkę wypukłą
std::vector<Point> ConvexHull(std::vector<Point> points) {
    // Znajdź punkt o najmniejszej wartości y (a jeśli wartości y są równe, to ten o mniejszym x)
    Point orientationPoint = points[0];
    for (int i = 1; i < points.size(); i++) {
        if ((points[i].y < orientationPoint.y) || (points[i].y == orientationPoint.y && points[i].x < orientationPoint.x)) {
            orientationPoint = points[i];
        }
    }

    // Sortowanie punktów według kąta względem punktu "orientationPoint"
    for (int i = 1; i < points.size(); i++) {
        for (int j = i - 1; j >= 0; j--) {
            if (pointAngle(points[j], orientationPoint) == pointAngle(points[j + 1], orientationPoint)) {
                if (pointLength(points[j], orientationPoint) > pointLength(points[j + 1], orientationPoint)) {
                    std::swap(points[j], points[j + 1]);
                }
            } else if (pointAngle(points[j], orientationPoint) > pointAngle(points[j + 1], orientationPoint)) {
                std::swap(points[j], points[j + 1]);
            }
        }
    }

    // Jeśli mamy mniej niż 3 punkty, nie da się utworzyć otoczki wypukłej, zwrot punktów
    if (points.size() <= 3) {
        return points;
    } else {
        std::vector<Point> outline; // Wektor do przechowywania punktów tworzących otoczkę wypukłą
        for (int i = 0; i < points.size(); i++) {
            // Usuwamy ostatni punkt, jeśli nie spełnia warunków otoczki wypukłej
            while (outline.size() > 1 && pointCrossProduct(outline[outline.size() - 2], outline.back(), points[i]) <= 0) {
                outline.pop_back();
            }
            outline.push_back(points[i]);
        }
        return outline; // Zwracamy punkty tworzące otoczkę wypukłą
    }
}

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <string>
#include <iomanip>

// Struktura reprezentująca punkt (x, y)
struct Point {
    double x; // współrzędna x
    double y; // współrzędna y
};

// Funkcja obliczająca iloczyn wektorowy trzech punktów
double pointCrossProduct(Point p1, Point p2, Point p3) {
    return (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
}

// Funkcja obliczająca kąt między punktem a punktem odniesienia
double pointAngle(Point point1, Point point2) {
    return atan2(point2.y - point1.y, point2.x - point1.x);
}

// Funkcja obliczająca długość wektora 2 punktów
double pointLength(Point point1, Point point2) {
    return sqrt(pow(point2.x - point1.x, 2) + pow(point2.y - point1.y, 2));
}

// Funkcja znajdująca podzbiór punktów tworzących otoczkę wypukłą
std::vector<Point> ConvexHull(std::vector<Point> points) {
    // Znajdź punkt o najmniejszej wartości y (a jeśli wartości y są równe, to ten o mniejszym x)
    Point orientationPoint = points[0];
    for (int i = 1; i < points.size(); i++) {
        if ((points[i].y < orientationPoint.y) || (points[i].y == orientationPoint.y && points[i].x < orientationPoint.x)) {
            orientationPoint = points[i];
        }
    }

    // Sortowanie punktów według kąta względem punktu "orientationPoint"
    for (int i = 1; i < points.size(); i++) {
        for (int j = i - 1; j >= 0; j--) {
            if (pointAngle(points[j], orientationPoint) == pointAngle(points[j + 1], orientationPoint)) {
                if (pointLength(points[j], orientationPoint) > pointLength(points[j + 1], orientationPoint)) {
                    std::swap(points[j], points[j + 1]);
                }
            } else if (pointAngle(points[j], orientationPoint) > pointAngle(points[j + 1], orientationPoint)) {
                std::swap(points[j], points[j + 1]);
            }
        }
    }

    // Jeśli mamy mniej niż 3 punkty, nie da się utworzyć otoczki wypukłej, zwrot punktów
    if (points.size() <= 3) {
        return points;
    } else {
        std::vector<Point> outline; // Wektor do przechowywania punktów tworzących otoczkę wypukłą
        for (int i = 0; i < points.size(); i++) {
            // Usuwamy ostatni punkt, jeśli nie spełnia warunków otoczki wypukłej
            while (outline.size() > 1 && pointCrossProduct(outline[outline.size() - 2], outline.back(), points[i]) <= 0) {
                outline.pop_back();
            }
            outline.push_back(points[i]);
        }
        return outline; // Zwracamy punkty tworzące otoczkę wypukłą
    }
}

int main() {
    // Pobieranie nazwy pliku wejściowego
    std::string fileName;
    std::vector<Point> points; // Wektor przechowujący punkty wczytane z pliku
    std::cout << "Podaj nazwe pliku" << std::endl;
    std::cin >> fileName;
    std::ifstream file(fileName);

    // Sprawdzanie, czy plik istnieje
    if (!file) {
        std::cerr << "Nie ma takiego pliku" << std::endl;
    } else {
        int n; // Liczba punktów
        file >> n; // Wczytanie liczby punktów z pliku
        double xPoint, yPoint;
        for (int i = 0; i < n; i++) {
            file >> xPoint >> yPoint; // Odczytanie współrzędnych każdego punktu
            points.push_back(Point{xPoint, yPoint}); // Dodanie punktu do wektora
        }
        file.close(); // Zamknięcie pliku
    }

    // Znajdź punkty tworzące otoczkę wypukłą
    std::vector<Point> outerPoints = ConvexHull(points);

    // Wyświetlanie punktów tworzących otoczkę wypukłą
    std::cout << "[";
    for (int i = 0; i < outerPoints.size(); i++) {
        if (i > 0 && i <= outerPoints.size() - 1)
            std::cout << ", ";
        std::cout << "(";
        std::cout << std::fixed << std::setprecision(1) << outerPoints[i].x << ", " << outerPoints[i].y;
        std::cout << ")";
    }
    std::cout << "]";

    return 0;
}
