#include <iostream>
#include "ElevationFetcher.h"
#include <math.h>

//
// Created by Randy on 9/20/2019.
// Most code copied from https://gdal.org/tutorials/raster_api_tut.html
//
ElevationFetcher::ElevationFetcher(const char* folderName) {
    GDALAllRegister();
    poDataset = (GDALDataset *) GDALOpen( folderName, GA_ReadOnly );
    if( poDataset == nullptr ){
        cout << "Failed to open dataset" << '\n';
        return;
    }
//    printf( "Driver: %s/%s\n",
//            poDataset->GetDriver()->GetDescription(),
//            poDataset->GetDriver()->GetMetadataItem( GDAL_DMD_LONGNAME ) );
//    printf( "Size is %dx%dx%d\n",
//            poDataset->GetRasterXSize(), poDataset->GetRasterYSize(),
//            poDataset->GetRasterCount() );
//    if( poDataset->GetProjectionRef() != nullptr )
//        printf( "Projection is `%s'\n", poDataset->GetProjectionRef() );
    double adfGeoTransform[6];
    auto getGeoTransformResult = poDataset->GetGeoTransform( adfGeoTransform );
    if( getGeoTransformResult != CE_None ){
        cout << "Could not get valid transform" << '\n';
        return;
    }
    originX = adfGeoTransform[0];
    originY = adfGeoTransform[3];
    pixelX = adfGeoTransform[1];
    pixelY = adfGeoTransform[5];
//    int             nBlockXSize, nBlockYSize;
//    int             bGotMin, bGotMax;
//    double          adfMinMax[2];
    poBand = poDataset->GetRasterBand( 1 );
//    poBand->GetBlockSize( &nBlockXSize, &nBlockYSize );
//    printf( "Block=%dx%d Type=%s, ColorInterp=%s\n",
//            nBlockXSize, nBlockYSize,
//            GDALGetDataTypeName(poBand->GetRasterDataType()),
//            GDALGetColorInterpretationName(
//                    poBand->GetColorInterpretation()) );
//    adfMinMax[0] = poBand->GetMinimum( &bGotMin );
//    adfMinMax[1] = poBand->GetMaximum( &bGotMax );
//    if( ! (bGotMin && bGotMax) )
//        GDALComputeRasterMinMax((GDALRasterBandH)poBand, TRUE, adfMinMax);
//    printf( "Min=%.3fd, Max=%.3f\n", adfMinMax[0], adfMinMax[1] );
//    if( poBand->GetOverviewCount() > 0 )
//        printf( "Band has %d overviews.\n", poBand->GetOverviewCount() );
//    if( poBand->GetColorTable() != nullptr )
//        printf( "Band has a color table with %d entries.\n",
//                poBand->GetColorTable()->GetColorEntryCount() );
}
//vector<float> ElevationFetcher::getElevations(const vector<tuple<double, double>>& latLngs) {
//    vector<float> elevations(latLngs.size());
//    int i = 0;
//    for (auto [lat, lng] : latLngs) {
//        // Thanks to padding on raster files, we can just use simple rounding
//        poBand->RasterIO( GF_Read, (int) round((lng - originX) / pixelX), (int) round((lat - originY) / pixelY), 1, 1,
//                          &elevations[i], 1, 1, GDT_Float32,
//                          0, 0 );
//        i++;
//        }
//    return elevations;
//}

vector<float> ElevationFetcher::getElevations(const vector<pair<int, int>>& latLngs) {
    vector<float> elevations(latLngs.size());
    int i = 0;
    // Not sure why normal iteration won't work?
//    unordered_set<tuple<int, int>, hash_pair>::iterator itr;
//    int lat, lng;
//    for (itr = latLngs.begin(); itr != latLngs.end(); itr++)
    for (auto [lat, lng] : latLngs)
    {

        // Thanks to padding on raster files, we can just use simple rounding
//        tie(lat, lng) = (*itr);
        poBand->RasterIO( GF_Read, lng, lat, 1, 1,
                          &elevations[i], 1, 1, GDT_Float32,
                          0, 0 );
        i++;
    }
    return elevations;
}
#include "ElevationFetcher.h"
