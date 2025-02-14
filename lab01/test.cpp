#include<set>
#include<gmsh.h>

int main(int argc, char** argv){

    gmsh::initialize();
    gmsh::model::add("test");
    double lc = 0.02;
    double R = 3.0;
    double r = 0.5;
    double w = 0.05;
    int p0 = gmsh::model::geo::addPoint(0, 0, 0, lc);
    int p1 = gmsh::model::geo::addPoint(R-r, 0, 0, lc);
    int p2 = gmsh::model::geo::addPoint(R, 0, 0, lc);
    int p3 = gmsh::model::geo::addPoint(R, 0, r, lc);
    int p4 = gmsh::model::geo::addPoint(R + r, 0, 0, lc);
    int p5 = gmsh::model::geo::addPoint(R, 0, -r, lc);
    int arc1 = gmsh::model::geo::addCircleArc(p1, p2, p3);
    int arc2 = gmsh::model::geo::addCircleArc(p3, p2, p4);
    int arc3 = gmsh::model::geo::addCircleArc(p4, p2, p5);
    int arc4 = gmsh::model::geo::addCircleArc(p5, p2, p1);

    int cl1 = gmsh::model::geo::addCurveLoop({arc1, arc2, arc3, arc4});
    std::vector<std::pair<int, int>> ov;
    gmsh::model::geo::copy({{1, arc1}, {1, arc2}, {1, arc3}, {1, arc4}}, ov);
    gmsh::model::geo::dilate(ov, R, 0, 0, 1-w/r, 1-w/r, 1-w/r);
    int cl2 = gmsh::model::geo::addCurveLoop({ov[0].second, ov[1].second, ov[2].second, ov[3].second});
    int s1 = gmsh::model::geo::addPlaneSurface({cl1, -cl2});
    gmsh::model::geo::synchronize();
    gmsh::model::mesh::generate(2);
    std::vector<std::pair<int, int>> rot1;
    gmsh::model::geo::revolve({{2, s1}}, 0, 0, 0, 0, 0, 1, M_PI /2, rot1);
    std::vector<std::pair<int, int>> rot2;
    gmsh::model::geo::revolve({{2, rot1[0].second}}, 0, 0, 0, 0, 0, 1, M_PI / 2, rot2);
    std::vector<std::pair<int, int>> rot3;
    gmsh::model::geo::revolve({{2, rot2[0].second}}, 0, 0, 0, 0, 0, 1, M_PI / 2, rot3);
    std::vector<std::pair<int, int>> rot4;
    gmsh::model::geo::revolve({{2, rot3[0].second}}, 0, 0, 0, 0, 0, 1, M_PI / 2, rot4);

    gmsh::model::geo::addPhysicalGroup(3, {rot1[1].second, rot2[1].second, rot3[1].second, rot4[1].second}, 1);
    gmsh::model::geo::synchronize();
    gmsh::model::mesh::generate(3);

    gmsh::write("tt.msh");

    std::set<std::string> args(argv, argv + argc);
    if(!args.count("-nopopup")) gmsh::fltk::run();

    gmsh::finalize();



//https://ipmnet.ru/~ermakov/gmsh/doc/texinfo/gmsh.pdf  2.3 example -> rotation 
    return 0;
}