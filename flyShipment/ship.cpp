#include "ship.h"

void Ship::createShip(int L, int H, int Wt, int Wb) {
    // W - x
    // H - y
    // L - z
    ship_size.H = H;
    ship_size.L = L;
    ship_size.Wt = Wt;
    ship_size.Wb = Wb;

    Point init_point;
    init_point.set(0,0,L); // чтобы не пересекаться с грузом.

    Point form_point;
    form_point.set(0,0,L);


    ShipPolygon polygon;
// for x/y axe
    Point xy_points_array[4];

    xy_points_array[0] = init_point;
    form_point.set_x(Wb);
    xy_points_array[1] = form_point;
    form_point.set_x((Wb - Wt)/2);
    form_point.set_y(H);
    xy_points_array[2] = form_point;
    form_point.set_x(Wb - (Wb - Wt)/2);
    xy_points_array[3] = form_point;
    polygon.createPolygon(xy_points_array);
    ship.push_back(polygon);
    for (int i = 0; i < 4; i++) {
        xy_points_array[i].print_point();
        xy_points_array[i].set_z(2 * L);
        std::cout << std::endl;
    }
    for (int i = 0; i < 4; i++) {
        xy_points_array[i].print_point();
        std::cout << std::endl;
    }
    polygon.createPolygon(xy_points_array);
    ship.push_back(polygon);
// for x/z axe
    Point xz_points_array[4];
    form_point.set(0,0,L);

    xz_points_array[0] = init_point;
    form_point.set_x(Wb);
    xz_points_array[1] = form_point;
    form_point.set_x(0);
    form_point.set_z(2*L);
    xz_points_array[2] = form_point;
    form_point.set_x(Wb);
    xz_points_array[3] = form_point;
    polygon.createPolygon(xz_points_array);
    ship.push_back(polygon);
    for (int i = 0; i < 4; i++) {
        xz_points_array[i].print_point();
        std::cout << std::endl;
    }

    form_point.set(0,0,L);
    form_point.set_x((Wb-Wt)/2);
    xz_points_array[0] = form_point;
    form_point.set_x(Wb - (Wb-Wt)/2);
    xz_points_array[1] = form_point;
    form_point.set_x((Wb-Wt)/2);
    form_point.set_z(2*L);
    xz_points_array[2] = form_point;
    form_point.set_x(Wb - (Wb-Wt)/2);
    xz_points_array[3] = form_point;
    polygon.createPolygon(xz_points_array);
    ship.push_back(polygon);
    for (int i = 0; i < 4; i++) {
        xz_points_array[i].print_point();
        std::cout << std::endl;
    }

// for y/z axe
    Point yz_points_array[4];
    form_point.set(0,0,L);

    yz_points_array[0] = init_point;
    form_point.set_z(2*L);
    yz_points_array[1] = form_point;
    form_point.set_z(L);
    form_point.set_y(H);
    form_point.set_x((Wb-Wt)/2);
    yz_points_array[2] = form_point;
    form_point.set_z(2*L);
    yz_points_array[3] = form_point;
    polygon.createPolygon(yz_points_array);
    ship.push_back(polygon);
    for (int i = 0; i < 4; i++) {
        yz_points_array[i].print_point();
        std::cout << std::endl;
    }

    form_point.set(Wb,0,L);
    yz_points_array[0] = form_point;
    form_point.set_z(2*L);
    yz_points_array[1] = form_point;
    form_point.set_z(L);
    form_point.set_x(Wb - (Wb-Wt)/2);
    form_point.set_y(H);
    yz_points_array[2] = form_point;
    form_point.set_z(2*L);
    yz_points_array[3] = form_point;
    polygon.createPolygon(yz_points_array);
    ship.push_back(polygon);
    for (int i = 0; i < 4; i++) {
        yz_points_array[i].print_point();
        std::cout << std::endl;
    }

    Point somepoint;
    somepoint.set(Wb/2, H/2, 1.5*L);
    center = somepoint;

}

void Ship::move(double dx, double dy, double dz) {
    Point change(dx, dy, dz);

    for(ShipPolygon& pol : ship) {
        for (Edge& edge : pol.spolygon) {
            edge.begin += change;
            edge.end += change;
        }
    }

    center += change;
}

void Ship::rotate(double dxy, double dyz, double dzx) {

    for(ShipPolygon& pol : ship) {
        for (Edge& edge : pol.spolygon) {
            if (dxy != 0) {
                edge.begin.rotate_dxy(dxy, center);
                edge.end.rotate_dxy(dxy, center);
            }
            if (dyz != 0) {
                edge.begin.rotate_dyz(dyz, center);
                edge.end.rotate_dyz(dyz, center);
            }
            if (dzx != 0) {
                edge.begin.rotate_dzx(dzx, center);
                edge.end.rotate_dyz(dyz, center);
            }
        }
    }

}

void Ship::resize(double k) {
    for(ShipPolygon& pol : ship) {
        for (Edge& edge : pol.spolygon) {
            edge.begin += center + (edge.begin - center) * k;
            edge.end += center + (edge.end - center) * k;
        }
    }

    center *= k; // здесь может быть трабл

}

void Ship::rotate(double dxy, double dyz, double dzx, const Point& center) {
    for(ShipPolygon& pol : ship) {
        for (Edge& edge : pol.spolygon) {
            if (dxy != 0) {
                edge.begin.rotate_dxy(dxy, center);
                edge.end.rotate_dxy(dxy, center);
            }
            if (dyz != 0) {
                edge.begin.rotate_dyz(dyz, center);
                edge.end.rotate_dyz(dyz, center);
            }
            if (dzx != 0) {
                edge.begin.rotate_dzx(dzx, center);
                edge.end.rotate_dyz(dyz, center);
            }
        }
    }

    if (dxy != 0) {
        this->center.rotate_dxy(dxy, center);
    }
    if (dyz != 0) {
        this->center.rotate_dyz(dyz, center);
    }
    if (dzx != 0) {
        this->center.rotate_dzx(dzx, center);
    }
}

void Ship::resize(double k, const Point& center) {
    for(ShipPolygon& pol : ship) {
        for (Edge& edge : pol.spolygon) {
            edge.begin = center + (edge.begin - center) * k;
            edge.end = center + (edge.end - center) * k;
        }
    }

    this->center = center + (this->center - center) * k;

}