#ifndef TRANSVOIDTOINT_H
#define TRANSVOIDTOINT_H
#include <gdal.h>
#include <gdal_priv.h>
#include <stdint.h>

class TransVoidToInt
{
 public:
  TransVoidToInt(GDALRasterBand*,void*,GDALDataType );
 protected:
   void *pBandData;
   double nScale,nOffSet;//compress the pixel value to 0-255;

   GDALDataType nBandType;
   GDALRasterBand *pRasterBand;


public:
   int GetValue(int);
   bool ComputeRasterScale();
};

#endif // TRANSVOIDTOINT_H
