// GetGC.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int main(int argc,char *argv[])
{
	CV_Assert(argc == 3);
	CStr imgW = argv[1], salDir = argv[2];
	string imgDir, imgExt;
	vecS namesNE;
	CmFile::MkDir(salDir); 
	int imgNum = CmFile::GetNamesNE(imgW, namesNE, imgDir, imgExt);

	for (int i = 0; i < imgNum; i++){
		if (CmFile::FilesExist(salDir + namesNE[i] + "_GC.png"))
			continue;

		Mat img = imread(imgDir + namesNE[i] + imgExt);
		CV_Assert(img.data != NULL);
		img.convertTo(img, CV_32FC3, 1.0/255);
		CmSaliencyGC sGC(img, "", true);
		sGC.HistgramGMMs();
		Mat sal1f = sGC.GetSaliencyCues();
		imwrite(salDir + namesNE[i] + "_GC.png", sal1f*255);
	}
}

