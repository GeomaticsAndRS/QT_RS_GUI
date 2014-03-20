#include "transvoidtointone.h"

TransVoidToIntOne::TransVoidToIntOne(GDALRasterBand* p_RasterBand,void* p_BandData,GDALDataType n_BandType):
    TransVoidToInt(p_RasterBand,p_BandData,n_BandType)
{

}

double TransVoidToIntOne::GetValue(int index)
{
    double n_Value;
    if(nBandType==GDT_Byte)
      {
        char n_val1=((char*)pBandData)[index];
        n_Value=n_val1;
      }
    else if(nBandType==GDT_UInt16||nBandType==GDT_Int16)
      {
        int16_t n_val1=((int16_t*)pBandData)[index];
        n_Value =n_val1;
      }
    else if(nBandType==GDT_UInt32||nBandType==GDT_Int32)
      {
        int32_t n_val1=((int32_t*)pBandData)[index];
        n_Value =n_val1;
      }
    else if(nBandType==GDT_Float32)
      {
        float n_val1=((float*)pBandData)[index];
        n_Value =n_val1;
      }
    else if(nBandType==GDT_Float64)
      {
        double n_val1=((double*)pBandData)[index];
        n_Value =n_val1;
      }
    return n_Value;
}
