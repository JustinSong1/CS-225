#include "Image.h"
#include "StickerSheet.h"

int main() {

    //
    // Reminder:
    //   Before exiting main, save your creation to disk as myImage.png
    //

    Image court;
    court.readFromFile("court.png");

    Image steph;
    steph.readFromFile("steph.png");
    steph.scale(0.4);

    Image lebron;
    lebron.readFromFile("lebron.png");
    lebron.scale(0.25);

    Image trophy;
    trophy.readFromFile("trophy.png");
    trophy.scale(0.3);

    StickerSheet sheet(court, 5);

    sheet.addSticker(steph, 100, 300);
    sheet.addSticker(lebron, 500, 100);
    sheet.addSticker(trophy, 400, 300);

    sheet.render().writeToFile("myImage.png");
    return 0;
}
