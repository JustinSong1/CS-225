/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    int rows = theSource.getRows();
    int cols = theSource.getColumns();
    MosaicCanvas* canvas = new MosaicCanvas(rows, cols);
    vector<Point<3>> points;
    map<Point<3>, TileImage> tileMap;
    points.reserve(theTiles.size());
    for (size_t i = 0; i < theTiles.size(); i++) {
        LUVAPixel avg = theTiles[i].getAverageColor();
        Point<3> point = convertToXYZ(avg);
        points.push_back(point);
        tileMap[point] = theTiles[i];
    }

    KDTree<3> pointsTree(points);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            Point<3> target = convertToXYZ(theSource.getRegionColor(i, j));
            Point<3> replacement = pointsTree.findNearestNeighbor(target);
            canvas -> setTile(i, j, &tileMap[replacement]);
        }
    }
    return canvas;
}

