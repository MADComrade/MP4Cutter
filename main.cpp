//#include <QCoreApplication>
#include "mp4parser.h"
#include "streamreader.h"
#include "streamwriter.h"

/// MVHD

int main(int argc, char *argv[])
{
    //QCoreApplication a(argc, argv);
    //StreamReader reader("D:/asklab/video/video_2018_05_30_20-21-01.mp4");
    StreamReader reader("D:/file_03_05_2015_23-27-38.mp4");
    if (reader.openStream())
    {
        MP4Parser parser;
        parser.parse(reader);
        //parser.prepareData(360,450);
        parser.prepareData(15,45);
        StreamWriter writer("D:/newfile.mp4");
        if(writer.openStream()){
            parser.writeOnlyVideo(reader,writer);
        }
    }
    system("pause");
    return 0;//a.exec();
}
