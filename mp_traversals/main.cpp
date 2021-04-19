
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;

int main() {

  PNG png;
  png.readFromFile("tests/lantern.png");

  FloodFilledImage image(png);
  BFS bfs(png, Point(10, 10), 0.1);
  MyColorPicker picker{};
  image.addFloodFill(bfs, picker);
  DFS dfs(png, Point(118,10), 0.1);
  image.addFloodFill(dfs, picker);
  Animation animation = image.animate(1000);
  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");


  return 0;
}
