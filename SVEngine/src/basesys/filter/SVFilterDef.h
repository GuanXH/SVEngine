//
// SVFilterDef.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//
#ifndef SV_FILTERDEF_H
#define SV_FILTERDEF_H


enum SVFILTERITEMTYPE {
    E_BEATY_FILTER=0,
    E_SHADOWS_FILTER,
    E_CONTRAST_FILTER,
    E_SATURATION_FILTER,
    E_ACUTANCE_FILTER,
    E_BRIGHTNESS_FILTER,
    E_WHITENING_FILTER,
    E_HIGHLIGHTS_FILTER,
    E_GAMMA_FILTER,
    E_REDSHIFT_FILTER,
    E_GREENSHIFT_FILTER,
    E_BLUESHIFT_FILTER,
    E_SDREDSHIFT_FILTER,
    E_SDGREENSHIFT_FILTER,
    E_SDBLUESHIFT_FILTER,
    E_HHREDSHIFT_FILTER,
    E_HHGREENSHIFT_FILTER,
    E_HHBLUESHIFT_FILTER,
    E_TEMPERATURE_FILTER,
    E_TINT_FILTER
};

enum SVFILTERFUNCTYPE{
    SV_FUNC_NONE=0,
    SV_FUNC_BEAUTY,
    SV_FUNC_BASEONFILTER,
    SV_FUNC_LOOKUP,
    SV_FUNC_BSPLINE,
    SV_FUNC_BRIGHTNESSCONTRAST
};

#endif /* SV_FILTERDEF_H */
